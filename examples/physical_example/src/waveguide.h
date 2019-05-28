/**
* \file waveguide.h
* \class WaveGuide
*
*  Waveguide model with fractional delay lines.
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/

#ifndef DELAYLINE_H
#define DELAYLINE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

class WaveGuide
{
private:

    /// number of FIR coefficients
    int     nCoef;

    /// length of the delay lines
    int     l_delayLine;

    /// leftward delay line
    double  *dl_l;

    /// rightward delay line
    double  *dl_r;

    /// gain factor
    double   gain;

    ///
    /// \brief shiftFactor
    /// the factor by which the delay lines
    /// are shifted.
    double   shiftFactor;

    /// pointer to an array of filter coefficients
    double *filt;

public:

    ///
    /// \brief WaveGuide
    /// The constructor
    /// \param l_delayLine
    /// length of the delay lines
    /// \param nF
    /// number of filter coefficients
    ///
    WaveGuide(int l_delayLine, int nF);

    ///
    /// \brief shift
    /// function for shifting the delay lines
    /// by one sample (legacy)
    void shift();

    ///
    /// \brief frac_shift
    /// fnction for fractional shift
    void frac_shift();

    ///
    /// \brief getOutputAt
    ///  get the oputput at the bridge
    /// \param pos not used
    /// \return
    ///
    double getOutputAt(int pos);

    ///
    /// \brief interpolate
    /// linear interpolation betweeen two samples.
    /// \param lowerVal the value closer to the position
    /// \param upperVal the value further from the position
    /// \param frac the fraction (0-1)of the interpolation point
    /// \return the interpolated value
    ///
    double interpolate(double lowerVal, double upperVal, double frac);

    ///
    /// \brief excite
    /// Excite the waveguide.
    /// A triangular excitation (plucking) at
    /// a certain position with a certain tension
    /// \param pos a value between 0 and 1 for the plucking position
    /// \param frac_shift
    ///
    void excite(double pos, double frac_shift);

    ///
    void set_gain(double a);
};

#endif // DELAYLINE_H
