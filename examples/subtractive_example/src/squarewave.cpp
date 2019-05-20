/**
 * \class SquareWave
 * \file SquareWave.h
 *
 * \author Henrik von Coler
 *
 * \version 0.1
 *
 * \date  2019-05-20
 *
 *
 */

#include "squarewave.h"


SquareWave::SquareWave()
{

}

void SquareWave::init(double f, double a, double p, double w, int fS)
{
    freq    = f;
    amp     = a;
    phi     = p;
    width   = w;
    fs      = fS;
}

double SquareWave::getNextSample()
{

    // This method gets the next sample of the square wave
    // with a fixed duty cycle of 50%.

    double thisVal;

    if(phi< M_PI * ((1-width)*2))
        thisVal = 1;
        else
        thisVal = -1;


    // apply amplitude
    thisVal = thisVal*amp;

    // rotate to next step
    phi += 2.0 * M_PI * freq * (1.0/ (double) fs);

    // wrap to 2 pi
    if(phi>=2*M_PI)
    {
        phi -= 2*M_PI;

    }

    return thisVal;

}


double SquareWave::frequency()
{
    return freq;
}

double SquareWave::amplitude()
{
    return amp;
}

double SquareWave::phase()
{
    return phi;
}

void SquareWave::frequency(double f)
{
    freq = f;
}

void SquareWave::amplitude(double a)
{
    amp = a;
}

void SquareWave::phase(double p)
{
    phi = p;
}

void SquareWave::pulsewidth(double w)
{
    width = w;
}
