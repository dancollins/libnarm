#   Copyright 2015 Dan Collins & Tim Dawson
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

vpath %.c STM32F0xx_StdPeriph_Driver/src

# All the sources we want to include in the library
STM32_SRC = \
	stm32f0xx_adc.c \
	stm32f0xx_can.c \
	stm32f0xx_cec.c \
	stm32f0xx_comp.c \
	stm32f0xx_crc.c \
	stm32f0xx_crs.c \
	stm32f0xx_dac.c \
	stm32f0xx_dbgmcu.c \
	stm32f0xx_dma.c \
	stm32f0xx_exti.c \
	stm32f0xx_flash.c \
	stm32f0xx_gpio.c \
	stm32f0xx_i2c.c \
	stm32f0xx_iwdg.c \
	stm32f0xx_misc.c \
	stm32f0xx_pwr.c \
	stm32f0xx_rcc.c \
	stm32f0xx_rtc.c \
	stm32f0xx_spi.c \
	stm32f0xx_syscfg.c \
	stm32f0xx_tim.c \
	stm32f0xx_usart.c \
	stm32f0xx_wwdg.c

INCLUDE = \
	STM32F0xx_StdPeriph_Driver/inc \
	CMSIS/Include \
	CMSIS/Device/ST/STM32F0xx/Include

#
# COMPILER FLAGS
#
ARCH_FLAGS = -mthumb -mcpu=cortex-m0 -mfloat-abi=soft

CFLAGS = $(ARCH_FLAGS)
CFLAGS += -ffreestanding -nostdlib
CFLAGS += -fdata-sections -ffunction-sections

CFLAGS += -include ../Projects/STM32F0xx_StdPeriph_Templates/stm32f0xx_conf.h
CFLAGS += $(addprefix -I, $(INCLUDE))

OBJS = $(addprefix objs/, $(STM32_SRC:.c=.o))

.PHONY: all clean

all: libstm32f0xx.a

objs/%.o: %.c
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

libstm32f0xx.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	$(RM) -rf objs deps

#
# TOOLCHAIN
#
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
MKDIR=mkdir
RM=rm
