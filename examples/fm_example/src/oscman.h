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

    /// a server thread
    lo::ServerThread *st;


    /// the carrier frequency
    double f_c;

    /// the modulation frequency
    double f_m;

    /// the modulation index
    double idx;

    /// the master gain
    double gain;

    // -------------------------------------------------------------------------
    // All the callback functions
    // -------------------------------------------------------------------------

    static int mod_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


    static int car_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


    static int idx_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

    static int gain_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);



    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

public:


    ///
    /// \brief OscMan
    /// constructor
    /// \param yaml_manager
    ///
    OscMan(YamlMan *yaml_manager);

    ///
    /// \brief get_carrier
    /// \return the carrier frequency
    double get_carrier();

    ///
    /// \brief get_mod
    /// \return th modulation frequency
    ///
    double get_mod();

    ///
    /// \brief get_idx
    /// \return the modulation index
    ///
    double get_idx();

    ///
    /// \brief get_gain
    /// \return the master gain
    ///
    double get_gain();

};

#endif
