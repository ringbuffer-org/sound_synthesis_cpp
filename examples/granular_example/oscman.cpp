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



OscMan::OscMan(int p)
{

    port  = p;

    speed = 0;

    st = new lo::ServerThread(port);

    if (st->is_valid())
    {

        // Add the example handler to the server!
        st->add_method("/speed", "f", speed_callback, this);

        st->start();

        std::cout << "Started OSC Server!" << std::endl;

    }
    else
        throw std::invalid_argument("OSC server not started - possibly a bad port!");
}


int OscMan::speed_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed playback speed to: " << argv[0]->f << std::endl;

    statCast->speed = argv[0]->f;

}



double OscMan::get_speed()
{
    return speed;
}


