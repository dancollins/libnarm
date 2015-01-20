/*   Copyright 2015 Dan Collins & Tim Dawson
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
 
#ifndef _NM_DEV_AD9850_H
#define _NM_DEV_AD9850_H


#include <stm32f0xx.h> //TODO: replace this with a generic header, mabey an abstration layer
#include "math.h"

typedef struct{
  GPIO_TypeDef* gpio_port;
  uint16_t  w_clk_pin;
  uint16_t  fq_ud_pin;
  uint16_t  data_pin;
  uint16_t  reset_pin;
  uint8_t   reg[5]; //this is the data that is sent to the dss
}nm_AD9850_t;



extern void nm_AD9850_init(nm_AD9850_t* dss);
extern void nm_AD9850_set_phase(nm_AD9850_t* dss, uint8_t phase);
extern void nm_AD9850_correct_frequency(nm_AD9850_t* dss, double ppm);
extern void nm_AD9850_set_frequency(nm_AD9850_t* dss, double Freq);

#endif /* _NM_DEV_AD9850_H */
