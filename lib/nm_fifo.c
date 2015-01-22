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
 
#include "nm_fifo.h"

int8_t nm_fifo_init(nm_fifo_t* fifo, uint8_t* buffer, uint8_t size){
  if(fifo && buffer && size>0){
    fifo->buf = buffer;
    fifo->size=size;
    fifo->free=size;
    fifo->head = 0;
    fifo->tail = 0;
    return 0;
  }
  return -1;
}

uint8_t nm_fifo_write(nm_fifo_t* fifo, uint8_t* ptr, uint8_t len) {
  uint8_t i;
  if(fifo && ptr && len>0){
    for(i=0; i<len && fifo->free>0; i++){
      fifo->buf[fifo->head] = ptr[i];
      fifo->free--;
      fifo->head=(fifo->head+1)%fifo->size;
    }
    //fprintf(stderr, "Wrote: %u, Free: %u\n",  i, fifo->free);
    return i;
  }
  return 0;
}

uint8_t nm_fifo_read(nm_fifo_t* fifo, uint8_t* dst, uint8_t len){
  uint8_t i;
  if(fifo && dst && len>0){
    for(i=0; i<len && (fifo->free < fifo->size); i++){
        dst[i] = fifo->buf[fifo->tail];
        fifo->free++;
        fifo->tail=(fifo->tail+1)%fifo->size;
    }
    //fprintf(stderr, "Read: %u, Free: %u\n",  i, fifo->free);
    return i;
  }
  return 0;
}

