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

    double gain;
    double position;
    double shift;

    bool triggered;
    // -------------------------------------------------------------------------
    // All the callback functions
    // -------------------------------------------------------------------------


    static int trigger_callback(const char *path, const char *types, lo_arg ** argv,
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
    double get_shift();

    double get_position();

    double get_gain();

    bool is_triggered();

};

#endif
