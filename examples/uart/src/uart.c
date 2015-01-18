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

int main(void) {
  GPIO_InitTypeDef gpio_cfg;

  nm_systick_init();
  nm_debug_init();

  gpio_cfg.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_cfg);

  while(1) {
	printf("Hello, world!\n");
	fprintf(stderr, "INTERRUPT\n");

	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_SET);
	nm_systick_delay(250);
	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_RESET);
	nm_systick_delay(250);
  }

  return 0;
}
