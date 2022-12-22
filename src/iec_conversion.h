/**
 * @file iec_conversion.h
 * @brief
 * @copyright 2022 Emiliano Augusto Gonzalez (hiperiondev). This project is released under MIT license. Contact: egonzalez.hiperion@gmail.com
 * @see Project Site: https://github.com/hiperiondev/iec61131lib
 * @note This is based on other projects. Please contact their authors for more information.
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

#ifndef IEC_CONVERSION_H_
#define IEC_CONVERSION_H_

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 * TO             ANY                     1            Simple conversion, changing from type * to type **
 * TRUNC          (note 1)                1            Real to integer conversion, changing from real type * to integer type **
 * BCD_TO         (note 2)                1            Change from Binary Coded Decimal (BCD) type * to integer type **
 * TO_BCD         (note 3)                1            Change from integer type * to Binary Coded Decimal (BCD) type **
 *
 * note 1: The from (*) type can be REAL or LREAL. The to (**) type can be SINT, USINT, INT, UINT, DINT, UDINT, LINT, or ULINT
 * note 2: allowed
 *   BYTE_BCD_TO_SINT: Convert two BCD digits encoded in a BYTE to a small integer (SINT).
 *   WORD_BCD_TO_INT: Convert four BCD digits encoded in a WORD to an integer (INT).
 *   DWORD_BCD_TO_DINT: Convert eight BCD digits encoded in a DWORD to a double integer (DINT).
 *   LWORD_BCD_TO_LINT: Convert sixteen BCD digits encoded in a LWORD to a long integer (LINT).
 * note 3: allowed
 *   SINT_TO_BCD_BYTE: Convert a small integer (SINT) to two BCD digits encoded in a BYTE.
 *   INT_TO_BCD_WORD: Convert an integer (INT) to four BCD digits encoded in a WORD.
 *   DINT_TO_BCD_DWORD: Convert a double integer (DINT) to eight BCD digits encoded in a DWORD.
 *   LINT_TO_BCD_LWORD: Convert a long integer (LINT) to sixteen BCD digits encoded in a LWORD.
 */

/**
 * @fn uint8_t iec_to(iec_t *result, iec_t v1, iectype_t to_type)
 * @brief
 *
 * @param result
 * @param v1
 * @param to_type
 * @return status
 */
uint8_t iec_to(iec_t *result, iec_t v1, iectype_t to_type) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_trunc(iec_t *result, iec_t v1, iectype_t to_type)
 * @brief
 *
 * @param result
 * @param v1
 * @param to_type
 * @return status
 */
uint8_t iec_trunc(iec_t *result, iec_t v1, iectype_t to_type) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_bcd_to(iec_t *result, iec_t v1, iectype_t to_type)
 * @brief
 *
 * @param result
 * @param v1
 * @param to_type
 * @return status
 */
uint8_t iec_bcd_to(iec_t *result, iec_t v1, iectype_t to_type) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_to_bcd(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_to_bcd(iec_t *result, iec_t v1) {
    return IEC_OK;
}

#endif /* IEC_CONVERSION_H_ */
