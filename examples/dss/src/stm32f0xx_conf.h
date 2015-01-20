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

#ifndef _stm32_conf_h
#define _stm32_conf_h

/* Define this if you want the STM library to provide assertions */
/*#define STM_ASSERT*/

/* You can comment out any headers you don't need, but this doesn't affect
 * the binary size because the linker trims out stuff that's not used. */
#include "stm32f0xx_adc.h"
#include "stm32f0xx_can.h"
#include "stm32f0xx_cec.h"
#include "stm32f0xx_crc.h"
#include "stm32f0xx_crs.h"
#include "stm32f0xx_comp.h"
#include "stm32f0xx_dac.h"
#include "stm32f0xx_dbgmcu.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_flash.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_syscfg.h"
#include "stm32f0xx_i2c.h"
#include "stm32f0xx_iwdg.h"
#include "stm32f0xx_pwr.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_rtc.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_wwdg.h"
#include "stm32f0xx_misc.h"

#ifdef STM_ASSERT
#error "Assertions don't work in narm yet!"
#else
#define assert_param(expr) ((void)0)
#endif

#endif /* _stm32_conf_h */
