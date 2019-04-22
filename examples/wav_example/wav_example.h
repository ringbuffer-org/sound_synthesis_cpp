/**
* \file GainExample.h
* \class GainExample
*
* \brief Simple example, passing the input to the output
*        with gain modification through OSC.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/18 $
*
*/



#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>

#include<jack/jack.h>

#include"oscman.h"
#include"singlesample.h"

using std::cout;
using std::endl;


class WavExample{

private:

    SingleSample *sample;

    int fs        = 0;

    int nOutputs  = 2;

    int nChannels;

    const char **ports;

    jack_client_t   *client;
    jack_status_t   status;

    jack_port_t     **output_port;

    /// The OSC manager object
    OscMan *oscman;

    ///
    /// \brief process
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
    ///        Default constructor!
    WavExample(std::string filename);

};





