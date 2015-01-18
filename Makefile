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

.PHONY: all clean

all:
	$(MAKE) -C lib
	$(MAKE) -C vendor/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries
	$(MAKE) -C examples/blinky
	$(MAKE) -C examples/malloc
	$(MAKE) -C examples/uart

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C vendor/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries clean
	$(MAKE) -C examples/blinky clean
	$(MAKE) -C examples/malloc clean
	$(MAKE) -C examples/uart clean

#
# Toolchain
#
MAKE=make
