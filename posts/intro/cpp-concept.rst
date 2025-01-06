.. title: Concept
.. slug: cpp-concept
.. date: 2020-11-29
.. tags:
.. category: cpp:intro
.. link:
.. description:
.. priority: 0
.. type: text


This module focuses on fundamental principles of sound synthesis algorithms in C++, covering paradigms like subtractive synthesis, additive synthesis, physical modeling, distortion methods and processed recording.
Theory and background of these approaches are covered in the contents of the `Sound Synthesis Introduction <https://hvc.berlin/teaching/sound-synthesis-introduction/>`_.

The concept is based on Linux audio systems as development and runtime systems (von Coler & Runge, 2017).
Using Raspberry PIs, classes can be supplied with an ultra low cost computer pool, resolving any compatibility issues of individual systems.
Besides, the single board computers can be integrated into embedded projects for actual hardware instruments.
Participants can also install Linux systems on their own hardware for increased performance.

Only few software libraries are part of the system used in this class, taking care of audio input and output, communication (OSC, MIDI), configuration and audio file processing.
This minimal required framework allows the focus on the actual implementation of the algorithms on a sample-by-sample level, not relying on extensive higher level abstractions.

-----

Although the concept of this class has advantages, there are different alternatives with their own benefits.
There is a variety of frameworks to consider for implementing sound synthesis paradigms and building digital musical instruments with C/C++.
The `JUCE <https://github.com/juce-framework/JUCE>`_ framework allows the compilation of
*'desktop and mobile applications, including VST, VST3, AU, AUv3, RTAS and AAX audio plug-ins'*.
It comes with many helpful features and can be used to create DAW-ready software components.
Environments like Puredata or SuperCollider come with APIs for programming user extensions.
The resulting software components can be integrated into existing projects, easily.

-----

References
----------

.. publication_list:: bibtex/cpp-teaching.bib
	   :style: unsrt
