/**
*
* \file physical_example.cpp
* \class PhysicalExample
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/


#include"physical_example.h"


using std::cout;
using std::endl;


PhysicalExample::PhysicalExample(YamlMan *ym, int ID, string m){


    cout << "Starting Jack Client!" << endl;
    this->client = jack_client_open("Subtractive_Example", JackNullOption, &status, NULL);
    fs = jack_get_sample_rate(client);

    mode = m;

    yaml_manager = ym;



    // allocate a midi manager
    if(mode.compare("MIDI")==0)
        midiman = new MidiMan(ID);




    // creating an OSC manager instance
    if(mode.compare("OSC")==0)
    oscman = new OscMan(yaml_manager);

    // create new waveguide object
    waveguide_string = new WaveGuide(100, 3);
    waveguide_string->set_gain(0.0);

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


int PhysicalExample::process(jack_nframes_t nframes)
{




    // -------------------------------------------------
    // process OSC input

    if(mode.compare("OSC") == 0)
    {

        double GAIN = oscman->get_gain();
        waveguide_string->set_gain(GAIN);

        double tmpShift = oscman->get_shift();
        double tmpPos   = oscman->get_position();
        bool t          = oscman->is_triggered();
        if(t==true)
        {
            waveguide_string->excite(tmpPos, tmpShift);
        }
    }

    // -------------------------------------------------
    // process MIDI


    if(mode.compare("MIDI")==0)
    {

        // MIDI is not implemented in this example

        // after processing - flush all the messages
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

        // shift waveguide
        waveguide_string->frac_shift();

        // get output value
        double tmpOut = waveguide_string->getOutputAt(10);

        // write all input samples to output
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            out[chanCNT][sampCNT] = tmpOut;
        }

    }
    return 0;
}


int PhysicalExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<PhysicalExample*>(object)->process(x);
}
