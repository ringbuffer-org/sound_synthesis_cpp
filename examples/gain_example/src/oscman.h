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

#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include<vector>
#include<string>
#include<iostream>

class OscMan
{

private:


    /// the IP port to be opened
    int port = 6666;

    ///
    lo::ServerThread *st;

    /// The actual gain value
    double gain;

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
    OscMan(int port);

    ///
    /// \brief OscMan::get_gain
    /// \return the gain value [double]
    ///
    double get_gain();


};

#endif
