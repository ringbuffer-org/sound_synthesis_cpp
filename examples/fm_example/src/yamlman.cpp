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

    // read values
    port = config["port"].as<int>();
    path1 = config["path1"].as<std::string>();
    path2 = config["path2"].as<std::string>();
    path3 = config["path3"].as<std::string>();
    path4 = config["path4"].as<std::string>();

}


int YamlMan::return_port()
{
    return port;
}

std::string YamlMan::return_path_1()
{
    return path1;
}

std::string YamlMan::return_path_2()
{
    return path2;
}

std::string YamlMan::return_path_3()
{
    return path3;
}

std::string YamlMan::return_path_4()
{
    return path4;
}


