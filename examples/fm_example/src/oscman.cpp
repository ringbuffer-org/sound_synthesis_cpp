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

    // set defaults
    f_m  = 100;
    f_c  = 200;
    idx  = 10;
    gain = 1;

    try
    {
        st = new lo::ServerThread(port);
    }
    catch (int e)
    {
        std::cout << "Possibly a bad port!" << std::endl;
    }

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_1(), "f", mod_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_2(), "f", car_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_3(), "f", idx_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_4(), "f", gain_callback, this);

    st->start();

    std::cout << "Started OSC Server!" << std::endl;
}


int OscMan::mod_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed modulator to: " << argv[0]->f << std::endl;

    statCast->f_m = argv[0]->f;

}


int OscMan::car_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed carrier to: " << argv[0]->f << std::endl;

    statCast->f_c = argv[0]->f;

}



int OscMan::idx_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed index to: " << argv[0]->f << std::endl;

    statCast->idx = argv[0]->f;

}



int OscMan::gain_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed gain to: " << argv[0]->f << std::endl;

    statCast->gain = argv[0]->f;

}


double OscMan::get_mod()
{
    return f_m;
}


double OscMan::get_carrier()
{
    return f_c;
}


double OscMan::get_idx()
{
    return idx;
}


double OscMan::get_gain()
{
    return gain;
}
