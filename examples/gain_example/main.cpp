/**
* \file main.cpp
*
* \brief Just the main file ...
*
* \author Henrik von Coler
*
* \date $Date: 2019/04/15 $
*
*/

#include"yamlman.h"
#include"oscman.h"
#include"gain_example.h"


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

        for (int i = 1; i < argc; i++)
        {
            if (i + 1 != argc)
            {
                if (strcmp(argv[i], "-c") == 0)
                {
                    configfile = argv[i + 1];
                    i++;
                }
            }
        }



        YamlMan *yaml_manager = new YamlMan(configfile);

        /// initial ports from constructor created here.
        GainExample *t = new GainExample(yaml_manager);
    }
}
