/**
 * \file oscman.h
 * \class OscMan
 *
 * \brief Class which parses the incoming OSC messages.
 *
 * \author Henrik von Coler
 *
 * \date 2019/03/18$
 *
 */

#ifndef OSCMAN_H
#define OSCMAN_H


// works with 'self built'

#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include "yamlman.h"

#include<iostream>
#include<vector>
#include<string>


class OscMan
{

private:



    /// the IP port to be opened
    int port;

    ///
    lo::ServerThread *st;

    /// The actual shift value
    double shift;
    /// The master gain value
    double gain;

    ///
    ////// \brief OscMan::shift_callback
    ////// \param path
    ////// \param types
    ////// \param argv
    ////// \param argc
    ////// \param data
    ////// \param user_data
    ////// \return
    static int shift_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

    ///
    ////// \brief OscMan::gain_callback
    ////// \param path
    ////// \param types
    ////// \param argv
    ////// \param argc
    ////// \param data
    ////// \param user_data
    ////// \return
    static int gain_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


public:


    ///
    /// \brief OscMan::OscMan
    ///         The constructor
    /// \param yaml_manager
    ///
    OscMan(YamlMan *yaml_manager);

    ///
    /// \brief OscMan::get_shift
    /// \return the shift value [double]
    ///
    double get_shift();

    ///
    /// \brief get_gain
    /// \return the master gain
    ///
    double get_gain();


};

#endif
