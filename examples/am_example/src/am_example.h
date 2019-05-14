/**
* \file am_example.h
* \class AmExample
*
* \brief Simple example, passing the input to the output
*        with amplitude modulation through OSC.
*
* \author Henrik von Coler
*
* \date $Date: 2019/05/14 $
*
*/

#include<iostream>
#include<stdlib.h>
#include<unistd.h>

#include<jack/jack.h>

#include"yamlman.h"
#include"oscman.h"
#include"sinusoid.h"


using std::cout;
using std::endl;



class AmExample{

private:

    ///
    /// \brief yaml_manager
    ///        is used for reading the config file
    YamlMan *yaml_manager;

    ///
    /// \brief fs
    /// the jack server sampling rate
    int fs;

    ///
    /// \brief carrier
    /// the carrier signal for the AM
    Sinusoid *carrier;

    ///
    /// \brief nChannels
    ///         the number of audio channels @todo (should not be hard-coded)
    int nChannels = 2;

    ///
    /// \brief client
    ///         the jack client, obviously
    jack_client_t   *client;

    ///
    /// \brief status
    ///         gets the status from the jack server
    jack_status_t   status;


    ///
    /// \brief input_port
    /// the jack input ports
    jack_port_t     **input_port;

    ///
    /// \brief output_port
    /// the jack output ports
    jack_port_t     **output_port;

    ///
    /// \brief in
    ///
    /// \brief out
    jack_default_audio_sample_t **in, **out;


    ///  The OSC manager object
    OscMan *oscman;

    ///
    /// \brief process
    /// \param nframes
    /// \return
    ///
    int process (jack_nframes_t nframes);

    ///
    /// \brief callback_process
    ///         is used to access the members of this
    ///         class in the static mode
    /// \param x number of samples in the buffer
    /// \param object void pointer
    /// \return
    ///
    static int callback_process(jack_nframes_t x, void* object);

public:

    ///
    /// \brief GainExample
    ///         the constructor
    /// \param yaml_manager
    ///
    AmExample(YamlMan *yaml_manager);

};





