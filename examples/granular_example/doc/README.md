granular__example {#mainpage}
=======================

# BRIEF

This example uses the SingleSample
class in comination with a TriangularWindow
class for a basic granular synthesis.

The playback speed (analysis window rate) can be
controlled using OSC. The OSC path
and port are hardcoded in the file
WavExample.cpp and oscman.cpp.

# Libraries

The following libraries are used within this project:

* JACK
* libsndfile
* liblo

# Usage

The binaray granular_example expects three
command line arguments:

- the wav file to read with the flag '-f'
- the grain size in samples '-l'
- the number of windows to be used '-n

```console
~/examples/granular_example $ ./granular_example -f ../../wav/ALF_8bitDRY.wav -l 1000 -n 4 
```
