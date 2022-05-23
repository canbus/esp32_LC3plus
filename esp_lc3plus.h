/*
 *  B&O Classics Adaptor
 *
 *  i2c module
 *
 *  LAPJ/KANK
 *  2022
 * 
*/

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "esp_err.h"



esp_err_t lc3plus_init(void);
esp_err_t lc3plus_enc(int32_t *samples, uint8_t *out_bytes);

void scale_24_to_16(const int32_t* in, int16_t* out, int n);
void scale_16_to_24(const int16_t* in, int32_t* out, int n);
void interleave(int32_t** in, int32_t* out, int n, int channels);
void deinterleave(int32_t* in, int32_t** out, int n, int channels);