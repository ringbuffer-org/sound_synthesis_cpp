/**
* \file am_example.cpp
* \class AmExample
*
* \brief Am example - modulates the audio
* input of the interface with a OSC controlled sinusoid.
*
* \author Henrik von Coler
*
* \date $Date: 2019/05/18 $
*
*/

#include"am_example.h"


using std::cout;
using std::endl;


AmExample::AmExample(YamlMan *yaml_manager){

    // creating an OSC manager instance
    oscman = new OscMan(yaml_manager);

    cout << "Starting Jack Client!" << endl;

    this->client = jack_client_open("Gain_Example", JackNullOption, &status, NULL);


    carrier    = new Sinusoid();

    fs = jack_get_sample_rate(client);

    carrier->init(100,1,0,fs);

    // connect the callback function
    jack_set_process_callback(this->client, this->callback_process, this);

    // allocate array
    input_port = new jack_port_t*[nChannels];
    for (int i=0; i<nChannels; i++)
    {
        std::string tmp_str = "input_" + std::to_string(i+1);
        input_port[i] = jack_port_register (client, tmp_str.c_str(),
                                            JACK_DEFAULT_AUDIO_TYPE,
                                            JackPortIsInput, 0);
    }


    output_port = new jack_port_t*[nChannels];
    for (int i=0; i<nChannels; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }


    out = new jack_default_audio_sample_t*;
    in  = new jack_default_audio_sample_t*;

    jack_activate(this->client);

    // connect inputs
    jack_connect (client, "system:capture_1", jack_port_name(input_port[0]));
    jack_connect (client, "system:capture_2", jack_port_name(input_port[1]));
    // connect outputs
    jack_connect (client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect (client, jack_port_name(output_port[1]), "system:playback_2");

    // run forever
    sleep (-1);


}



int AmExample::process(jack_nframes_t nframes)
{

    // get the recent carrier frequency
    // value from the OSC manager
    double tmpGain  = oscman->get_gain();
    double shift = oscman->get_shift();

    // set sinusoid parameter
    carrier->frequency(shift);

    // get input buffers
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
        in[i]  = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->input_port[i], jack_get_buffer_size(client));
    }

    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {
        // get carrier value for this sample
        double  tmpVal = carrier->getNextSample();

        // write all input samples to output
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            // apply AM
            out[chanCNT][sampCNT] = in[chanCNT][sampCNT] * tmpVal * tmpGain ;
        }
    }

    return 0;
}


int AmExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<AmExample*>(object)->process(x);
}
