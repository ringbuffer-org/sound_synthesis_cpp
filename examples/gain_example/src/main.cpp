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

#include"gain_example.h"
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>

using std::cout;
using std::endl;


int main(int argc, char *argv[]){

  int port;

    if (argc < 3)
        cout << "Need port parameter to start!" << endl;

    else{

              for (int i = 1; i < argc; i++)
              {
                  if (i + 1 != argc)
                  {
                      if (strcmp(argv[i], "-p") == 0)
                      {
                            // convert string argument to integer
                            port = atoi(argv[i + 1]);

                          i++;
                      }
                  }
                }

        GainExample *t = new GainExample(port);
    }
}
