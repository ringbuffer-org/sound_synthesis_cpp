#include "yamlman.h"

YamlMan::YamlMan(std::string filepath)
{

    cout << "Loading config from YAML file: " << filepath << endl;

    YAML::Node config = YAML::LoadFile(filepath);

    port = config["port"].as<int>();

    path = config["path"].as<std::string>();

}


int YamlMan::return_port()
{

    return port;

}

std::string YamlMan::return_path()
{

    return path;

}


