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
#include <unistd.h>

#include <stm32f0xx.h>

volatile uint32_t TimingDelay = 0;
void delay(uint32_t ticks);

void nm_debug_init(void) {
  GPIO_InitTypeDef gpio_cfg;
  USART_InitTypeDef uart_cfg;

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
}

int _write(int fd, char *ptr, int len) {
  int ret;

  switch(fd) {
  case STDOUT_FILENO:
	for (int i = 0; i < len; i++) {
	  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
		;
	  USART_SendData(USART2, ptr[i]);
	}
	ret = len;
	break;

  default:
	ret = -1;
	break;
  }

  return ret;
}

int main(void) {
  GPIO_InitTypeDef gpio_cfg;

  /* SysTick interrupt every 1ms */
  SysTick_Config(SystemCoreClock / 1000);

  nm_debug_init();

  gpio_cfg.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_cfg);

  while(1) {
	printf("Hello, world!\n");

	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_SET);
	delay(250);
	GPIO_WriteBit(GPIOA, GPIO_Pin_14, Bit_RESET);
	delay(250);
  }

  return 0;
}

/* Create a delay for the given systicks */
void delay(uint32_t ticks) {
	TimingDelay = ticks;
	while (TimingDelay != 0);
}

/* Override the systick handler */
void SysTick_Handler(void) {
	if (TimingDelay != 0)
		TimingDelay--;
}

