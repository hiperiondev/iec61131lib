/*
 * Project Site: https://github.com/hiperiondev/iec61131lib
 *
 * This is based on other projects:
 *
 *    Others (see individual files)
 *
 *    please contact their authors for more information.
 *
 * Copyright (c) 2022 Emiliano Augusto Gonzalez ( egonzalez . hiperion @ gmail . com )
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

#ifndef IEC_BITWISE_BOOLEAN_H_
#define IEC_BITWISE_BOOLEAN_H_

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 *  AND           ANY_BIT, ANY_INT        2            Logical AND
 *  OR            ANY_BIT, ANY_INT        2            Logical OR
 *  XOR           ANY_BIT, ANY_INT        2            Logical XOR
 *  NOT           ANY_BIT, ANY_INT        1            Logical NOT
 */

/**
 * @fn uint8_t iec_and(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_and(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_BIT, ANY_INT,,,,);
    iec_anytype_allowed(v2, ANY_BIT, ANY_INT,,,,);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_or(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_or(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_BIT, ANY_INT,,,,);
    iec_anytype_allowed(v2, ANY_BIT, ANY_INT,,,,);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_xor(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_xor(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_BIT, ANY_INT,,,,);
    iec_anytype_allowed(v2, ANY_BIT, ANY_INT,,,,);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_not(iec_t*, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @return
 */
uint8_t iec_not(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_BIT, ANY_INT,,,,);

    return IEC_OK;
}

#endif /* IEC_BITWISE_BOOLEAN_H_ */
