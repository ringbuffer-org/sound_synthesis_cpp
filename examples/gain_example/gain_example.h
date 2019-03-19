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

#include<iostream>
#include<stdlib.h>
#include<unistd.h>

#include<jack/jack.h>

#include"oscman.h"


using std::cout;
using std::endl;



class GainExample{

private:

    int nChannels = 2;

    const char **ports;

    jack_client_t   *client;
    jack_status_t   status;

    jack_port_t     **input_port;
    jack_port_t     **output_port;

    jack_default_audio_sample_t **in, **out;


    /// The OSC manager object
    OscMan *oscman;

    ///
    /// \brief process
    /// \param nframes
    /// \return
    ///
    int process (jack_nframes_t nframes);

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
    GainExample();

};





