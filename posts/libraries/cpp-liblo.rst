.. title: Using OSC with the liblo
.. slug: cpp-liblo
.. date: 2021-12-10
.. tags:
.. category: cpp:libraries
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 1

The OSC protocol is a wide spread means for communication between software components or systems, not only suited for music applications. Read more in the `OSC chapter <https://hvc.berlin/Control/open-sound-control/>`_ of the Computer Music Basics. There is a large variety of OSC libraries available in C/C++. The examples in this class are based on the `liblo <http://liblo.sourceforge.net/>`_, a lightweight OSC implementation for POSIX systems.


Installing the Library
======================

On Ubuntu systems, as the ones used in this class, the ``liblo`` library is installed with the following command:

.. code-block:: console

  $ sudo apt-get install liblo-dev


Including the Library
=====================

The ``liblo`` comes with additional C++11 wrappers to offer an object-oriented workflow. This feature is also used in the examples of this class. The following lines include both headers:

.. code-block:: cpp

  #include <lo/lo.h>
  #include <lo/lo_cpp.h>

------

The GainExample
===============

The GainExample is based on the ThroughExample, adding the capability to control the gain of the passed through signal with OSC messages.

-----

Passing Command Line Arguments
------------------------------

The main function of this example accepts the OSC port to listen to as a command line argument. This is realized with a string comparison. The compiled binary is then started with an extra argument for the port:

.. code-block:: console

  $ ./gain_example -p 6666

------

The OSC Manager Class
---------------------

The OSC-ready examples in these tutorials rely on a basic class for receiving OSC messages and making them accessible to other program parts. It opens a server thread, which listens to incoming messages in the background. With the  ``add_method`` function, OSC paths and arguments specifications can be linked to a callback function.

.. code-block:: cpp

  // create new server
  st = new lo::ServerThread ( p );

  // / Add the example handler to the server !
  st->add_method("/gain", "f", gain_callback, this);

  st -> start ();


Inside the callback function ``gain_callback``, the incoming value is stored to the member variable ``gain`` of the OscMan class.

.. code-block:: cpp

  statCast->gain = argv[0]->f;


------

The Processing Function
-----------------------

At the beginning of each call of the processing function, the recent incoming OSC messages are read from the OSC Manager:

.. code-block:: cpp

  // get the recent gain value from the OSC manager
  double gain = oscman->get_gain();

The gain values are applied later in the processing function, when copying the input buffers to the output buffers:

.. code-block:: cpp

  out[chanCNT][sampCNT] = in[chanCNT][sampCNT] * gain;

-----

Compiling
=========

When compiling with g++, the liblo library needs to be linked in addition to the JACK library:

.. code-block:: console

  $ g++ -Wall -std=c++11 src/main.cpp src/gain_example.cpp src/oscman.cpp -ljack -llo -o gain_example
