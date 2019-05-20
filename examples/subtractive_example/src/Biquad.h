/**
 * \class Biquad
 * \brief A biquad filter class!
 *
 * \file Biquad.h
 *
 *
 * \link https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
 *
 * \author Henrik von Coler
 *
 * \version 0.1
 *
 * \date  2019-05/20
 *
 */





#ifndef Biquad_h
#define Biquad_h

enum {
    bq_type_lowpass = 0,
    bq_type_highpass,
    bq_type_bandpass,
    bq_type_notch,
    bq_type_peak,
    bq_type_lowshelf,
    bq_type_highshelf
};

class Biquad {
public:
    Biquad();
    Biquad(int type, double Fc, double Q, double peakGainDB);
    ~Biquad();
    void setType(int type);
    void setQ(double Q);
    void setFc(double Fc);
    void setPeakGain(double peakGainDB);
    void setBiquad(int type, double Fc, double Q, double peakGain);
    float process(float in);
    
protected:
    void calcBiquad(void);

    int type;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
};

inline float Biquad::process(float in) {
    double out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}

#endif // Biquad_h
