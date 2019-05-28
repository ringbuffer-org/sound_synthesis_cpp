physical_example {#mainpage}
=======================

# BRIEF

This example uses a fractional waveguide for physical modeling.
It can be controlled by OSC (MIDI not implemented).

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


# the OSC paths used:
path1: "/trigger"
path2: "/gain"
```

# Start physical example

The binary expects three arguments:
-c 'path to config file'
-ID 'id of the MIDI controller used'
-m 'the mode used (MIDI or OSC)'

```
./physical_example -c config.yml -ID 1 -m OSC
```



