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
#include "libnarm.h"

#include "stm32f0xx.h"

static volatile char debug_buf[256];
static volatile uint8_t debug_head, debug_tail, debug_on;

void nm_debug_init(void) {
  GPIO_InitTypeDef gpio_cfg;
  USART_InitTypeDef uart_cfg;
  NVIC_InitTypeDef nvic_cfg;

  /* Enable clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* Connect the pins to the USART */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

  /* Set TX and RX pins as AF PP output */
  gpio_cfg.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  gpio_cfg.GPIO_Mode = GPIO_Mode_AF;
  gpio_cfg.GPIO_Speed = GPIO_Speed_10MHz;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &gpio_cfg);

  /* Configure USART as 115200bps 8N1 with no flow control */
  uart_cfg.USART_BaudRate = 115200;
  uart_cfg.USART_WordLength = USART_WordLength_8b;
  uart_cfg.USART_StopBits = USART_StopBits_1;
  uart_cfg.USART_Parity = USART_Parity_No;
  uart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  uart_cfg.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART2, &uart_cfg);

  USART_Cmd(USART2, ENABLE);

  /* Configure USART2 interrupts */
  /* XXX: Find out what priority we should use */
  nvic_cfg.NVIC_IRQChannel = USART2_IRQn;
  nvic_cfg.NVIC_IRQChannelPriority = 1;
  nvic_cfg.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_cfg);

  debug_head = 0;
  debug_tail = 0;
  debug_on = 0;
}

uint8_t nm_debug_write(char *ptr, uint8_t len) {
  uint8_t i;
  uint8_t free_space = (debug_tail - debug_head) - 1;
  len = len > free_space ? free_space : len;

  for (i = 0; i < len; i++)
	debug_buf[debug_head++] = ptr[i];

  /* Start the transmission if it's not already */
  if (!debug_on) {
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	USART_SendData(USART2, debug_buf[debug_tail++]);

	debug_on = 1;
  }

  return i;
}

void USART2_IRQHandler(void) {
  if (USART_GetITStatus(USART2, USART_IT_TXE) == SET) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_SET);
	/* Check to see if we're done */
	if (debug_tail == debug_head) {
	  USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	  debug_on = 0;
	} else {
	  USART_SendData(USART2, debug_buf[debug_tail++]);
	}
  }
}
