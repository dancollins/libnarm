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
#ifndef _NM_SYSTICK_H
#define _NM_SYSTICK_H

#include <stdint.h>

/**
 * Prepares the systick timer for use.
 * This must be called before any other systick function. Multiple calls
 * are safe.
 */
extern void nm_systick_init(void);

/**
 * Creates a blocking delay for the given period.
 *
 * @param ms number of milliseconds to delay for
 */
extern void nm_systick_delay(uint32_t ms);

/**
 * Gets the number of ticks since the last call to nm_systick_init.
 *
 * @returns the number of ticks since the last call to nm_systick_init
 */
extern uint32_t nm_systick_get_ticks(void);

#endif /* _NM_SYSTICK_H */
