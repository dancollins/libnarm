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
#include <unistd.h>

#include "stm32f0xx.h"

#include "libnarm.h"

int _write(int fd, char *ptr, int len) {
  int ret;

  switch(fd) {
  case STDOUT_FILENO:
	/* stdout is buffered through a simple ring buffer to keep performance
	 * up */
	ret = nm_debug_write(ptr, len);
	break;

  case STDERR_FILENO:
	/* stderr isn't buffered, and there's a chance stdout is trying to use
	 * the USART port. So we pause stdout, write all our data out the port,
	 * and then unpause stdout. The last byte from stderr will cause an
	 * interrupt which will let stdout continue */
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

	for (int i = 0; i < len; i++) {
	  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
		;
	  USART_SendData(USART2, ptr[i]);
	}

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

	ret = len;
	break;

  default:
	ret = -1;
	break;
  }

  return ret;
}
