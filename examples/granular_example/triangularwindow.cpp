#include "triangularwindow.h"

TriangularWindow::TriangularWindow()
{
}


double TriangularWindow::get_value()
{
    double gain = 0;

    if(playback_position <= length/2)
    {
        gain =  m * playback_position;
    }
    else
    {
        gain =  1 - m * (playback_position - length/2);
    }

    return gain;
}

int TriangularWindow::get_relative_position()
{
    return center_offset - playback_position;
}

void TriangularWindow::increment_relative_position(double p, int maxLength)
{
    int v = center_offset + (int) ((double) length * p);

    if(v >= 0 && v<=maxLength)
        center_offset = v;
}


int TriangularWindow::step()
{

    int finished = 0;

    // the
    playback_position+=1;

    if(playback_position>=length)
    {
        playback_position =0;
        finished = 1;
    }
}

void TriangularWindow::initialize(int L, int P, int start)
{
    length              = L;
    center_offset       = P;

    playback_position   = start;

    m = 2 / (double) L ;

}

