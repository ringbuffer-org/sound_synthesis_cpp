/**
 * \class MidiMan
 *
 *
 * \brief Class which parses and stores the incoming MIDI messages.
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: von_coler@tu-berlin.de
 *
 *
 */

#ifndef MIDIMAN_H
#define MIDIMAN_H

#include <iostream>
#include <cstdlib>
#include <signal.h>

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <jack/midiport.h>
#include <rtmidi/RtMidi.h>

#include "datatypes.h"



class MidiMan
{



public:
    ///
    /// \brief a midi message
    typedef struct  {
        int byte1	      = -1;
        int byte2             = -1;
        double byte3          = -1;
        bool hasBeenProcessed = false;

    }midiMessage;

    MidiMan(int ID);
    ~MidiMan();



    std::vector<noteMessage> *get_noteMessages();

     std::vector<ctlMessage> *get_ctlMessages();

    void flush_all_messages();

    void setVerbose();



private:


    RtMidiIn *midiin;

    bool isVerbose = true;

    std::vector<noteMessage> note_messages;

    std::vector<ctlMessage>  ctl_messages;

    static void main_callback( double deltatime, std::vector< unsigned char > *message, void *userData );

};







#endif // MIDIMAN_H

