.. title: The JACK API
.. slug: cpp-jack
.. date: 2020-11-29
.. tags:
.. category: cpp:libraries
.. link:
.. description:
.. priority: 0
.. type: text


All examples in this class are implemented as JACK clients.
Audio input and output is thus based on the `JACK Audio API <https://jackaudio.org/api/>`_.
The JACK framework takes over a lot of management and allows a quick entry point for programmers.
Professional Linux audio systems are usually based on JACK servers, allowing the flexible connection of different software components. Read more in the `JACK Section <http://hvc.berlin/Linux/using-jack-audio/>`_ of the Computer Music Basics.

-----

The ThroughExample
==================

The ``ThroughExample`` is a slightly adapted version of the `Simple Client <https://github.com/jackaudio/example-clients/blob/master/simple_client.c>`_. It wraps the same functionality into a C++ class, adding multi-channel capabilities.

------

Main
----

The file ``main.cpp`` creates an instance of the ``ThroughExample`` class. No command line arguments are passed and the object is created without any arguments:

.. code-block:: cpp

  ThroughExample *t = new ThroughExample();

-----

Member Variables
----------------

.. code-block:: cpp

  jack_client_t   *client;

The pointer to a jack client is needed for connecting this piece of software to the JACK server.
