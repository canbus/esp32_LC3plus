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
esp_err_t lc3plus_enc(void);