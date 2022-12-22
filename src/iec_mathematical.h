/**
 * @file iec_mathematical.h
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

#ifndef IEC_MATHEMATICAL_H_
#define IEC_MATHEMATICAL_H_

#include <math.h>

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 *  ABS           ANY_MAGNITUDE           1            Return the absolute value
 *  SQRT          ANY_REAL                1            Return the square root
 *  LN            ANY_REAL                1            Return the natural logarithm
 *  LOG           ANY_REAL                1            Return logarithm base 10
 *  EXP           ANY_REAL                1            Return natural exponent
 *  SIN           ANY_REAL                1            Return the sine of the input. The input is in radians
 *  COS           ANY_REAL                1            Return the cosine of the input. The input is in radians
 *  TAN           ANY_REAL                1            Return the tangent of the input. The input is in radians
 *  ASIN          ANY_REAL                1            Return the principle arc sine of the input. The output is in radians
 *  ACOS          ANY_REAL                1            Return the principle cosine of the input. The output is in radians
 *  ATAN          ANY_REAL                1            Return the principle tangent of the input. The output is in radians
 *  ATAN2         ANY_REAL, ANY_REAL      2            Return the principle tangent of the input. The output is in radians.
 */

/**
 * @fn uint8_t iec_abs(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_abs(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_MAGNITUDE,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, fabs((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_sqrt(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_sqrt(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, sqrt((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_ln(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_ln(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, log((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_log(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_log(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, log10((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_exp(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_exp(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, exp((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_sin(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_sin(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, sin((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_cos(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_cos(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, cos((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_tan(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_tan(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, tan((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_asin(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_asin(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, asin((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_acos(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return
 */
uint8_t iec_acos(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, acos((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_atan(iec_t *result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return
 */
uint8_t iec_atan(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);

    iec_set_value(*result, atan((double)iec_get_value(v1)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_atan2(iec_t *result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return status
 */
uint8_t iec_atan2(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_REAL,,,,,);
    iec_anytype_allowed(v2, ANY_REAL,,,,,);
    iec_type_promote(result, v1->type);
    iec_type_promote(result, v2->type);

    iec_set_value(*result, atan2((double)iec_get_value(v1), (double)iec_get_value(v2)));

    return IEC_OK;
}

#endif /* IEC_MATHEMATICAL_H_ */
