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

#include <stdio.h>

#include <stm32f0xx.h>

#include "libnarm.h"
#include "math.h"

int main(void) {
  GPIO_InitTypeDef gpio_cfg;
  nm_AD9850_t dss;
  
  nm_systick_init();
  nm_debug_init();

  gpio_cfg.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_cfg);

  //Setup DSS
  dss.gpio_port = GPIOA;
  dss.w_clk_pin = GPIO_Pin_4;
  dss.fq_ud_pin = GPIO_Pin_5;
  dss.data_pin  = GPIO_Pin_6;
  dss.reset_pin = GPIO_Pin_7;
  nm_AD9850_init(&dss);
  
  nm_AD9850_set_frequency(&dss, 28.8); //set 28.8MHz
  nm_AD9850_correct_frequency(&dss, -15.0d);
  nm_AD9850_correct_frequency(&dss, -2.481378d);
  nm_AD9850_correct_frequency(&dss, -0.003561d);
  
  
  while(1) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_SET);
    nm_systick_delay(500);
    GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_RESET);
    nm_systick_delay(500);
  }

  return 0;
}
