/**
 * @file iec_hardware.h
 * @brief main header
 * @copyright 2022 Emiliano Augusto Gonzalez (hiperiondev). This project is released under MIT license.
 * Contact: egonzalez.hiperion@gmail.com
 * @see https://github.com/hiperiondev/iec61131lib
 * Project Site: https://github.com/hiperiondev/iec61131lib
 *
 * This is based on other projects:
 *
 *    Others (see individual files)
 *
 *    please contact their authors for more information.
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef FUN_HARDWARE_H_
#define FUN_HARDWARE_H_

#include <stdint.h>

#ifdef ALLOW_64BITS
/**
 * @fn uint32_t hw_millis(void)
 * @brief
 *
 * @return
 */
uint64_t hw_millis(void) {
    return 0;
}

/**
 * @fn uint32_t hw_millis(void)
 * @brief
 *
 * @return
 */
uint64_t hw_micros(void) {
    return 0;
}
#else
/**
 * @fn uint32_t hw_millis(void)
 * @brief
 *
 * @return
 */
uint32_t hw_millis(void) {
    return 0;
}

/**
 * @fn uint32_t hw_micros(void)
 * @brief
 *
 * @return
 */
uint32_t hw_micros(void) {
    return 0;
}
#endif

#endif /* FUN_HARDWARE_H_ */
