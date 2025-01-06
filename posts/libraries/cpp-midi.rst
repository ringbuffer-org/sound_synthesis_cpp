.. title: Using MIDI with RtMidi
.. slug: cpp-midi
.. date: 2021-12-10 
.. tags:
.. category: cpp:libraries
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 2

Although the MIDI protocol is quite old and has several drawbacks, it is still widely used and is appropriate for many applications. Read the `MIDI section <http://hvc.berlin/Control/the-midi-protocol/>`_ in the Computer Music Basics for a deeper introduction.

The development system used in this class relies on the `RtMidi framework <https://github.com/thestk/rtmidi>`_. This allows the inclusion of any ALSA MIDI device on Linux systems and hence any USB MIDI device. The `RtMidi Tutorial <https://www.music.mcgill.ca/~gary/rtmidi/>`_ gives a thorough introduction to the use of the library.

-----

ALSA MIDI
=========

The `Advanced Linux Sound Architecture (ALSA) <https://www.alsa-project.org/wiki/Main_Page>`_ makes audio- and MIDI interfaces accessible for software. As an API it is part of the Linux kernel. Other frameworks, like JACK or Pulseaudio work on a higher level and rely on ALSA.

Finding your ALSA MIDI Devices
------------------------------

After connecting a MIDI device to an USB port, it should be available via ALSA.
All ALSA MIDI devices can be listed with the following shell command:

.. code-block:: console

  $ amidi -l

The output of this request can look as follows:

.. code-block:: console

    Dir     Device        Name
    IO      hw:1 ,0 ,0   nanoKONTROL MIDI 1
    IO      hw:2 ,0 ,0   PCR-1 MIDI 1
    I       hw:2 ,0 ,1   PCR-1 MIDI 2

In this case, two USB MIDI devices are connected. They can be addressed by their MIDI device ID (hw:0/1).

-----

The MIDI Tester Example
=======================

The MIDI tester example can be used to print all incoming MIDI messages to the console.
This can be helpful for reverse-engineering MIDI devices to figure out their controller numbers.


The MIDI Manager Class
----------------------

The MIDI Manager class introduced in this test example is used as a template for following examples which use MIDI. For receiving messages, RtMidi offers a  queued MIDI input and a user callback mode. In the latter case, each incoming message triggers a callback function. For the queued mode, as used here, incoming messages are collected until retrieved by an additional process.

The ``midiMessage`` struct is used to store incoming messages. It holds the three standard MIDI message bytes plus a Boolean for the processing state.

.. code-block:: cpp

    /// struct for holding a MIDI message
    typedef struct  {
        int byte1	      = -1;
        int byte2             = -1;
        double byte3          = -1;
        bool hasBeenProcessed = false;

    }midiMessage;
