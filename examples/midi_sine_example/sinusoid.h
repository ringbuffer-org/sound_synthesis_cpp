#ifndef SINUSOID_H
#define SINUSOID_H

#define _USE_MATH_DEFINES

#include<vector>
#include<math.h>

class Sinusoid
{
public:



    Sinusoid();

    void init(double f, double a, double p, int fS);

    void proceed(double ms);

    /// getters
    double frequency();
    double amplitude();
    double phase();
    /// setters (override)
    void frequency(double f);
    void amplitude(double a);
    void phase(double p);


    double getNextSample();



private:

    // PURE SINE STATE
    double freq;
    double amp;
    double phi;

    // SYSTEM RELATED
    int nframes;
    int fs;

    double *t;


};

#endif // SINUSOID_H
