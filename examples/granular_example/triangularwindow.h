#ifndef TRIANGULARWINDOW_H
#define TRIANGULARWINDOW_H


#include <iostream>


class TriangularWindow
{

public:

    TriangularWindow();

    void initialize(int L, int P, int start);

    double get_value();

    int get_relative_position();

    int increment_relative_position(double p, int maxLength);

    int step();

private:

    int length;

    double m;

    int center_offset;

    int playback_position;

};

#endif // TRIANGULARWINDOW_H
