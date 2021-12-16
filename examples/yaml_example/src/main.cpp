

#include <cstring>
#include <iostream>
#include <unistd.h>

#include "yamlman.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]){

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

   YamlMan  * m = new YamlMan(configfile);

   cout << "main() got the following info from the config file:" << endl << endl;

   std::cout << "param1: " << m->return_param1() << endl;

   std::cout << "param2: " << m->return_param2() << endl;

   std::cout << "param3: " << m->return_param3() << endl;
}
