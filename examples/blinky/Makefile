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

# Project Name
PROJECT = blinky

# Add project sources
SRCS_C = \
	blinky.c \
	system_stm32f0xx.c

SRCS_H =

SRCS_S = \
	startup_stm32f051.S

# Add project include directories here
INCLUDE = src


#
# VENDOR
#
# Include the STM code
STM_DIR = \
	../../vendor

STM_SRCS_C = \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_gpio.c \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_misc.c \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rcc.c \

STM_INCLUDE = \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/inc \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Include \
	STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Device/ST/STM32F0xx/Include

STM_DEFS = \
	-DUSE_STDPERIPH_DRIVER \
	-DSTM32F051

#
# COMPILER FLAGS
#
ARCH_FLAGS=-mthumb -mcpu=cortex-m0 -mfloat-abi=soft

GC=-Wl,--gc-sections
MAP=-Wl,-Map=$(PROJECT).map

CFLAGS=$(ARCH_FLAGS) $(STM_DEFS)
CFLAGS+=-Wall -Werror -g -std=gnu99
CFLAGS+=-O0 -flto -ffunction-sections -fdata-sections
CFLAGS+=-fno-builtin

CFLAGS += $(addprefix -I, $(INCLUDE))
CFLAGS += $(addprefix -I, ../../lib)
CFLAGS += $(addprefix -I$(STM_DIR)/, $(STM_INCLUDE))

LDSCRIPTS=-Lsrc -T stm32f051k8_flash.ld
LFLAGS=--specs=nano.specs -lc -lnosys $(LDSCRIPTS) $(GC) $(MAP)

LFLAGS += -lnarm -L../../lib

OBJS = \
	$(addprefix build/, $(SRCS_C:.c=.o)) \
	$(addprefix build/, $(SRCS_S:.S=.o)) \
	$(addprefix build/vendor/, $(STM_SRCS_C:.c=.o)) \
	$(addprefix build/vendor/, $(STM_SRCS_S:.S=.o))


#
# BUILD RULES
#
.PHONY: all clean

all: clean output/$(PROJECT).elf

build/%.o: src/%.c
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

build/%.o: src/%.S
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

build/vendor/%.o: $(STM_DIR)/%.c
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

build/vendor/%.o: $(STM_DIR)/%.s
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

output/$(PROJECT).elf: $(OBJS)
	$(MKDIR) -p output
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
	$(OBJCOPY) -O binary output/$(PROJECT).elf output/$(PROJECT).bin
	$(OBJCOPY) -O ihex output/$(PROJECT).elf output/$(PROJECT).hex
	$(OBJDUMP) -St -marm output/$(PROJECT).elf > output/$(PROJECT).lst
	$(SIZE) output/$(PROJECT).elf

clean:
	rm -rf build
	rm -rf output


#
# TOOLCHAIN
#
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size
MKDIR=mkdir

