#ifndef GRAINPLAYER_H
#define GRAINPLAYER_H


#include "singlesample.h"
#include "triangularwindow.h"

class GrainPlayer
{
public:

    GrainPlayer(std::string filePath, int fs, int win_size, int nWin);

    double get_sample();

    void   set_relative_distance(double r);

    double get_position();

private:

    SingleSample *sample;

    double relative_stepsize;

    TriangularWindow *windows;

    int nWindows;
};

#endif // GRAINPLAYER_H
