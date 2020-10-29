#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <math.h>
#include <algorithm>

class TransferFunction
{
public:
    TransferFunction();

    virtual void set(double p);

    virtual double map(double in);

private:
    double scaler;
};

#endif // TRANSFERFUNCTION_H
