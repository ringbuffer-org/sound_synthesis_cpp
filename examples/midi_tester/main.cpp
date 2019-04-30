

#include <cstring>
#include <iostream>
#include <unistd.h>

#include "midiman.h"



using std::cout;
using std::endl;

int main(int argc, char *argv[]){

    int id;

    for (int i = 1; i < argc; i++)
    {
        if (i + 1 != argc)
        {

            if (strcmp(argv[i], "-ID") == 0)
            {
                id = atoi(argv[i + 1]);
                i++;
            }
        }
    }

   MidiMan  * m = new MidiMan(id);

   while(1)
   {
       m->get_midi_messages();
       m->flushProcessedMessages();
       usleep(50);
   }

}
