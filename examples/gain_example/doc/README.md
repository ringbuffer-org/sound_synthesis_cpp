gain_example {#mainpage}
=======================

# BRIEF

This example introduces the basic
libraries and tools used in the
Sound Synthesis class. It passes
audio from the inputs to the outputs,
allowing to set the gain using an OSC
interface.

# Libraries

The following libraries are used within this project:

* jack
* YAML
* LIBLO

# OSC server config

The file 'config.yml' is read by 
gain_example in order to set the port
and the OSC path used to set the gain.