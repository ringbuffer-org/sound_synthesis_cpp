.. title: Working with the g++ Compiler
.. slug: cpp-compiler
.. date: 2021-12-10
.. tags:
.. category: cpp:basic
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 1


Compiling a Program
===================

Examples and projects in this modules can be compiled with g++ from the GNU Compiler Collection.
With the proper libraries installed, g++ can be called directly for small to medium sized projects.
The first example, just passing through the audio, is compiled with the following command:

.. code-block:: console

  g++ -Wall src/gain_example.cpp src/oscman.cpp -ljack -o gain_example

The compiler gets the extra argument ``Wall`` to print all warnings.
All source (``cpp``) files are passed to the compiler, followed by all libraries which need to be linked (linker arguments). The name of the binary or executable is specified after the ``-o`` flag. 

------

Build Scripts
=============
