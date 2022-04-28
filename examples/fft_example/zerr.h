#ifndef ZERR_H
#define ZERR_H

#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<unistd.h>

#include<jack/jack.h>


#include <complex.h>
#include <fftw3.h>

// #include<rfftw.h>

#define PI 3.14159265



class Zerr
{
public:
    Zerr();

private:

    /// IFFT length
    uint L = 2048*2;
    uint L_fft = (L / 2 + 1);

    /// number of IFFT buffer for overlap add
    uint n_buffers;

    ///
    /// \brief nChannels
    /// the number of audio channels @todo (should not be hard-coded)
    int nChannels = 1;

    ///
    /// \brief client
    /// the jack client, obviously
    jack_client_t   *client;

    ///
    /// \brief status
    /// gets the status from the jack server
    jack_status_t   status;


    ///
    /// \brief input_port
    /// the jack input ports
    jack_port_t     **input_port;

    ///
    /// \brief output_port
    /// the jack output ports
    jack_port_t     **output_port;

    ///
    /// \brief in
    ///
    /// \brief out
    jack_default_audio_sample_t **in, **out;


    ///
    /// \brief process
    /// \param nframes
    /// \return
    ///
    int process (jack_nframes_t nframes);

    ///
    /// \brief callback_process
    ///         is used to access the members of this
    ///         class in the static mode
    /// \param x number of samples in the buffer
    /// \param object void pointer
    /// \return
    ///
    static int callback_process(jack_nframes_t x, void* object);


    // FFTW stuff


    double *ifft_buff;

    double *fft_in;

    double **ifft_out;
    double *power_spectrum;

    fftw_complex *fft_out;

    fftw_plan p_fft, p_ifft;



    uint fft_count = 0;

    float get_hann_sample(int pos, int L);
    float get_triangular_sample(int pos, int L);

    /// index of the most recent fft/ifft buffer
    uint ifft_index = 0;

    uint n_overlap;

};

#endif // ZERR_H
