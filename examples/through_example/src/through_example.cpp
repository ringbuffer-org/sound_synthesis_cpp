/**
* \file gain_example.cpp
* \class ThroughExample
*
* \brief Simple example, passing the input to the output
*        with gain modification through OSC.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/18 $
*
*/

#include"through_example.h"


using std::cout;
using std::endl;


ThroughExample::ThroughExample(){

    cout << "Starting Jack Client!" << endl;

    this->client = jack_client_open("Through_Example", JackNullOption, &status, NULL);

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



int ThroughExample::process(jack_nframes_t nframes)
{



    // get input buffers
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
        in[i]  = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->input_port[i], jack_get_buffer_size(client));
    }

    // write all input samples to output
    for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
    {
        for(int sampCNT=0; sampCNT<nframes; sampCNT++)
        {
            out[chanCNT][sampCNT] = in[chanCNT][sampCNT];
        }
    }

    return 0;
}


int ThroughExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<ThroughExample*>(object)->process(x);
}
