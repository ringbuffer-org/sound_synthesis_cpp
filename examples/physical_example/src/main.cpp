/**
* \file main.cpp
*
* \brief Just the main file ...
*
* \author Henrik von Coler
*
* \date 2019-04-15
*
*/

#include"yamlman.h"
#include"physical_example.h"


#include<iostream>
#include<stdlib.h>
#include<unistd.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]){

    if (argc < 3)
        cout << "Need config file to start!" << endl;

    else{

        // process command line arguments
        std::string configfile;
        int id;
        std::string mode;

        for (int i = 1; i < argc; i++)
        {
            if (i + 1 != argc)
            {
                if (strcmp(argv[i], "-c") == 0)
                {
                    configfile = argv[i + 1];
                    i++;
                }

                if (strcmp(argv[i], "-ID") == 0)
                {
                    id = atoi(argv[i + 1]);
                    i++;
                }

                if (strcmp(argv[i], "-m") == 0)
                {
                    mode = argv[i + 1];
                    i++;
                }
            }
        }

        // initialize objects
        YamlMan *yaml_manager = new YamlMan(configfile);
        PhysicalExample *t = new PhysicalExample(yaml_manager, id, mode);
    }
}
