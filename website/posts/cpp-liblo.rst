.. title: Using the liblo
.. slug: cpp-liblo
.. date: 2021-12-10
.. tags:
.. category: cpp:control
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 2

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

  # include# include...
  <lo/lo.h>
  <lo/lo_cpp.h>


The OSC Manager Class
=====================

The OSC-ready examples in these tutorials rely on a basic class for processing

.. code-block:: cpp

  // create new server
  st = new lo :: ServerThread ( p );

  // / Add the example handler to the server !
  st - > add_method ( NULL , NULL , double_callback , this );
  st - > start ();
