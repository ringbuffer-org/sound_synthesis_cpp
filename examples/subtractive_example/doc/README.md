subtractive_example {#mainpage}
=======================

# BRIEF

This example uses a square wave oscillator and a biquad filter.
It can be controlled by MIDI or OSC, depending on the command
line arguments.

# Libraries

The following libraries are used within this project:

* jack
* YAML
* LIBLO
* libRtMIDI

# OSC server config

The file 'config.yml' defines
the OSC and MIDI paths used
for controlling the synth:

```
# the OSC port:
port: 6666

# the midi controllers used:
ctl1: 14 
ctl2: 15
ctl3: 16
ctl4: 17

# the OSC paths used:
path1: "/attack"
path2: "/release" 
path3: "/pulsewidth"
path4: "/expo"
```

# Start subtractive example

The binary expects three arguments:
-c 'path to config file'
-ID 'id of the MIDI controller used'
-m 'the mode used (MIDI or OSC)'

```
./subtractive_example -c config.yml -ID 1 -m OSC
```



