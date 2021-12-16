/**
* \file gain_example.h
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
#include"sinefolder.h"
#include"tangentshaper.h"
#include"transferfunction.h"


using std::cout;
using std::endl;



class Waveshaper{

private:

    /// \brief nChannels
    ///         the number of audio channels @todo (should not be hard-coded)
    int nChannels = 2;

    /// \brief client
    ///         the jack client, obviously
    jack_client_t   *client;

    /// \brief status
    ///         gets the status from the jack server
    jack_status_t   status;

    /// \brief input_port
    /// the jack input ports
    jack_port_t     **input_port;

    /// \brief output_port
    /// the jack output ports
    jack_port_t     **output_port;

    /// \brief in
    ///
    /// \brief out
    jack_default_audio_sample_t **in, **out;


    ///  The OSC manager object
    OscMan *oscman;


    TransferFunction *trans_fun;

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
    Waveshaper(YamlMan *yaml_manager);

};





