#ifndef TANGENTSHAPER_H
#define TANGENTSHAPER_H

#include <math.h>
#include <algorithm>

#include "transferfunction.h"
#include "tangentshaper.h"

class TangentShaper: public TransferFunction
{
public:
    TangentShaper();

    void set(double s);

    double map(double in);

private:
    double scaler;
};

#endif // TANGENTSHAPER_H
