/**
*
* \file physical_example.cpp
* \class KarplusStrongExample
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/


#include"karplus_strong_example.h"


using std::cout;
using std::endl;


KarplusStrongExample::KarplusStrongExample(YamlMan *ym, int ID, string m){


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

    // allocate noise buffer
    noise_buffer = new double [l_buff];
    for (int i=0; i<l_buff; i++)
      noise_buffer[i]=0.0;

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


int KarplusStrongExample::process(jack_nframes_t nframes)
{

    // -------------------------------------------------
    // process OSC input

    if(mode.compare("OSC") == 0)
    {

        gain = oscman->get_gain();


        bool t          = oscman->is_triggered();

        if(t==true)
        {
          buffer_pos = 0;
          for(int i=0; i<=l_buff; i++)
            noise_buffer[i]=  rand() % 2 - 1;
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

        // write all input samples to output
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
          out[chanCNT][sampCNT]=noise_buffer[buffer_pos];
        }

        // smoothing the buffer
        double sum = 0;
        for(int smoothCNT=0; smoothCNT<l_smooth; smoothCNT++)
          {
            if(buffer_pos+smoothCNT<l_buff)
              sum+=noise_buffer[buffer_pos+smoothCNT];
            else
              sum+=noise_buffer[smoothCNT];
          }
          noise_buffer[buffer_pos] = gain*(sum/l_smooth);



        // increment buffer position
         buffer_pos++;
         if (buffer_pos>=l_buff)
          buffer_pos=0;
    }
    return 0;
}


int KarplusStrongExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<KarplusStrongExample*>(object)->process(x);
}
