/**
* \file wav_example.h
* \class WavExample
*
* \brief Simple example, passing the input to the output
*        with gain modification through OSC.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/18 $
*
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<jack/jack.h>

#include "oscman.h"
#include "grainplayer.h"

using std::cout;
using std::endl;

class GranularExample{

private:

    ///
    /// \brief sample
    ///
    GrainPlayer *grainer;

    ///
    /// \brief fs
    /// sample rate of the jack server
    int fs        = 0;

    ///
    /// \brief nOutputs
    ///  number off jack output ports
    int nOutputs  = 2;

    ///
    /// \brief nChannels
    /// number of channels in the sample
    int nChannels;

    ///
    /// \brief ports
    /// the jack output ports
    const char **ports;


    jack_client_t   *client;
    jack_status_t   status;

    jack_port_t  **output_port;

    /// The OSC manager object
    OscMan *oscman;

    ///
    /// \brief process
    ///     get the next buffer from the sample and playback
    /// \param nframes
    /// \return
    ///
    int process(jack_nframes_t nframes);

    ///
    /// \brief callback_process
    /// \param x
    /// \param object
    /// \return
    ///
    static int callback_process(jack_nframes_t x, void* object);

public:

    ///
    /// \brief GainExample
    ///        Constructor!
    GranularExample(std::string filename, int win_size, int nWindows);

};



