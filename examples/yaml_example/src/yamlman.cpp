/**
 * \file yamlman.cpp
 * \class YamlMan
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 */

#include "yamlman.h"

YamlMan::YamlMan(std::string filepath)
{

    cout << "Loading config from YAML file: " << filepath << endl;

    YAML::Node config = YAML::LoadFile(filepath);

    // access YAML nodes:
    param1 = config["param1"].as<std::string>();
    param2 = config["param2"].as<int>();
    param3 = config["param3"].as<double>();

}


std::string YamlMan::return_param1()
{
    return param1;
}

int YamlMan::return_param2()
{
    return param2;
}

double YamlMan::return_param3()
{
    return param3;
}
