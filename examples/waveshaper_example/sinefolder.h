#ifndef SINEFOLDER_H
#define SINEFOLDER_H

#include <math.h>
#include <algorithm>

#include "transferfunction.h"
#include "sinefolder.h"

class SineFolder: public TransferFunction
{
public:
    SineFolder();

    void set(double s);

    double map(double in);

private:
    double scaler;
};

#endif // SINEFOLDER_H
