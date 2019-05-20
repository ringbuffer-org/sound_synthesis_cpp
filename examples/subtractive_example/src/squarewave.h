/**
 * \class SquareWave
 * \brief Square wave oscillator
 *        with variable pulse width.
 * \file SquareWave.h
 *
 *
 * \author Henrik von Coler
 *
 * \version 0.1
 *
 * \date  2019-05-20
 *
 *
 */

#ifndef SINUSOID_H
#define SINUSOID_H

#define _USE_MATH_DEFINES

#include<vector>
#include<math.h>


class SquareWave
{
public:



    SquareWave();

    void init(double f, double a, double p, double w, int fS);

    void proceed(double ms);

    /// getters
    double frequency();
    double amplitude();
    double phase();
    double pulsewidth();

    /// setters (override)
    void frequency(double f);
    void amplitude(double a);
    void phase(double p);
    void pulsewidth(double w);


    double getNextSample();



private:

    // PURE SINE STATE
    double freq;
    double amp;
    double phi;
    double width;

    // SYSTEM RELATED
    int nframes;
    int fs;

    double *t;


};

#endif // SINUSOID_H
