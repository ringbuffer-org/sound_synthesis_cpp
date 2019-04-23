wav_example {#mainpage}
=======================

# BRIEF

This example introduces the libsndfile
for reading a wav file and playing it
back in a loop. It is able to process
mono and stereo files.

The playback speed (resampling) can be
controlled using OSC. The OSC path
and port are hardcoded in the file
WavExample.cpp and oscman.cpp.

# Libraries

The following libraries are used within this project:

* JACK
* libsndfile
* liblo

# Usage

The binaray gain_example expects one command
line argument for wav file to read with the
flag '-f':

./gain_example -f ../wav/stereo_sine.wav