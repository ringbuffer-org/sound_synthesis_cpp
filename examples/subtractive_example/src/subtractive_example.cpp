/**
* \file subtractive_example.cpp
* \class SubtractiveExample
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/


#include"subtractive_example.h"


using std::cout;
using std::endl;


SubtractiveExample::SubtractiveExample(YamlMan *ym, int ID, string m){


    cout << "Starting Jack Client!" << endl;
    this->client = jack_client_open("Subtractive_Example", JackNullOption, &status, NULL);
    fs = jack_get_sample_rate(client);

    mode = m;

    yaml_manager = ym;

    // creating an OSC manager instance
    oscman = new OscMan(yaml_manager);

    // allocate a midi manager
    if(mode.compare("MIDI")==0)
        midiman = new MidiMan(ID);

    // allocate and initialize the
    // square wave oscillator
    square    = new SquareWave();
    square->init(100,1,0,0.5,fs);

    // allocate the biquad filter
    // and set initial parameters
    filter = new Biquad();
    filter->setBiquad(bq_type_lowpass, 1000.0 / fs, 0.707, 0);

    // initialize two envelopes
    gain_env    = new Envelope(0.05, 1, 1, fs);
    cutoff_env  = new Envelope(0.05, 1, 4, fs);

    // connect the callback function
    jack_set_process_callback(this->client, this->callback_process, this);

    // the output ports
    output_port = new jack_port_t*[nChannels];
    for (int i=0; i<nChannels; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }


    out = new jack_default_audio_sample_t*;

    jack_activate(this->client);

    // connect outputs
    jack_connect (client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect (client, jack_port_name(output_port[1]), "system:playback_2");

    // run forever
    sleep (-1);


}


int SubtractiveExample::process(jack_nframes_t nframes)
{


    // -------------------------------------------------
    // process OSC input

    if(mode.compare("OSC") == 0)
    {
        double tmpAtt    = oscman->get_attack();
        gain_env->set_attack(tmpAtt);
        cutoff_env->set_attack(tmpAtt);

        double tmpRel      = oscman->get_release();
        gain_env->set_release(tmpRel);
        cutoff_env->set_release(tmpRel);

        double tmpExpo = oscman->get_expo();
        cutoff_env->set_exponent(tmpExpo);

        double tmpPW       = oscman->get_pulsewidth();
        square->pulsewidth(tmpPW);



        double tmpVel = oscman->get_velocity();
        double tmpFre = oscman->get_frequency();

        if(tmpVel>0 && tmpFre > 0)
        {

            square->frequency(tmpFre);

            gain_env->trigger();
            cutoff_env->trigger();


        }
    }

    // -------------------------------------------------
    // process MIDI


    if(mode.compare("MIDI")==0)
    {

        //convert pointer to reference
        std::vector<noteMessage>& m1 = *midiman->get_noteMessages();

        for (const auto i:m1)
        {
            if(i.velocity > 0)
            {
                double tmpFre = 440.0 * std::pow(2, ((double) i.noteNumber -69) / 12.0) ;

                square->frequency(tmpFre);

                gain_env->trigger();
                cutoff_env->trigger();
            }
        }

        //convert pointer to reference
        std::vector<ctlMessage>& m2 = *midiman->get_ctlMessages();

        for (const auto i:m2)
        {


            if(i.ctlNumber == yaml_manager->return_ctl1())
            {

                double tmpAtt = std::max(0.01,0.4*((double) i.value / 127.0));

                std::cout << tmpAtt << std::endl;

                gain_env->set_attack(tmpAtt);
                cutoff_env->set_attack(tmpAtt);
            }

            if(i.ctlNumber == yaml_manager->return_ctl2())
            {
                double tmpRel = std::max(0.01,5*((double) i.value / 127.0));
                std::cout << tmpRel << std::endl;
                gain_env->set_release(tmpRel);
                cutoff_env->set_release(tmpRel);
            }


            if(i.ctlNumber == yaml_manager->return_ctl3())
            {
                double tmpVal = std::max(1.0,20*((double) i.value / 127.0));
                cutoff_env->set_exponent(tmpVal);
            }


            if(i.ctlNumber == yaml_manager->return_ctl4())
            {
                double tmpVal = (double) i.value / 127.0;
                square->pulsewidth(tmpVal);
            }
        }

        // after processing, we flush all the messages
        midiman->flush_all_messages();

    }


    // -------------------------------------------------
    // get output buffers
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }

    // -------------------------------------------------
    // loop over all buffer samples

    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {

        // get oscillator value for this sample
        double  tmpVal = square->getNextSample();

        // filter it
        double tmpOut = filter->process(tmpVal);

        // apply envelopes
        double G = 0;
        if(gain_env->is_active()==true)
        {
            G = gain_env->get_next_value();
            double C = cutoff_env->get_next_value()*5000.0;
            filter->setBiquad(bq_type_lowpass, C / fs, 0.5, 0);
        }


        // write all input samples to output
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            out[chanCNT][sampCNT] = tmpOut * G ;
        }

    }
    return 0;
}


int SubtractiveExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<SubtractiveExample*>(object)->process(x);
}
