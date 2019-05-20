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
    L_att         = 0.05;
    L_rel         = 1;
    pulsewitdh    = 0.5;
    expo          = 2;

    // used for triggering notes
    velocity  = 0;
    frequency = 0;



    try
    {
        st = new lo::ServerThread(port);
    }
    catch (int e)
    {
        std::cout << "Possibly a bad port!" << std::endl;
    }

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_1(), "f", att_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_2(), "f", rel_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_3(), "f", pulsewidth_callback, this);

    // Add the example handler to the server!
    st->add_method(yaml_manager->return_path_4(), "f", expo_callback, this);

    // Add the example handler to the server!
    st->add_method("/trigger", "ff", trigger_callback, this);


    st->start();

    std::cout << "Started OSC Server!" << std::endl;
}


int OscMan::att_callback(const char *path, const char *types, lo_arg ** argv,
                         int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    // allow values greater 0.001
    double in = argv[0]->f;
    in = std::max(0.001,in);

    std::cout << "Changed attack to: " << in << std::endl;

    statCast->L_att = in;

}


int OscMan::rel_callback(const char *path, const char *types, lo_arg ** argv,
                         int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);


    // allow values greater 0.001
    double in = argv[0]->f;
    in = std::max(0.001,in);


    std::cout << "Changed release to: " << argv[0]->f << std::endl;

    statCast->L_rel = argv[0]->f;

}


int OscMan::pulsewidth_callback(const char *path, const char *types, lo_arg ** argv,
                                int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    double in = argv[0]->f;

    // limit between 0.01 and 0.99
    in = std::max(0.01,in);
    in = std::min(0.99,in);

    std::cout << "Changed pulsewidth to: "  << in << std::endl;

    statCast->pulsewitdh = in;

}


int OscMan::expo_callback(const char *path, const char *types, lo_arg ** argv,
                          int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    // allow values greater 0.001
    double in = argv[0]->f;
    in = std::max(1.0,in);

    std::cout << "Changed release exponent to: " << in << std::endl;

    statCast->expo = in;

}


int OscMan::trigger_callback(const char *path, const char *types, lo_arg ** argv,
                             int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Received note with amplitude: " << argv[0]->f << " and frequency: " << argv[1]->f << std::endl;

    statCast->velocity  = argv[0]->f;
    statCast->frequency = argv[1]->f;

}


double OscMan::get_release()
{
    return L_rel;
}


double OscMan::get_attack()
{
    return L_att;
}


double OscMan::get_pulsewidth()
{
    return pulsewitdh;
}


double OscMan::get_expo()
{
    return expo;
}

double OscMan::get_velocity()
{
    double tmp = velocity;
    velocity   = 0;

    return tmp;
}

double OscMan::get_frequency()
{
    double tmp = frequency;
    frequency   = 0;

    return tmp;
}
