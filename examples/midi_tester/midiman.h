/**
 * \class MidiMan
 *
 *
 * \brief Reduced version of the MIDI manager class
 *        for controller mappings.
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2019/04/30 14:16:20 $
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

    /// struct for holding a MIDI message
    typedef struct  {
        int byte1	      = -1;
        int byte2             = -1;
        double byte3          = -1;
        bool hasBeenProcessed = false;

    }midiMessage;

    ///
    /// \brief MidiMan
    /// \param device_ID
    ///
    MidiMan(int device_ID);

    ///
    ~MidiMan();

    ///
    /// \brief flushProcessedMessages
    ///
    void flushProcessedMessages();

    ///
    /// \brief get_midi_messages
    /// \return
    ///
    midiMessage get_midi_messages();

    ///
    /// \brief setVerbose
    ///
    void setVerbose();

private:

    ///
    /// \brief done
    ///
    static bool done;

    ///
    /// \brief midiin
    ///
    RtMidiIn *midiin;

    ///
    /// \brief isVerbose
    ///
    bool isVerbose = true;

    ///
    /// \brief val
    ///
    std::vector<int>   val;

};







#endif // MIDIMAN_H
