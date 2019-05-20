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
#include <algorithm>

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
    double L_att;

    /// the modulation frequency
    double L_rel;

    /// the modulation index
    double pulsewitdh;

    ///
    double expo;

    double velocity;
    double frequency;

    // -------------------------------------------------------------------------
    // All the callback functions
    // -------------------------------------------------------------------------

    static int att_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


    static int rel_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


    static int pulsewidth_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

    static int expo_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

    static int trigger_callback(const char *path, const char *types, lo_arg ** argv,
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
    double get_attack();


    ///
    double get_release();

    ///
    double get_pulsewidth();

    ///
    double get_expo();

    double get_velocity();

    double get_frequency();

};

#endif
