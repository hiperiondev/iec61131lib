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

#ifndef IEC_DATE_TIME_H_
#define IEC_DATE_TIME_H_

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 *
 */

uint8_t iec_add_dt_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_add_tod_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_add_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_concat_date_tod(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_concat_date(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_concat_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7) {
    return IEC_OK;
}

uint8_t iec_concat_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    return IEC_OK;
}

uint8_t iec_day_of_week(iec_t result, iec_t v1) {
    return IEC_OK;
}

uint8_t iec_divtime(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_multime(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_split_date(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    return IEC_OK;
}

uint8_t iec_split_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7, iec_t v8) {
    return IEC_OK;
}

uint8_t iec_split_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5) {
    return IEC_OK;
}

uint8_t iec_sub_date_date(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_sub_dt_dt(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_sub_dt_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_sub_tod_tod(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_sub_tod_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

uint8_t iec_sub_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

#endif /* IEC_DATE_TIME_H_ */
