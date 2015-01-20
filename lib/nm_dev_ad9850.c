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


#include "nm_dev_ad9850.h"
 
/* dss clock data */
inline void nm_AD9850_clk(nm_AD9850_t* dss){
  GPIO_WriteBit(GPIOA, dss->w_clk_pin, 1);
  GPIO_WriteBit(GPIOA, dss->w_clk_pin, 0);
}

/* dss frequancy update */
inline void nm_AD9850_fqud(nm_AD9850_t* dss){
  GPIO_WriteBit(GPIOA, dss->fq_ud_pin, 1);
  GPIO_WriteBit(GPIOA, dss->fq_ud_pin, 0);
}

/* dss write serial byte */
static void nm_AD9850_write(nm_AD9850_t* dss){ 
  uint8_t i,j;
  nm_AD9850_fqud(dss);
  for(j=0; j<5; j++){
    for(i=0; i<8; i++){
      GPIO_WriteBit(GPIOA, dss->data_pin, (dss->reg[j]>>i)&0x01);
      nm_AD9850_clk(dss);
    }
  }
  nm_AD9850_fqud(dss);
}

void nm_AD9850_set_powerdown(nm_AD9850_t* dss, uint8_t powerdown){
  
  dss->reg[4] = ( ( powerdown & 0x1 )<<2) | ( dss->reg[4] & ~(1<<2) );
  nm_AD9850_write(dss); //write out
  
}

void nm_AD9850_set_frequency(nm_AD9850_t* dss, double Freq){
  
  //fout = (reg * clkin)/2^32 -- From data sheet
  //freq = (reg * 125)/2^32
  //freq * 2^32 / 125 = reg

  uint32_t* reg = (uint32_t *)&dss->reg[0];
  *reg = lround ( (Freq*pow(2,32))/125.0d );
  nm_AD9850_write(dss);	//write out
  
}

void nm_AD9850_correct_frequency(nm_AD9850_t* dss, double ppm){
  uint32_t* reg = (uint32_t *)&dss->reg[0];
  
  double freq = ((*reg)*125.0d)/pow(2,32);
  freq = (2.0d*freq) - ((freq) * (1.0d + (ppm) / 1000000.0d));
  nm_AD9850_set_frequency(dss, freq);
  
}

void nm_AD9850_set_phase(nm_AD9850_t* dss, uint8_t phase){
  dss->reg[4] = (phase<<3) | ( dss->reg[4] & 0b00000111);
  nm_AD9850_write(dss);	//write out
}

void nm_AD9850_init(nm_AD9850_t* dss){
  
  for(uint8_t x=0; x < 5; x++){
    dss->reg[x]=0;
  }
  
  GPIO_InitTypeDef gpio_cfg;
  gpio_cfg.GPIO_Pin = dss->w_clk_pin | dss->fq_ud_pin | dss->data_pin | dss->reset_pin;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(dss->gpio_port, &gpio_cfg);

  //set all outputs low
  GPIO_WriteBit(GPIOA, dss->w_clk_pin , 0);
  GPIO_WriteBit(GPIOA, dss->fq_ud_pin , 0);
  GPIO_WriteBit(GPIOA, dss->data_pin  , 0);
  GPIO_WriteBit(GPIOA, dss->reset_pin , 0); 
  
}
