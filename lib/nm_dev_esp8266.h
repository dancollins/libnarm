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
#ifndef _NM_DEV_ESP8266_H
#define _NM_DEV_ESP8266_H

#include <stdint.h>
#include "nm_fifo.h"

typedef struct{
  uint8_t tx_buf[64];
  uint8_t rx_buf[64];
  nm_fifo_t tx_fifo;
  nm_fifo_t rx_fifo;
}nm_dev_esp8266_t;

#endif /* _NM_DEV_ESP8266_H */
