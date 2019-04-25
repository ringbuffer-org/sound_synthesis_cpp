/**
*
* \file  granular_example.cpp
* \class GranularExample
*
* \brief Read a wave file and play it back in a granular style.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/23 $
*
*/

#include"granular_example.h"

using std::cout;
using std::endl;

GranularExample::GranularExample(std::string filename, int win_size, int nWindows)
{

    // creating an OSC manager instance
    try{
        oscman = new OscMan(5111);
    }
    catch(int e)
    {
        cout << "Bad Port!";
    }

    this->client = jack_client_open("Grain_Example", JackNullOption, &status, NULL);

    fs = jack_get_sample_rate(client);


    // create a ne grain player
    grainer = new GrainPlayer(filename, fs, win_size, nWindows);

    nChannels = 1;

    // -----------------------------------------------------------------------
    // standard JACK startup:
    // -----------------------------------------------------------------------

    cout << "Starting Jack Client! " << endl;

    jack_set_process_callback(this->client, this->callback_process, this);

    output_port = new jack_port_t*[nChannels];

    for (int i=0; i<nOutputs; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }

    jack_activate(this->client);

    jack_connect(client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect(client, jack_port_name(output_port[1]), "system:playback_2");

    // run forever
    sleep(-1);

    // -----------------------------------------------------------------------


}


int GranularExample::process (jack_nframes_t nframes)
{


    // allocate output buffer array
    jack_default_audio_sample_t **out = new jack_default_audio_sample_t*[nChannels];
    for ( int i=0 ; i<nChannels; i++)
    {
        // buffer size can change
        out[i] = (jack_default_audio_sample_t *) jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }

    grainer->set_relative_distance(oscman->get_speed());

    // loop over all samples of output buffer
    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {
        out[0][sampCNT] = grainer->get_sample();
    }
    return 0;
}


int GranularExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<GranularExample*>(object)->process(x);
}

