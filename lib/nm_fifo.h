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
 
#ifndef _NM_FIFO_H
#define _NM_FIFO_H

#include <stdint.h>
#include <stdio.h>

typedef struct{
  uint8_t head;
  uint8_t tail;
  uint8_t size;
  uint8_t free;
  uint8_t* buf;
}nm_fifo_t;

/**
 * initates the fifo data structure
 *
 * @param fifo is pointer to fifo state
 * @param buffer pointer to the underlying buffer
 * @param size of buffer should be a power of 2 for best performance
 * @returns 0 on sucsesse and < 0 on failure
 */
int8_t nm_fifo_init(nm_fifo_t* fifo, uint8_t* buffer, uint8_t size);


uint8_t nm_fifo_write(nm_fifo_t* fifo, uint8_t* ptr, uint8_t len);
uint8_t nm_fifo_read(nm_fifo_t* fifo, uint8_t* dst, uint8_t len);

#endif /* _NM_FIFO_H */
