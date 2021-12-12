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

    ///
    /// \brief path3
    /// The OSC path used for the third parameter
    std::string path3;

    ///
    /// \brief path4
    /// The OSC path used for the fourth parameter
    std::string path4;


    int ctl1;
    int ctl2;
    int ctl3;
    int ctl4;

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


    ///
    /// \brief return_path_3
    /// \return
    ///  getter for path #3
    string return_path_3();

    ///
    /// \brief return_path_4
    /// \return
    ///  getter for path #4
    string return_path_4();


    int return_ctl1();

    int return_ctl2();

    int return_ctl3();

    int return_ctl4();
};

#endif // YAMLMAN_H
