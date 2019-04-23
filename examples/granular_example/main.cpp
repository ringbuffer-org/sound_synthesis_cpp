/**
* \file main.cpp
*
* \brief Simple example for wav playback.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/22 $
*
*/


#include"granular_example.h"


using std::cout;
using std::endl;

int main(int argc, char *argv[]){

    std::string filename;
    int window_size;
    int nWindows;

    for (int i = 1; i < argc; i++)
    {
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-f") == 0)
            {
                filename = argv[i + 1];
                i++;
            }

            if (strcmp(argv[i], "-l") == 0)
            {
                window_size = atoi(argv[i + 1]);
                i++;
            }

            if (strcmp(argv[i], "-n") == 0)
            {
                nWindows = atoi(argv[i + 1]);
                i++;
            }
        }
    }

    GranularExample * t = new GranularExample(filename, window_size, nWindows);

}
