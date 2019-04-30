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

    typedef struct  {
        int byte1	      = -1;
        int byte2             = -1;
        double byte3          = -1;
        bool hasBeenProcessed = false;

    }midiMessage;

    MidiMan(int device_ID);
    ~MidiMan();

    std::vector<std::string> returnAllNames();

    void updateMidiMessages(void *port_buf);
    void parseMidiMessages();

    void addNoteOnMessage(int in[3]);
    std::vector<noteMessage> getNoteOnMessages();
    void clearNoteOnMessages();

    void addNoteOffMessage(int in[3]);
    std::vector<noteMessage> getNoteOffMessages();
    void clearNoteOffMessages();

    void eraseNoteOnMessage(int position);

    void addFaderMessage(ctlMessage m);

    void markOnMessageProcessed(int pos);
    void markOffMessageProcessed(int pos);

    void flushProcessedMessages();

    ctlMessage getLastFaderMessage();

    int getNumFaderMessages();

    static void finish(int ignore);

    midiMessage get_midi_messages();

    void setVerbose();



private:

    // rtmidi
    static bool done;

    RtMidiIn *midiin;
    int nBytes, i;
    double stamp;
    bool isVerbose = true;

    std::vector<int>   val;

    noteMessage *tmpNote;

    void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData );


};







#endif // MIDIMAN_H

