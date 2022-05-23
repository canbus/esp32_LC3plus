#include "lc3.h"

#include "esp_lc3plus.h"


int          nBytes = 0, i = 0;
unsigned int nSamples = 0, nSamplesRead = 0, nSamplesFile = 0xffffffff, sampleRate = 48000;
short        nChannels = 2, bipsIn = 24;
int          real_bitrate = 0, frame = 1, delay = 0;
int          encoder_size = 0;
int          bfi_ext = 0;
LC3PLUS_Enc*     encoder                                        = NULL;
LC3PLUS_Error    err                                            = LC3PLUS_OK;
int32_t      sample_buf[LC3PLUS_MAX_CHANNELS * LC3PLUS_MAX_SAMPLES] = {0};
int32_t      buf_24[LC3PLUS_MAX_CHANNELS * LC3PLUS_MAX_SAMPLES]     = {0};
int16_t      buf_16[LC3PLUS_MAX_CHANNELS * LC3PLUS_MAX_SAMPLES]     = {0};
uint8_t      bytes[LC3PLUS_MAX_CHANNELS * LC3PLUS_MAX_BYTES]        = {0};
int          dc2_extra_frame                                = 0;
int epmode = 0;
int epmr = 0;
int cur_epmode = 0, cur_epmr = 0;
float frame_ms = 10;
int32_t lfe = 0;
int bitrate = 0;
int dc = 0;


esp_err_t lc3plus_init(void)
{
    /* Setup Encoder */
    encoder_size = lc3plus_enc_get_size(sampleRate, nChannels);
    encoder = malloc(encoder_size);
    err = lc3plus_enc_init(encoder, sampleRate, nChannels);
    // exit_if(err, ERROR_MESSAGE[err]);
    err = lc3plus_enc_set_frame_ms(encoder, frame_ms);
    // exit_if(err, ERROR_MESSAGE[err]);


    cur_epmode = (LC3PLUS_EpMode)epmode;
    err        = lc3plus_enc_set_ep_mode(encoder, (LC3PLUS_EpMode)epmode);
    // exit_if(err, ERROR_MESSAGE[err]);
    cur_epmr = (LC3PLUS_EpModeRequest)epmr;
    err      = lc3plus_enc_set_ep_mode_request(encoder, (LC3PLUS_EpModeRequest)epmr);
    // exit_if(err, ERROR_MESSAGE[err]);
    
    err = lc3plus_enc_set_lfe(encoder, lfe);
    // exit_if(err, ERROR_MESSAGE[err]);
    err = lc3plus_enc_set_bitrate(encoder, bitrate);
    // exit_if(err, ERROR_MESSAGE[err]);
    delay        = dc ? lc3plus_enc_get_delay(encoder) / dc : 0;
    nSamples     = lc3plus_enc_get_input_samples(encoder);
    real_bitrate = lc3plus_enc_get_real_bitrate(encoder);


    /* Print out info */
    printf("Encoder size:                  %i\n", encoder_size);
    // printf("Decoder size:                  %i\n", decoder_size);
    printf("Sample rate:                   %i\n", sampleRate);
    printf("Channels:                      %i\n", nChannels);
    printf("Signal length:                 %u\n", nSamplesFile);
    printf("Frame length:                  %i\n", nSamples);
    // printf("Output format:                 %i bit\n", arg.bipsOut);
    printf("Target bitrate:                %i\n", bitrate);
    printf("Real bitrate:                  %i\n", real_bitrate);
    // printf("Bandwidth cutoff:              %s\n", arg.bandwidth ? arg.bandwidth : "-");
    // printf("High resolution mode:          %s\n\n", arg.hrmode ? "on" : "off");
    // printf("PLC mode:                      %i\n", arg.plcMeth);


    return ESP_OK;
}

esp_err_t lc3plus_enc(int32_t *samples, uint8_t *out_bytes)
{
    /* Encoder */
    int32_t* input24[LC3PLUS_MAX_CHANNELS];
    for (i = 0; i < nChannels; i++) {
        input24[i] = buf_24 + i * nSamples;
    }

    /* read audio data */
    // ReadWavInt(input_wav, sample_buf, nSamples * nChannels, &nSamplesRead);
    memcpy(sample_buf,samples,(nSamples * nChannels) * sizeof(sample_buf[0]));
    /* zero out rest of last frame */
    // memset(sample_buf + nSamplesRead, 0, (nSamples * nChannels - nSamplesRead) * sizeof(sample_buf[0]));

    /* deinterleave channels */
    deinterleave(sample_buf, input24, nSamples, nChannels);

    /* encode */

    if (bipsIn == 24) {
        err = lc3plus_enc24(encoder, input24, bytes, &nBytes);
    } else {
        int16_t* input16[LC3PLUS_MAX_CHANNELS];

        for (i = 0; i < nChannels; i++) {
            input16[i] = buf_16 + i * nSamples;
        }

        scale_24_to_16(buf_24, buf_16, nSamples * nChannels);
        err = lc3plus_enc16(encoder, input16, bytes, &nBytes);
    }

    memcpy(out_bytes, bytes, nBytes);

    return ESP_OK;
}



void scale_24_to_16(const int32_t* in, int16_t* out, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        out[i] = in[i];
    }
}

void scale_16_to_24(const int16_t* in, int32_t* out, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        out[i] = in[i];
    }
}

void interleave(int32_t** in, int32_t* out, int n, int channels)
{
    int ch, i;
    for (ch = 0; ch < channels; ch++) {
        for (i = 0; i < n; i++) {
            out[i * channels + ch] = in[ch][i];
        }
    }
}
 
 void deinterleave(int32_t* in, int32_t** out, int n, int channels)
{
    int ch, i;
    for (ch = 0; ch < channels; ch++) {
        for (i = 0; i < n; i++) {
            out[ch][i] = in[i * channels + ch];
        }
    }
}
