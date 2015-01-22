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

#include "nm_dev_esp8266.h"

//TODO: setup UART
int8_t nm_dev_esp8266_init(nm_dev_esp8266_t* dev){
  if(dev){
    nm_fifo_init(&dev->tx_fifo, dev->tx_buf, sizeof(dev->tx_buf));
    nm_fifo_init(&dev->rx_fifo, dev->rx_buf, sizeof(dev->rx_buf));


    return 0;
  }
  return -1;
}
