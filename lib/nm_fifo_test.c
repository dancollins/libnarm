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
#include "nm_fifo.h"

int main(void) {
  uint8_t fifo_buf[64];
  nm_fifo_t fifo;
  uint8_t fifo_out[65];
  uint8_t l[1];
  uint8_t r; 
  nm_fifo_init(&fifo, fifo_buf, sizeof(fifo_buf));

 
  for(uint8_t i=0; i<32; i++){
    *l=  i+'0';
    if(nm_fifo_write(&fifo, l, 1) != 1){ 
      fprintf(stderr, "didnt write: %u\n", i+1);
    }
  }

  fifo_out[64]='\0'; //set null terminator
  r = nm_fifo_read(&fifo, fifo_out, 64);
  fprintf(stderr, "output %u: %s\n", r, fifo_out);

  
  for(uint8_t i=0; i<70; i++){
    *l=  i+'0';
    if(nm_fifo_write(&fifo, l, 1) != 1){ 
      fprintf(stderr, "didnt write: %u\n", i+1);
    }
  }
  fifo_out[64]='\0'; //set null terminator
  r= nm_fifo_read(&fifo, fifo_out, 70);
  fprintf(stderr, "output %u: %s\n", r, fifo_out);

  return 0;
}
