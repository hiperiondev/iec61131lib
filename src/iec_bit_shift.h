/*
 * @file iec_bit_shift.h
 * @brief main header
 * @copyright 2022 Emiliano Augusto Gonzalez (hiperiondev). This project is released under MIT licence
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

#ifndef IEC_BIT_SHIFT_H_
#define IEC_BIT_SHIFT_H_

/*
 * Summary:
 *
 *  Function      Parameter Type            Parameters   Description
 *  SHL           1:ANY_INTEGRAL;2:ANY_NUM  2            Shifts an integer value to the left.
 *  SHR           1:ANY_INTEGRAL;2:ANY_NUM  2            Shifts an integer value to the right.
 *  ROL           1:ANY_INTEGRAL;2:ANY_NUM  2            Rotates an integer value to the left.
 *  ROR           1:ANY_INTEGRAL;2:ANY_NUM  2            Rotates an integer value to the right
 */

#define U8V(v)       ((uint8_t)(v)  & 0xFFU)
#define U16V(v)      ((uint16_t)(v) & 0xFFFFU)
#define U32V(v)      ((uint32_t)(v) & 0xFFFFFFFFU)
#define U64V(v)      ((uint64_t)(v) & 0xFFFFFFFFFFFFFFFFU)

#define rotl8(v, n)  (U8V((uint8_t)(v) << (n)) | ((uint8_t)(v) >> (8 - (n))))
#define rotl16(v, n) (U16V((uint16_t)(v) << (n)) | ((uint16_t)(v) >> (16 - (n))))
#define rotl32(v, n) (U32V((uint32_t)(v) << (n)) | ((uint32_t)(v) >> (32 - (n))))
#define rotl64(v, n) (U64V((uint64_t)(v) << (n)) | ((uint64_t)(v) >> (64 - (n))))

#define rotr8(v, n)  rotl8(v, 8 - (n))
#define rotr16(v, n) rotl16(v, 16 - (n))
#define rotr32(v, n) rotl32(v, 32 - (n))
#define rotr64(v, n) rotl64(v, 64 - (n))

/**
 * @fn uint8_t iec_shl(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_shl(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_INTEGRAL,,,,,);
    iec_anytype_allowed(v2, ANY_NUM,,,,,);
    iec_type_promote(result, v1->type);

    maxuint_t _v1 = iec_get_value(v1);
    maxuint_t _v2 = iec_get_value(v2);

    if (sign(iec_get_value(v2))) {
        _v1 = _v1 << _v2;
    } else {
        _v1 = _v1 >> _v2;
    }

    iec_set_value(*result, _v1);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_shr(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_shr(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_INTEGRAL,,,,,);
    iec_anytype_allowed(v2, ANY_NUM,,,,,);
    iec_type_promote(result, v1->type);

    maxuint_t _v1 = iec_get_value(v1);
    maxuint_t _v2 = iec_get_value(v2);
    if (sign(iec_get_value(v2))) {
        _v1 = _v1 >> _v2;
    } else {
        _v1 = _v1 << _v2;
    }
    iec_set_value(*result, _v1);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_rol(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_rol(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_INTEGRAL,,,,,);
    iec_anytype_allowed(v2, ANY_NUM,,,,,);
    iec_type_promote(result, v1->type);

    maxuint_t _v1 = iec_get_value(v1);
    maxuint_t _v2 = iec_get_value(v2);
    if (sign(iec_get_value(v2))) {
        switch (IEC_T_SIZEOF[v1->type]) {
            case 8:
                _v1 = rotl8(_v1, _v2);
                break;
            case 16:
                _v1 = rotl16(_v1, _v2);
                break;
            case 32:
                _v1 = rotl32(_v1, _v2);
                break;
            case 64:
                _v1 = rotl64(_v1, _v2);
                break;
            default:
                _v1 = 0;
        }
    } else {
        switch (IEC_T_SIZEOF[v1->type]) {
            case 8:
                _v1 = rotr8(_v1, _v2);
                break;
            case 16:
                _v1 = rotr16(_v1, _v2);
                break;
            case 32:
                _v1 = rotr32(_v1, _v2);
                break;
            case 64:
                _v1 = rotr64(_v1, _v2);
                break;
            default:
                _v1 = 0;
        }
    }
    iec_set_value(*result, _v1);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_ror(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_ror(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_INTEGRAL,,,,,);
    iec_anytype_allowed(v2, ANY_NUM,,,,,);
    iec_type_promote(result, v1->type);

    maxuint_t _v1 = iec_get_value(v1);
    maxuint_t _v2 = iec_get_value(v2);
    if (sign(iec_get_value(v2))) {
        switch (IEC_T_SIZEOF[v1->type]) {
            case 8:
                _v1 = rotr8(_v1, _v2);
                break;
            case 16:
                _v1 = rotr16(_v1, _v2);
                break;
            case 32:
                _v1 = rotr32(_v1, _v2);
                break;
            case 64:
                _v1 = rotr64(_v1, _v2);
                break;
            default:
                _v1 = 0;
        }
    } else {
        switch (IEC_T_SIZEOF[v1->type]) {
            case 8:
                _v1 = rotl8(_v1, _v2);
                break;
            case 16:
                _v1 = rotl16(_v1, _v2);
                break;
            case 32:
                _v1 = rotl32(_v1, _v2);
                break;
            case 64:
                _v1 = rotl64(_v1, _v2);
                break;
            default:
                _v1 = 0;
        }
    }
    iec_set_value(*result, _v1);

    return IEC_OK;
}

#endif /* IEC_BIT_SHIFT_H_ */
