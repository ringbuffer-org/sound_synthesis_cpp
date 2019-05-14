am_example {#mainpage}
=======================

# BRIEF

This example uses amplitude modulation
on the input signal of the audio interface.
The carrier frequency can be controlled
using OSC.


# Libraries

The following libraries are used within this project:

* jack
* YAML
* LIBLO

# OSC server config

The file 'config.yml' is read by 
gain_example in order to set the port
and the OSC path used to set the gain.