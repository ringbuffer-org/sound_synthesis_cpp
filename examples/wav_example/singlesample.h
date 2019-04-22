/**
 * \file singlesample.h
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
 * \version $Revision: 0.52$
 *
 * \date 2016-11-22
 *
 *
 */

#ifndef SINGLESAMPLE_H
#define SINGLESAMPLE_H


#include<iostream>

#include <sndfile.hh>
#include <string>
#include <cmath>



using std::cout;
using std::endl;

class SingleSample
{
public:

    SingleSample(std::string filePath, int fs);
    virtual ~SingleSample();
    void read_wavefile(std::string filePath);

    int get_L();
    double **get_x();

    void set_f(int in);
    void set_sr(int in);
    void set_nChannels(int in);
    int get_nChannels();

    void set_L(int in);

    void initialize();

    double get_sample(int chan, int pos);

    double get_sample(int chan, double pos);

    double get_rate();

    void set_rate(double r);

    double get_pos();
    void set_pos(double p);

    void step();


    //void setResampleRate(double resRate);
    int getFS();


private:

    SNDFILE *sf;
    SF_INFO info;

    int FS;

    /// The resampling factor between
    /// audio sample and interface.
    double resFac;

    int num_channels;

    /// The number of frames in the wav file
    int nFrames;
    ///
    int fs_sample;
    int nChannels;
    int L;

    ///
    /// \brief x
    /// The 2d-array with the sample data,
    /// arranged as a matrix.
    double** x;

    double pos;

    /// the playback rates
    double rate;

    double resampleFactor = 1;
};

#endif // SINGLESAMPLE_H
