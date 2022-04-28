// https://gist.github.com/ricpacca/652ab90ba3a5754e980c78d6634b84a0

#include "zerr.h"

using std::cout;
using std::endl;

Zerr::Zerr()
{

    //    cout << "Starting Jack Client!" << endl;

    this->client = jack_client_open("Zerr", JackNullOption, &status, NULL);


    // connect the callback function
    jack_set_process_callback(this->client, this->callback_process, this);


    // allocate array
    input_port = new jack_port_t*[nChannels];
    for (int i=0; i<nChannels; i++)
    {
        std::string tmp_str = "input_" + std::to_string(i+1);
        input_port[i] = jack_port_register (client, tmp_str.c_str(),
                                            JACK_DEFAULT_AUDIO_TYPE,
                                            JackPortIsInput, 0);
    }

    output_port = new jack_port_t*[nChannels];
    for (int i=0; i<nChannels; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }

    out = new jack_default_audio_sample_t*;
    in  = new jack_default_audio_sample_t*;


    // allocate and initialize FFT arrays
    n_buffers = L / jack_get_buffer_size(this->client);

    //    cout << L << endl;
    //    cout << jack_get_buffer_size(this->client) << endl;
    //    cout << n_buffers << endl;



    ifft_buff = new double[L];
    for(int i=0; i<=L; i++)
        ifft_buff[i]=0;

    fft_in = new double[L];
    for(int i=0; i<=L; i++)
        fft_in[i]=0;

    fft_out = new fftw_complex[L_fft];
    //    for(int i=0; i<=L; i++)
    //        fftw_complex[i] = 0;


    ifft_out = new double*[n_buffers];
    for(int i=0; i<=n_buffers; i++)
        ifft_out[i] = new double[L];

    power_spectrum = new double[L_fft];
    for(int i=0; i<L_fft; i++)
        power_spectrum[i] = 0;

    p_fft  =  fftw_plan_dft_r2c_1d(L, fft_in, fft_out, FFTW_ESTIMATE);
    p_ifft =  fftw_plan_dft_c2r_1d(L, fft_out, ifft_buff, FFTW_ESTIMATE);

    jack_activate(this->client);

    // connect inputs
    jack_connect (client, "pure_data:output0", jack_port_name(input_port[0]));
    jack_connect (client, "pure_data:output1", jack_port_name(input_port[1]));
    // connect outputs
    jack_connect (client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect (client, jack_port_name(output_port[0]), "jaaa:in_1");

    // run forever
    sleep (-1);
}




int Zerr::process(jack_nframes_t nframes)
{


    // get input buffers
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
        in[i]  = (jack_default_audio_sample_t *)
                jack_port_get_buffer(this->input_port[i], jack_get_buffer_size(client));

    }

    // shift FFT input by nframes
    for(int idx=0; idx<L-nframes; idx++)
    {
        // fft_in[idx] = fft_in[idx+nframes] * get_triangular_sample(idx,L);
        fft_in[idx] = fft_in[idx+nframes];// * get_hann_sample(idx,L);
        // cout << idx << " ";
    }

    // insert new samples
    for(int idx=0; idx<nframes; idx++)
    {
        // only take the first channels
        //fft_in[L-nframes+idx] = in[0][idx] * get_triangular_sample(L-nframes+idx,L);
        fft_in[L-nframes+idx] = in[0][idx]; // * get_hann_sample(L-nframes+idx,L);
        // cout << idx << " ";
    }

    fftw_execute(p_fft);

    for(int tmpCNT = 0;tmpCNT<L_fft; tmpCNT++)
    {
        power_spectrum[tmpCNT] = fft_out[tmpCNT][0] *fft_out[tmpCNT][0]  + fft_out[tmpCNT][1]*fft_out[tmpCNT][1];
        //        cout << power_spectrum[tmpCNT] << " ";
    }
    //    cout << endl;

    fftw_execute(p_ifft);

    // copy recent ifft result to matrix
    for(int tmpCNT = 0;tmpCNT< L; tmpCNT++)
    {
        ifft_out[ifft_index][tmpCNT] = ifft_buff[tmpCNT]* get_hann_sample(tmpCNT,L);

        // cout << ifft_buff[tmpCNT] << " ";
        // cout << ifft_out[ifft_index][tmpCNT] << " ";

    }
    // cout << endl;

    // delete-loop
    for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
    {
        for(int sampCNT=0; sampCNT<nframes; sampCNT++)
            out[chanCNT][sampCNT] = 0.0;
    }

    // write all input samples to output
    for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
    {

        // the overlap add
        for(int bufCNT=0; bufCNT<n_buffers; bufCNT++)
        {

            uint buf_ind  = 0;
            float outsamp = 0;

            for(int sampCNT=0; sampCNT<nframes; sampCNT++)
            {

                // the INDIVIDUAL ola index for each buffer
                buf_ind = (sampCNT + (ifft_index * nframes) - (bufCNT*nframes)  )%L;

                // outsamp =  get_triangular_sample(buf_ind,L);
                outsamp = (ifft_out[bufCNT][buf_ind] / (L_fft+n_overlap)); // * get_hann_sample(buf_ind,L);

                out[chanCNT][sampCNT] += outsamp*0.25;

                // cout << ifft_index << " ";

                cout << buf_ind << " ";
                // cout << outsamp << " ";
                // cout << ifft_out[bufCNT][buf_ind] << " ";


            }

            // cout << buf_ind << " ";
            cout << endl;
        }
    }

    ifft_index++;
    if(ifft_index>=n_buffers)
        ifft_index=0;

    return 0;
}

int Zerr::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<Zerr*>(object)->process(x);
}

float Zerr::get_hann_sample(int pos, int L)
{
    float val = 0.5 * (1.0 - cos( (2.0*PI* (float) pos) / (float)L) );
    return val;
}

float Zerr::get_triangular_sample(int pos, int L)
{
    float val = 0;

    if( ((float) pos) < ((float) L / 2.0))
        val  = (1.0 / ( L/2.0)) *   pos;
    else
        val =  1.0 - ((1.0 / ( L/2.0))  *   ((float)pos-((float)L/2.0)));

    return val;
}
