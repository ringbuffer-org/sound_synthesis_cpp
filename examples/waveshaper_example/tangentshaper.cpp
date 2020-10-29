#include "tangentshaper.h"

TangentShaper::TangentShaper()
{
    scaler = 1.0;
}

void TangentShaper::set(double s)
{
    scaler = s;
}

double TangentShaper::map(double in)
{

    double val = std::max(-1.0,std::min(1.0,in));

    double out = std::tanh(scaler * 2*M_PI*val);

    return out;
}
