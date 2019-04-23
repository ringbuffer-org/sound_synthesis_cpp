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
 * It serves as a state machine by holding a playback speed and position.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.527$
 *
 * \date 2016-11-22
 *
 *
 */

#ifndef SINGLESAMPLE_H
#define SINGLESAMPLE_H


#include <iostream>
#include <sndfile.hh>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

class SingleSample
{
public:

    ///
    /// \brief SingleSample
    ///     the standard constructor
    /// \param filePath
    /// \param fs
    ///  the  jack sample rate
    SingleSample(std::string filePath, int fs);

    ///
    /// \brief ~SingleSample
    /// ths should be the destructor
    virtual ~SingleSample();

    ///
    /// \brief read_wavefile
    /// \param filePath
    ///
    void read_wavefile(std::string filePath);

    ///
    /// \brief get_sample
    /// get sample values at exact integer postions
    /// \param chan
    /// \param pos
    /// \return
    ///
    double get_sample(int chan, int pos);

    ///
    /// \brief get_sample return interpolated value
    /// this is an overloaded function!
    /// \param chan the cahnnel to access
    /// \param pos the floating point position
    /// \return the sample's interpolated value
    ///
    double get_sample(int chan, double pos);

    ///
    /// \brief step
    /// this function sets a new position,
    /// regarding the speed, and the resampleFactor
    void step();

    ///
    /// \brief get_x
    /// \return returns a pointer to the sample data arrays
    ///
    double **get_x();


    // A couple of getters and setters, mostly unused in this example
    void set_f(int in);
    void set_sr(int in);

    void set_nChannels(int in);
    int get_nChannels();

    void set_nFrames(int in);
    int get_nFrames();

    double get_rate();
    void set_rate(double r);

    double get_pos();
    void set_pos(double p);

    int getFS();


private:

    SNDFILE *sf;
    SF_INFO info;

    int FS;

    ///
    /// \brief resampleFactor
    /// rescales the playback speed according to
    /// the sample rate of the wav file and the JACK server
    double resFac;


    ///
    /// \brief nFrames
    /// The number of frames in the wav file
    /// which is the length in samples
    int nFrames;

    ///
    /// \brief fs_sample
    /// sampling rate of the wav file
    int fs_sample;

    ///
    /// \brief nChannels
    /// number of channels in this wav
    int nChannels;

    ///
    /// \brief L
    /// length of the interleaved wav data
    /// (number of frames times number of channels)
    int L;

    ///
    /// \brief x
    /// The 2d-array with the sample data,
    /// arranged as a matrix.
    double** x;

    ///
    /// \brief pos
    /// the recent postion within the sample
    double pos;

    /// the playback rate
    double rate;



};

#endif // SINGLESAMPLE_H
