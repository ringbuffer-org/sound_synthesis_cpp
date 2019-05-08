/**
*
* \file  midi_sine_example.cpp
* \class MidiSineExample
*
* \brief
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/23 $
*
*/

#include"midi_sine_example.h"

using std::cout;
using std::endl;

MidiSineExample::MidiSineExample(int ID, int nPart )
{

    nPartials = nPart;

    this->client = jack_client_open("MIDI_Sine_Example", JackNullOption, &status, NULL);

    fs = jack_get_sample_rate(client);

    // allocate array
    sines    = new Sinusoid[nPartials];

    // set initial values
    for (int i=0; i<nPartials; i++)
        sines[i].init(432 * (double) (i+1),0.1,1,fs);

    // create a ne grain player
    //grainer = new GrainPlayer(filename, fs, win_size, nWindows);

    nChannels = 2;



    /// allocate a new midi manager
    midiMan = new MidiMan(ID);

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


int MidiSineExample::process (jack_nframes_t nframes)
{


    // allocate output buffer array
    jack_default_audio_sample_t **out = new jack_default_audio_sample_t*[nChannels];
    for ( int i=0 ; i<nChannels; i++)
    {
        // buffer size can change
        out[i] = (jack_default_audio_sample_t *) jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }


    // process midi messages
    MidiMan::midiMessage m =  midiMan->get_rtmidi();

    // if a valid MIDI message is received
    if(m.byte3>=0)
    {

        double f0 = 0;

        // if it is a note message, use first data byte
        if(m.byte1 == 144)
            f0 = 440.0 * std::pow(2, ((double) m.byte2-69) / 12.0) ;

        // if it is a control message, use second data byte
        if(m.byte1 == 176)
            f0 = 440.0 * std::pow(2, ((double) m.byte3-69) / 12.0) ;

        // flush all messages
        midiMan->flushProcessedMessages();

        // set alll partial frequencies and amplitudes
        for (int i=0; i<nPartials; i++)
        {
            sines[i].amplitude(0.1 * 1/(i+1));
            sines[i].frequency(f0* (double) (i+1));
        }
    }

    // loop over all samples of output buffer
    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {

        // initialize samples
        out[0][sampCNT] = 0;
        out[1][sampCNT] = 0;


        // loop over all partials
        for (int i=0; i<nPartials; i++)
        {

            double tmpVal = sines[i].getNextSample();

            // take care of nyquist frequency
            if (sines[i].frequency()<fs/2)
            {
            out[0][sampCNT] += tmpVal;
            out[1][sampCNT] += tmpVal;
            }

        }

    }
    return 0;
}


int MidiSineExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<MidiSineExample*>(object)->process(x);
}

