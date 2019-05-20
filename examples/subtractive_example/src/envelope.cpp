#include "envelope.h"

Envelope::Envelope(double att, double rel, double expo, int fs)
{

    L_attack   = att;
    L_release  = rel;

    exponent =expo;

    t = 0.0;

    active = false;

    FS = fs;

}


void Envelope::trigger()
{
    t       = 0;
    active  = true;
}



double Envelope::get_next_value()
{

    double outVal;

    if(t<=L_attack)
    {
        outVal = 1.0/(L_attack) * t;
    }
    else
    {
       outVal = pow(1.0-((1/(L_release))*t), exponent);
    }

    // step ahead
    t = t + (1.0 / (double) FS );
    // stop and end of release
    if(t>=(L_attack+L_release))
    {
        active=false;
    }

    return outVal;
}

bool Envelope::is_active()
{
    return active;
}


void Envelope::set_exponent(int e)
{
    exponent = e;
}

void Envelope::set_attack(double a)
{
    L_attack = a;
}

void Envelope::set_release(double r)
{
    L_release = r;
}
