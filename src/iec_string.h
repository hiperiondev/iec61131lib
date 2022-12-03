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

#ifndef IEC_STRING_H_
#define IEC_STRING_H_

#include "util_murhash.h"

/*
 * Summary:
 *
 *  Function      Parameter Type                       Parameters   Description
 *  LEN           ANY_STRING                           1            Return the length of a string.
 *  LEFT          1:ANY_STRING;2:ANY_INT               2            Return the left part of a string.
 *  RIGHT         1:ANY_STRING;2:ANY_INT               2            Return the right part of a string.
 *  MID           1:ANY_STRING;2,3:ANY_INT             3            Return the center part of a string.
 *  CONCAT        1:ANY_STRING;2-n:ANY_CHAR            2-n          Add together (concatenate) two or more strings.
 *  INSERT        1:ANY_STRING;2:ANY_CHARS;3:ANY_INT   3            Insert one string into another string.
 *  DELETE        1:ANY_STRING;2,3:ANY_INT             3            Delete part of a string.
 *  REPLACE       1:ANY_STRING;2:ANY_CHAR;3,4:ANY_INT  4            Replaces part of one string with another string.
 *  FIND          1:ANY_STRING;2:ANY_CHAR              2            Finds the location of one string within another.
 */

uint8_t iec_len(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    return IEC_OK;
}

uint8_t iec_left(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_right(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_mid(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_concat(iec_t *result, stack_t list) {
    return IEC_OK;
}

uint8_t iec_insert(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHARS,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_delete(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_replace(iec_t *result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHAR,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    iec_anytype_allowed(v4, ANY_INT,,,,,);
    return IEC_OK;
}

uint8_t iec_find(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHAR,,,,,);
    return IEC_OK;
}

uint32_t iec_string_hash(iec_t *result) {
    return IEC_OK;
}

uint8_t iec_string_set(iec_t *result, void *str, bool wstr) {

    return IEC_OK;
}

#endif /* IEC_STRING_H_ */
