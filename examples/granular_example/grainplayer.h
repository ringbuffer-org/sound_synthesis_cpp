/**
*
* \file  grainplayer.cpp
* \class GrainPlayer
*
* \brief The granular player class,
*        holding a SingleSound and an
*        array of window functions, representing
*        the grains.
*
* \author Henrik von Coler
*
* \date  2019/03/23
*
*/


#ifndef GRAINPLAYER_H
#define GRAINPLAYER_H


#include "singlesample.h"
#include "triangularwindow.h"

class GrainPlayer
{
public:

    ///
    /// \brief GrainPlayer
    /// the constructor
    /// \param filePath path to the wav file to read
    /// \param fs sampling rate of the JACK server
    /// \param win_size the grain size (size of the window)
    /// \param nWin the number of grains to be used
    ///
    GrainPlayer(std::string filePath, int fs, int win_size, int nWin);

    ///
    /// \brief get_sample
    /// get a single sample, using all active grains
    /// \return
    /// a sound sample for the output
    double get_sample();

    void   set_relative_distance(double r);


private:

    ///
    /// \brief sample
    /// an instance of the single sample class
    SingleSample *sample;

    ///
    /// \brief relative_stepsize
    /// relative_stepsize is the
    double relative_stepsize;

    ///
    /// \brief windows
    ///        pointer to an array of windows
    TriangularWindow *windows;

    int nWindows;
};

#endif // GRAINPLAYER_H
