#include "singlesample.h"

SingleSample::SingleSample(std::string filePath)
{
    rate = 1;
    pos  = 0.0;
    read_wavefile(filePath);
}

SingleSample::~SingleSample()
{

}


double SingleSample::get_rate()
{

    return rate;
}

void   SingleSample::set_rate(double r)
{
    rate = r;

}

double SingleSample::get_pos()
{

    return pos;
}

void SingleSample::set_pos(double p)
{

}

/// loop play
void SingleSample::get_frame(int n, float* a)
{

    for(int i=0; i<n; i++)
    {

        pos = pos+rate;

        // are we within bounds?
        if((int)pos<L && (int)pos>=0 )
        {
            a[i] = get_sample(pos);
        }
        else
        {
            if ( rate >= 0)
                pos = 0;
            else
                pos = L-1;
        }
    }
}


int SingleSample::get_L()
{
    return L;
}

double* SingleSample::get_x()
{
    return x;
}


void SingleSample::set_f(int in)
{
    f =  in;
}

void SingleSample::set_sr(int in)
{
    sr =  in;
}


void SingleSample::set_L(int in)
{
    L =  in;
}

void SingleSample::set_nChannels(int in)
{
    nChannels =  in;
}

void SingleSample::initialize()
{
    x = new double[L*sizeof(double)];
}

double SingleSample::get_sample(int pos)
{
    /// Return sample at integer position only.s
    return x[pos];

}

int SingleSample::getFS()
{
    return info.samplerate;
}


double SingleSample::get_sample(double pos)
{
    /// Use linear interpolation to
    /// get the next sample at the floating point
    /// position in time!

    if(pos>=1 && pos<L)
    {

        double nearRound;
        double fract = modf(pos,&nearRound);

        int lowerBound = (int) nearRound;
        int upperBound = lowerBound +1;

        double lowerSP = x[lowerBound];
        double upperSP = x[upperBound];

        double interp = (1-fract)*lowerSP + fract*upperSP;
        return interp;
    }

    else
        return 0;
}

void SingleSample::step()
{

    pos = pos+rate;

    // loop in forward playback
    if(pos>=L)
        pos = 0;

    // loop in reverse playback
    if(pos<0)
        pos = L;

}


void SingleSample::read_wavefile(std::string filePath)
{

    cout << "Trying to read: " << filePath << endl;

    /// Open the audio file using sndfile!
    info.format = 0;
    sf          = sf_open(filePath.c_str(),SFM_READ,&info);

    if (sf == NULL)
    {
        printf("Failed to open the audio file.\n");
        //exit(-1);
    }

    set_f(  info.frames);
    set_sr(info.samplerate);
    set_nChannels(info.channels);

    set_L(info.frames*info.channels);

    initialize();

    int num = sf_read_double (sf,x,info.frames*info.channels);
    sf_close(sf);

}


