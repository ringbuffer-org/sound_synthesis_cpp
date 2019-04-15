/**
 * \file yamlman.h
 * \class YamlMan
 *
 * \brief Class which parses YAML files for parameters.
 *
 * YamlMan also keeps the parameter settings and offers
 * getters for each, individually.
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 */

#ifndef YAMLMAN_H
#define YAMLMAN_H

#include<yaml-cpp/yaml.h>
#include<iostream>
#include<string.h>

using std::cout;
using std::endl;
using std::string;

class YamlMan
{

private:


    /// \brief port
    /// The OSC port to be used for receiving messages
    int port;

    /// \brief path
    /// The OSC path used for the parameter
    std::string path;

public:

    /// \brief YamlMan
    ///         Constructor
    /// \param filepath The path of the config file (*.yml)
    YamlMan(std::string filepath);

    /// \brief return_port
    /// \return The OSC port to be used
    int return_port();

    /// \brief return_path
    ///         Returns the OSC path used
    ///         to change the gain of the signal.
    ///
    /// \return The OSC path.
    string return_path();

};

#endif // YAMLMAN_H
