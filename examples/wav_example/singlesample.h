/**
 * \class SingleSample
 *
 *
 * \brief Class which holds the waveform of a sample in an array.
 *
 *
 * This class holds the waveform of a sample in an array and provides
 * all necessary methods for reading and accessing it.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/11/22 14:16:20 $
 *
 * Contact: voncoler@tu-berlin.de
 *
 *
 */

#ifndef SINGLESAMPLE_H
#define SINGLESAMPLE_H


#include<iostream>

#include <sndfile.h>
#include <string>
#include <cmath>



using std::cout;
using std::endl;

class SingleSample
{
public:
    SingleSample(std::string filePath);
    virtual ~SingleSample();
    void read_wavefile(std::string filePath);

    int get_L();
    double* get_x();

    void set_f(int in);
    void set_sr(int in);
    void set_nChannels(int in);
    void set_L(int in);

    void initialize();

    double get_sample(double pos);
    double get_sample(int pos);

    double get_rate();
    void   set_rate(double r);

    double get_pos();
    void set_pos(double p);

    void step();

    void get_frame(int n, float *a);

    //void setResampleRate(double resRate);
    int getFS();


private:

    SNDFILE *sf;
    SF_INFO info;


    int num_channels;
    int f,sr,nChannels;
    int num, L;

    double* x;

    double pos;
    double rate;

    double resampleFactor = 1;
};

#endif // SINGLESAMPLE_H
