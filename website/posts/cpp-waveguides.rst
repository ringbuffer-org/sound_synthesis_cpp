.. title: Simple Waveguides in C++
.. slug: cpp-simple-waveguides
.. date: 2021-12-10
.. tags:
.. category: cpp:physical
.. link:
.. description:
.. type: text
.. has_math: true
.. priority: 3

Waveguides can be used to model acoustical oscillators, such as strings, pipes or drumheads.
The `theory of digital waveguides <http://hvc.berlin/Physical_Modeling/physical-modeling-waveguides-losses/>`_ is covered in the sound synthesis introduction.

The WaveGuide Class
===================

The WaveGuide class implements all necessary components for a waveguide string emulation.
Inside the class, the actual waveguide-buffers are realized as pointers to double arrays.

**From ``WaveGuide.h``:**

.. code-block:: cpp

    /// length of the delay lines
    int     l_delayLine;

    /// leftward delay line
    double  *dl_l;

    /// rightward delay line
    double  *dl_r;


----

The pointer arrays need to be initialized in the constructor of the WaveGuide class.

**From ``WaveGuide.cpp``:**

.. code-block:: cpp

    dl_l = new double[l_delayLine];
    dl_r = new double[l_delayLine];

    for (int i=0; i<l_delayLine-1; i++)
    {
        dl_l[i] = 0.0;
        dl_r[i] = 0.0;
    }


----

Plucking the String
===================

The method ``void WaveGuide::excite(double pos, double shift)`` is called for plucking the string, respectively exciting it.
It receives a plucking position and a shift parameter. In two loops, the method fills the two waveguides with the excitation function. In this example, a simple triangular function is chosen.

**From ``WaveGuide.cpp``:**

.. code-block:: cpp

    // set positive slope until plucking index
    for (int i=0; i<idx; i++)
    {
        dl_l[i] = 0.5* ((double) i / (double)(idx));
        dl_r[i] = 0.5* ((double) i / (double)(idx));
    }
    // set negative slope from plucking index to end
    for (int i=idx; i<l_delayLine; i++)
    {
        dl_l[i] = 0.5*(1.0 - ((double) i / (double) (l_delayLine-idx)));
        dl_r[i] = 0.5*(1.0 - ((double) i / (double) (l_delayLine-idx)));
    }


Oscillating
===========
