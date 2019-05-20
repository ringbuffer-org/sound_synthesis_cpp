#include "midiman.h"



MidiMan::MidiMan(int ID)
{

    // rtmidid intit
    midiin = new RtMidiIn(RtMidiIn::Api::UNSPECIFIED ,std::string("RtMidi Input Client"),(unsigned int) 100);

    midiin->openPort(ID);

    midiin->setCallback( &main_callback, this);



    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );


}



void MidiMan::setVerbose()
{
    isVerbose = true;
}


void MidiMan::main_callback(double deltatime, std::vector< unsigned char > *message, void *userData )
{

    // static cast to this object
    MidiMan* statCast = static_cast<MidiMan*>(userData);

    // is this a note message?
    int byte0 = (int)message->at(0);
    if(byte0 == 144)
    {
        if(statCast->isVerbose==true)
        std::cout << "Received MIDI note message! " << "(" <<  (int)message->at(1) << "-" <<  (int)message->at(2) << ")" << std::endl;

        noteMessage tmpMes;
        tmpMes.noteNumber = (int)message->at(1);
        tmpMes.velocity   = (int)message->at(2);

        statCast->note_messages.push_back(tmpMes);

    }

    if(byte0 == 176)
    {
        if(statCast->isVerbose==true)
        std::cout << "Received MIDI control message! " << "(" <<  (int)message->at(1) << "-" <<  (int)message->at(2) << ")" << std::endl;

        ctlMessage tmpMes;
        tmpMes.ctlNumber = (int)message->at(1);
        tmpMes.value     = (int)message->at(2);

        statCast->ctl_messages.push_back(tmpMes);

    }
}


std::vector<noteMessage>* MidiMan::get_noteMessages()
{
    return &note_messages;
}


std::vector<ctlMessage> *MidiMan::get_ctlMessages()
{
    return &ctl_messages;
}


void MidiMan::flush_all_messages()
{
    note_messages.clear();
    ctl_messages.clear();
}





