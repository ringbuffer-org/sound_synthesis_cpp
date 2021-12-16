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

    std::string param1;

    int param2;

    double param3;

public:

    /// \brief YamlMan
    ///         Constructor
    /// \param filepath The path of the config file (*.yml)
    YamlMan(std::string filepath);

    string return_param1();

    int return_param2();

    double return_param3();

};

#endif // YAMLMAN_H
