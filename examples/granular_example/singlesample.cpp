/**
 * \file singlesample.cpp
 * \class SingleSample
 *
 * \brief Class which holds the waveform of a sample in an array.
 *
 * This class holds the waveform of a sample in an array and provides
 * all necessary methods for reading and accessing it.
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.52$
 *
 * \date 2016-11-22
 *
 *
 */

#include "singlesample.h"

SingleSample::SingleSample(std::string filePath, int fs)
{

    // set default values
    rate = 1;
    pos  = 0.0;
    FS   = fs;

    // read the data
    read_wavefile(filePath);

}

double SingleSample::get_sample(int chan, double pos)
{

    // Use linear interpolation to
    // get the next sample at the floating point
    // position index!


    if(pos>=0 && pos<=L)
    {

        double nearRound;
        double fract = modf(pos,&nearRound);

        int lowerBound = (int) nearRound;
        int upperBound = lowerBound +1;

        double lowerSP = x[chan][lowerBound];
        double upperSP = x[chan][upperBound];

        double interp = (1-fract)*lowerSP + fract*upperSP;
        return interp;
    }

    else
    {
        return 0;
        cout << "Out of range!: "  << endl;
    }
}

void SingleSample::step()
{

    double R = rate * resFac;

    pos = pos+R;

    // loop in forward playback
    if(pos>nFrames)
        pos = 0 + pos-(double)nFrames;

    // loop in reverse playback
    if(pos<0)
        pos = nFrames;

}


void SingleSample::read_wavefile(std::string filePath)
{

    cout << "Reading: " << filePath << endl;

    // Open the audio file using sndfile!
    info.format = 0;
    sf          = sf_open(filePath.c_str(),SFM_READ,&info);

    if (sf == NULL)
    {
        printf("Failed to open the audio file.\n");
        //exit(-1);
    }

    // write wav parameters to member variables
    nFrames     = info.frames;
    fs_sample   = info.samplerate;
    nChannels   = info.channels;
    L           = info.frames * info.channels;

    //
    resFac = ((double) fs_sample / (double) FS );

    cout << "GR:  " << resFac << endl;
    cout << "Fs:\t\t" << fs_sample << endl;
    cout << "Num Channels:\t" << nChannels << endl;
    cout << "Num Samples:\t" << nFrames << endl;

    // read interleaved data
    double* tmp = new double[L];
    sf_count_t num     = sf_read_double(sf,tmp,L);
    cout << "Read Frames:\t" << num << " of " << L << endl;
    sf_close(sf);

    // allocate memory for deinterleaved channels
    x = new double*[nChannels];
    for(int i=0; i< nChannels; i++)
    {
        x[i] = new double[nFrames];
    }

    // deinterleave into 'separate' arrays for L and R
    int i=0;
    for(int sampCNT=0; sampCNT<nFrames; sampCNT++)
    {
        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            x[chanCNT][sampCNT] = tmp[i];
            i++;
        }
    }

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

int SingleSample::get_nFrames()
{
    return nFrames;
}

double** SingleSample::get_x()
{
    return x;
}


void SingleSample::set_f(int in)
{
    nFrames =  in;
}

void SingleSample::set_sr(int in)
{
    fs_sample =  in;
}



void SingleSample::set_nChannels(int in)
{
    nChannels =  in;
}

int SingleSample::get_nChannels()
{
    return nChannels;
}


double SingleSample::get_sample(int chan, int pos)
{
     return x[chan][pos];
}

int SingleSample::getFS()
{
    return info.samplerate;
}


