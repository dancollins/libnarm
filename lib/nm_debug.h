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
#ifndef _NM_DEBUG_H
#define _NM_DEBUG_H

#include <stdint.h>

/**
 * Prepares the debug library for use.
 * This must be called before any other calls to the debug library. Multiple
 * calls wont break anything.
 */
extern void nm_debug_init(void);

/**
 * Send debug strings to the USART port.
 *
 * @param ptr pointer to the buffer containing data to send
 * @param len number of bytes to send
 * @returns number of bytes added to the buffer
 */
extern uint8_t nm_debug_write(char *ptr, uint8_t len);

#endif /* _NM_DEBUG_H */
