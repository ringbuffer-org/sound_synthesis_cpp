#include "sinefolder.h"

SineFolder::SineFolder()
{
    scaler = 1.0;
}

void SineFolder::set(double s)
{
    scaler = s;
}

double SineFolder::map(double in)
{

    double val = std::max(-1.0,std::min(1.0,in));

    double out = std::sin(scaler * 2*M_PI*val);

    return out;
}
