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

    /// \brief path1
    /// The OSC path used for the first parameter
    std::string path1;

    /// \brief path2
    /// The OSC path used for the second parameter
    std::string path2;


public:

    /// \brief YamlMan
    ///         Constructor
    /// \param filepath The path of the config file (*.yml)
    YamlMan(std::string filepath);

    /// \brief return_port
    /// \return The OSC port to be used
    int return_port();

    /// \brief return_path_1
    ///
    /// \return getter for path #1
    string return_path_1();

    /// \brief return_path_2
    ///
    /// \return getter for path #2
    string return_path_2();

};

#endif // YAMLMAN_H
