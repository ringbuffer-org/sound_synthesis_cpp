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


///
/// \brief OscMan::OscMan
/// \param p
///
OscMan::OscMan(int p)
{

    port = p;

    speed = 1.0;

    try
    {
        st = new lo::ServerThread(port);
    }
    catch (int e)
    {
        std::cout << "Possibly a bad port!" << std::endl;

    }

    // Add the example handler to the server!
    st->add_method("/speed", "f", speed_callback, this);

    st->start();

    std::cout << "Started OSC Server!" << std::endl;
}


///
////// \brief OscMan::gain_callback
////// \param path
////// \param types
////// \param argv
////// \param argc
////// \param data
////// \param user_data
////// \return
int OscMan::speed_callback(const char *path, const char *types, lo_arg ** argv,
int argc, void *data, void *user_data )
{


    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed playback speed to: " << argv[0]->f << std::endl;

    statCast->speed = argv[0]->f;

}


///
/// \brief OscMan::get_speed
/// \return
///
double OscMan::get_speed()
{
    return speed;
}


