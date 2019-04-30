#include "midiman.h"

bool MidiMan::done;

MidiMan::MidiMan(int device_ID)
{


    // rtmidid intit
    midiin = new RtMidiIn(RtMidiIn::Api::UNSPECIFIED ,std::string("RtMidi Input Client"),(unsigned int) 100);

    //
    unsigned int nPorts = midiin->getPortCount();

    midiin->openPort(device_ID);

    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );

    done = false;

}



void MidiMan::setVerbose()
{
    isVerbose = true;

}

MidiMan::midiMessage MidiMan::get_midi_messages()
{

   MidiMan::midiMessage mm;

    std::vector<unsigned char>  a;

    int nBytes = 1;

    // this is kind of a dirty workaroud -
    // we loop over all in-massages and take the last one:
    while(nBytes>0)
    {

        midiin->getMessage(&a);

        nBytes = a.size();

        // only do something if bytes are received
        if(nBytes!=0)
        {

            // only give feedback if 'verbose-mode' is active
            if(isVerbose == true  )
            {
                std::cout << "Received " << nBytes << " Bytes: " ;


                for (int i=0; i<nBytes; i++ )
                    std::cout <<  i << " = " << (int)a[i] << " -- " ;

                std::cout <<  std::endl;

            }

            mm.byte1 = a[0];
            mm.byte2 = a[1];
            mm.byte3 = a[2];

        }

    }

    return mm;
}

void MidiMan::flushProcessedMessages()
{

    val.clear();


}





