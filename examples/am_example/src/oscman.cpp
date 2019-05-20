/**
 * \file oscman.cpp
 * \class OscMan
 *
 * \brief Class which parses the incoming OSC messages.
 *
 * \author Henrik von Coler
 *
 * \date 2019/03/18
 *
 */

#include "oscman.h"



OscMan::OscMan(YamlMan *yaml_manager)
{

    port = yaml_manager->return_port();

    cout << "Receiving OSC on port: " << port << std::endl;

    shift = 1.0;
    gain = 1.0;

    try
    {
        st = new lo::ServerThread(port);
    }
    catch (int e)
    {
        std::cout << "Possibly a bad port!" << std::endl;
    }

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_1(), "f", shift_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_2(), "f", gain_callback, this);


    st->start();

    std::cout << "Started OSC Server!" << std::endl;
}


int OscMan::shift_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed shift to: " << argv[0]->f << std::endl;

    statCast->shift = argv[0]->f;

}

int OscMan::gain_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed gain to: " << argv[0]->f << std::endl;

    statCast->gain = argv[0]->f;

}

double OscMan::get_shift()
{
    return shift;
}

double OscMan::get_gain()
{
    return gain;
}
