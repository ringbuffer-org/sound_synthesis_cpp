/**
 * \class Sinusoid
 *
 *
 * \brief Simple sinusoid handler class.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/01 14:16:20 $
 *
 * Contact: von_coler@intelligent-noise-solutions.de
 *
 *
 */

#include "sinusoid.h"


Sinusoid::Sinusoid()
{

}

void Sinusoid::init(double f, double a, double p,  int fS)
{
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
}

double Sinusoid::getNextSample()
{

    /// This method gets the next sample of the sinusoid.
    /// The amplitude is applied and the angle of the
    /// sinusoid is increased, according to the sample rate.

    // get sinusoidal value
    double thisVal = sin(phi);

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


double Sinusoid::frequency()
{
    return freq;
}

double Sinusoid::amplitude()
{
    return amp;
}

double Sinusoid::phase()
{
    return phi;
}

void Sinusoid::frequency(double f)
{
    freq = f;
}

void Sinusoid::amplitude(double a)
{
    amp = a;
}

void Sinusoid::phase(double p)
{
    phi = p;
}
