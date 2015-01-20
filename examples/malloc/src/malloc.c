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
#include <stdlib.h>
#include <stdio.h>

#include <stm32f0xx.h>

#include "libnarm.h"

int main(void) {
  GPIO_InitTypeDef gpio_cfg;
  char *dynamic_buffer = NULL;

  nm_systick_init();
  nm_debug_init();

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  gpio_cfg.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  gpio_cfg.GPIO_Speed = GPIO_Speed_Level_3;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_cfg);

  GPIO_WriteBit(GPIOA, GPIO_Pin_14 | GPIO_Pin_15, Bit_RESET);

  while(1) {
	/* Allocate a block */
	dynamic_buffer = (char *)malloc(1024);
	if (dynamic_buffer == NULL) {
	  fprintf(stderr, "Failed to allocate dynamic memory!\n");
	  GPIO_WriteBit(GPIOA, GPIO_Pin_14 | GPIO_Pin_15, Bit_SET);
	  while(1)
		;
	}

	/* Use the block for something */
	snprintf(dynamic_buffer, 1024, "hello, world!");
	printf("123456789: %s\n", dynamic_buffer);

	/* Remove the block */
	free(dynamic_buffer);
	dynamic_buffer = NULL;

	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_RESET);
	nm_systick_delay(250);
	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_SET);
	nm_systick_delay(250);
  }
}
