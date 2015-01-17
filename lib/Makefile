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
PROJECT = libnarm

# Add project sources
SRCS_C = \
	nm_debug.c \
	nm_systick.c \
	syscalls.c

#
# VENDOR
#
# Include the STM headers
STM_DIR = \
	../vendor

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
CFLAGS+=-Os -flto -ffunction-sections -fdata-sections
CFLAGS+=-fno-builtin

CFLAGS += -I.
CFLAGS += $(addprefix -I$(STM_DIR)/, $(STM_INCLUDE))

OBJS = \
	$(addprefix build/, $(SRCS_C:.c=.o)) \
	$(addprefix build/, $(SRCS_S:.S=.o))


#
# BUILD RULES
#
.PHONY: all clean

all: clean $(PROJECT).a

build/%.o: %.c
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

build/%.o: %.S
	$(MKDIR) -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@

$(PROJECT).a: $(OBJS)
	$(AR) -r $@ $^

clean:
	rm -rf build
	rm -rf $(PROJECT).a


#
# TOOLCHAIN
#
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size
MKDIR=mkdir

