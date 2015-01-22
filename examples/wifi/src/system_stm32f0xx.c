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

/*
 * This file provides functions to set up the internal clocks and flash. Most
 * of this is called by the startup file and the user doesn't need to worry
 * about it. However, if the user wants to make changes to the clock during
 * execution (like moving to a low power clock) they should pay attention to
 * system_clock_update().
 *
 * The default configuration will be to use the internal 8MHz oscillator through
 * the PLL to create a 48MHz system clock.
 */

#include <stm32f0xx.h>

/* This global variable holds the value of the HCLK */
uint32_t SystemCoreClock = 48000000;

/* Look up table for the AHB prescaler. This helps us calculate HCLK */
static const volatile uint8_t ahb_prescale_lut[16] = {
  0, 0, 0, 0, 0, 0, 0, 1,
  2, 3, 4, 5, 6, 7, 8, 9
};

/* Sets the system clock, AHB/APBx prescalers and flash settings.
 * This function should be called once the RCC clock config is reset to
 * the default state (which is done by system_clock_init()) */
static void SetSysClock(void) {
  /* Enable prefetch buffer and set flash latency */
  FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

  /* HCLK = SYSCLK */
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

  /* PCLK = HCLK */
  RCC->CFGR |= RCC_CFGR_PPRE_DIV1;

  /* PLL configuration */
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
  RCC->CFGR |= (RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLXTPRE_PREDIV1 |
				RCC_CFGR_PLLMULL12);

  /* Enable PLL */
  RCC->CR |= RCC_CR_PLLON;

  /* Do nothing until the PLL is ready */
  while (!(RCC->CR & RCC_CR_PLLRDY))
	;

  /* Slect the PLL as system clock */
  RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  /* Do nothing until the PLL is used as system clock */
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
	;
}

/* Set up the clocks and the flash */
void SystemInit(void) {
  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset RCC registers */
  RCC->CR &= 0xFEF2FFFF;
  RCC->CR2 &= 0xffffffe;
  RCC->CFGR &= 0xf8c0b80c;
  RCC->CFGR2 &= 0xfffffff0;
  RCC->CFGR3 &= 0xfffffeac;

  /* Disable all interrupts */
  RCC->CIR = 0;

  /* Set system clock, AHB/APBx prescalers and flash settings */
  SetSysClock();
}

/* If the user makes changes to the clock registers, they can call this to
 * push the changes. This will also update the glocal clock speed variable */
void SystemCoreClockUpdate(void) {
  uint32_t tmp, pllmull, pllsrc, plldiv;

  /* Get the SYSCLK source */
  tmp = RCC->CFGR & RCC_CFGR_SWS;

  /* Clock value depends on clock source */
  switch (tmp) {
  case 0x0: /* HSI */
	SystemCoreClock = HSI_VALUE;
	break;

  case 0x4: /* HSE */
	SystemCoreClock = HSE_VALUE;
	break;

  case 0x8: /* PLL */
	pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
	pllsrc = RCC->CFGR & RCC_CFGR_PLLSRC;
	pllmull = (pllmull >> 18) + 2;

	if (pllsrc) {
	  plldiv = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
	  SystemCoreClock = (HSE_VALUE / plldiv) * pllmull;
	} else {
	  SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
	}
	break;

  default:
	SystemCoreClock = HSI_VALUE;
	break;
  }

  /* Calculate HCLK frequency */
  tmp = ahb_prescale_lut[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  SystemCoreClock >>= tmp;
}
