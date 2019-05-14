/**
* \file fm_example.cpp
* \class FmExample
*
* \author Henrik von Coler
*
* \date $Date: 2019/05/14 $
*
*/

#include"fm_example.h"


using std::cout;
using std::endl;


FmExample::FmExample(YamlMan *yaml_manager){

    // creating an OSC manager instance
    oscman = new OscMan(yaml_manager);

    cout << "Starting Jack Client!" << endl;
    this->client = jack_client_open("Gain_Example", JackNullOption, &status, NULL);

    fs = jack_get_sample_rate(client);


    carrier    = new Sinusoid();
    modulator  = new Sinusoid();
    carrier->init(100,1,0,fs);
    modulator->init(100,1,0,fs);

    // default modulation index
    IDX = 10;

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


int FmExample::process(jack_nframes_t nframes)
{

    // get the recent control
    // values from the OSC manager
    double tmpGain  = oscman->get_gain();
    double fm       = oscman->get_mod();
    double fc       = oscman->get_carrier();
    IDX             = oscman->get_idx();

    // set modulator frequency
    modulator->frequency(fm);

    // get output buffers
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }

    // loop over all buffer samples
    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {
        // apply FM
        carrier->frequency(fc + IDX * modulator->getNextSample());

        // get output value for this sample
        double  tmpVal = carrier->getNextSample();

        // write all input samples to output
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            out[chanCNT][sampCNT] = tmpVal * tmpGain;
        }
    }

    return 0;
}


int FmExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<FmExample*>(object)->process(x);
}
