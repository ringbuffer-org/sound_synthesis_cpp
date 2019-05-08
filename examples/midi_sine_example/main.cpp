

#include <iostream>
#include "midi_sine_example.h"



using std::cout;
using std::endl;

int main(int argc, char *argv[]){

    // process command line arguments
    int id;
    int n;
    for (int i = 1; i < argc; i++)
    {
        if (i + 1 != argc)
        {

            if (strcmp(argv[i], "-ID") == 0)
            {
                id = atoi(argv[i + 1]);
                i++;
            }

            if (strcmp(argv[i], "-n") == 0)
            {
                n = atoi(argv[i + 1]);
                i++;
            }

        }
    }

   MidiSineExample  * m = new MidiSineExample(id, n);

}
