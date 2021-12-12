/**
* \file waveguide.cpp
* \class WaveGuide
*
*  Waveguide model with fractional delay lines.
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/


#include "waveguide.h"

WaveGuide::WaveGuide(int l_dL, int nF)
{

    gain     = 0.9;

    shiftFactor = 1.0;

    // initalize filter
    nCoef       = nF;
    filt        = new double[nF];
    for (int i=0; i<nCoef-1; i++)
    {
        filt[i] = 1.0 / (double) nCoef;
    }


    // initialize delay lines
    l_delayLine = l_dL;
    dl_l = new double[l_delayLine];
    dl_r = new double[l_delayLine];

    for (int i=0; i<l_delayLine-1; i++)
    {
        dl_l[i] = 0.0;
        dl_r[i] = 0.0;
    }

}

void WaveGuide::excite(double pos, double shift)
{

    shiftFactor = shift;

    // get index of delay lines at this position
    int idx = (int) ( (double) l_delayLine * pos);
    // and stay whithin array boundaries
    idx     = std::max(std::min(l_delayLine,idx),0);

    std::cout << "Plucked string at index: " << idx << std::endl;

    // set positive slope until plucking index
    for (int i=0; i<idx; i++)
    {
        dl_l[i] = 0.5* ((double) i / (double)(idx));
        dl_r[i] = 0.5* ((double) i / (double)(idx));
    }
    // set negative slope from plucking index to end
    for (int i=idx; i<l_delayLine; i++)
    {
        dl_l[i] = 0.5*(1.0 - ((double) i / (double) (l_delayLine-idx)));
        dl_r[i] = 0.5*(1.0 - ((double) i / (double) (l_delayLine-idx)));
    }

}


void WaveGuide::shift()
{

    double filtSumL = 0.0;
    double filtSumR = 0.0;

    // apply filter
    for (int i=0; i<nCoef; i++)
    {
        filtSumL = filtSumL + dl_l[i] * filt[i];
        filtSumR = filtSumR + dl_r[l_delayLine-i] * filt[nCoef-i];
    }


    // shift
    for (int i = 0; i < l_delayLine; i++)
    {
        dl_l[i] = dl_l[i+1];
        dl_r[l_delayLine-i] = dl_r[l_delayLine-i-1] ;
    }

    // insert with filter
    dl_l[l_delayLine-1]    = -filtSumR * gain;
    dl_r[0]                = -filtSumL * gain;

}


void WaveGuide::frac_shift()
{

    // split shift factor into integer and fractional part
    int intShift     = floor(shiftFactor);
    double fracShift = shiftFactor- (double) intShift;

    // take reflection values at ends of both delay lines
    double rL = interpolate(dl_l[0+intShift], dl_l[1+intShift], fracShift);
    double rR = interpolate(dl_r[l_delayLine-1-intShift],dl_r[l_delayLine-2-intShift], fracShift);

    // shift delay lines
    for (int i = 0; i < l_delayLine; i++)
    {
        dl_l[i] = interpolate(dl_l[i+intShift],dl_l[i+1+intShift],fracShift);
        dl_r[l_delayLine-i] = interpolate(dl_r[l_delayLine-i-intShift], dl_r[l_delayLine-i-1-intShift] ,fracShift);

    }

    // the filter output
    double filtSumL = 0.0;

    // the memorized value first
    filtSumL += rL * filt[0];

    // loop over remaining coeffients
    for (int i=1; i<nCoef; i++)
    {
        filtSumL = filtSumL + dl_l[i] * filt[i];
    }

    // insert with filter and gain
    dl_l[l_delayLine-1]    = -rL*gain;
    dl_r[0]                = -filtSumL;

}


double WaveGuide::getOutputAt(int pos)
{

    // stay whithin array boundaries
    pos     = std::max(std::min(l_delayLine,pos),0);

    double sum = 0.5* (dl_l[pos] + dl_r[pos] );
    return sum;
}

double WaveGuide::interpolate(double lowerVal, double upperVal, double frac)
{

    double interpVal 	= (lowerVal * (1-frac)) + (upperVal * frac);

    return interpVal;

}

void WaveGuide::set_gain(double a)
{
    gain = a;
}
