/**
*
* \file  triangularwindow.cpp
* \class TriangularWindow
*
* \brief A single window (envelope) for granular synthesis.
*
* \author Henrik von Coler
*
* \date  2019/03/23
*
*/

#ifndef TRIANGULARWINDOW_H
#define TRIANGULARWINDOW_H


#include <iostream>


class TriangularWindow
{

public:

    ///
    /// \brief TriangularWindow
    /// the constructor
    TriangularWindow();

    ///
    /// \brief initialize
    /// \param L window length
    /// \param P the relative position of the grain within the sample
    /// \param start starting point for the playback position within the frame
    /// initialize a window
    void initialize(int L, int P, int start);

    ///
    /// \brief get_value
    /// get the value of the window at the playback_position
    ///  \return
    ///
    double get_value();

    ///
    /// \brief get_relative_position
    /// \return
    ///
    int get_relative_position();

    ///
    /// \brief increment_relative_position
    /// move window (grain) position in sample
    /// \param p the fraction of the window size to shift the position
    /// \param maxLength the maximum length of the sample
    ///
    void increment_relative_position(double p, int maxLength);

    ///
    /// \brief step
    /// \return returns '1' if end of window (grain) is reached
    ///
    int step();

private:

    ///
    /// \brief length
    /// the length of the window
    int length;

    ///
    /// \brief m
    /// the slope of the triangular window
    double m;

    ///
    /// \brief center_offset
    /// the position of the grain in the sample
    int center_offset;

    ///
    /// \brief playback_position
    /// the playback_position is the positio
    /// within the grain (window)
    int playback_position;

};

#endif // TRIANGULARWINDOW_H
