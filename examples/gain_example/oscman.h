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

#include<iostream>
#include<vector>
#include<string>


class OscMan
{

private:



    /// the port to be opened
    int port;

    lo::ServerThread *st;

    double gain;


    static int gain_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


public:

    OscMan(int p);

    double get_gain();


};

#endif
