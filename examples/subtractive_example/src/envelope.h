#ifndef ENVELOPE_H
#define ENVELOPE_H

#include<iostream>
#include<math.h>

using std::cout;

class Envelope
{
public:

    Envelope(double att, double rel, double expo, int fs);

    void trigger();

    double get_next_value();

    bool is_active();

    void set_exponent(int e);

    void set_attack(double a);

    void set_release(double r);

private:

    int FS;

    double L_attack;

    double L_release;

    int exponent;

    double t;

    bool active;

};

#endif // ENVELOPE_H
