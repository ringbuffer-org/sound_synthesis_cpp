/**
 * \class YamlMan
 *
 *
 * \brief Class which parses YAML files for parameters.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 * Contact: von_coler@tu-berlin.de
 *
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

    ///
    /// \brief port
    /// The OSC port to be used for receiving messages
    ///
    int port;

    ///
    /// \brief path
    /// The OSC path used for the parameter
    ///
    std::string path;

public:

    YamlMan(std::string filepath);


    ///
    /// \brief return_port
    /// \return
    ///
    int return_port();

    ///
    /// \brief return_path
    /// \return
    ///
    string return_path();


};

#endif // YAMLMAN_H
