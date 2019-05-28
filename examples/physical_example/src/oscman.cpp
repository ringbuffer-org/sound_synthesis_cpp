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

    // set initial values


    // used for triggering notes

    position    = 0.5;
    shift       = 1.0;


    triggered = false;

    try
    {
        st = new lo::ServerThread(port);
    }
    catch (int e)
    {
        std::cout << "Possibly a bad port!" << std::endl;
    }

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_1(), "ff", trigger_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_2(), "f", gain_callback, this);

    st->start();

    std::cout << "Started OSC Server!" << std::endl;
}




int OscMan::trigger_callback(const char *path, const char *types, lo_arg ** argv,
                             int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Received excitation at position: " << argv[0]->f << " with shift: " << argv[1]->f << std::endl;

    statCast->position  = argv[0]->f;
    statCast->shift = argv[1]->f;

    statCast->triggered = true;

}


int OscMan::gain_callback(const char *path, const char *types, lo_arg ** argv,
                             int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed gain to: " << argv[0]->f <<  std::endl;

    statCast->gain  = argv[0]->f;

}



double OscMan::get_shift()
{
    return shift;
}


double OscMan::get_position()
{
    return position;
}


double OscMan::get_gain()
{
    return gain;
}

bool OscMan::is_triggered()
{
    bool t = triggered;
    triggered = false;
    return t;
}




