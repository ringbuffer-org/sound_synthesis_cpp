#include "grainplayer.h"

GrainPlayer::GrainPlayer(std::string filePath, int fs, int win_size, int nWin)
{

    cout << "Creating GrainPlayer with " << win_size << " samples window size! " << endl;

    nWindows = nWin;

    sample   = new SingleSample(filePath, fs);

    windows  = new TriangularWindow[nWindows];

    for(int i=0; i<nWindows; i++)
    {
        windows[i].initialize(win_size,i* (win_size/nWindows),i* (win_size/nWindows));
    }

}



double GrainPlayer::get_sample()
{
    double output = 0;

    for(int windowCNT=0; windowCNT<nWindows; windowCNT++)
    {


        double tmpGain = windows[windowCNT].get_value();
        int tmpPos     = windows[windowCNT].get_relative_position();
        double tmpOut  = 0;

        if(tmpPos >= 0 && tmpPos <= sample->get_nFrames())
        {
            tmpOut  = tmpGain * sample->get_sample(0,tmpPos);
        }

        output += tmpOut;

        int f = windows[windowCNT].step();
        if(f==1)
        {
           int tmpVal =  windows[windowCNT].increment_relative_position(relative_stepsize,sample->get_nFrames());

        }
    }

    return output;

}


void GrainPlayer::set_relative_distance(double r)
{
    relative_stepsize = r;
}

double GrainPlayer::get_position()
{

}
