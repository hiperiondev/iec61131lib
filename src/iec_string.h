/*
 * @file iec_string.h
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

#ifndef IEC_STRING_H_
#define IEC_STRING_H_

#include <string.h>
#include <wchar.h>

#include "iec61131lib.h"
#include "util_buffer_string.h"
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

/**
 * @fn unsigned char iec_string_len(iec_t*, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @return
 */
uint8_t iec_string_len(iec_t *result, iec_t v1) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_totype(result, IEC_T_UDINT);

    str_t *str = iec_get_string(v1);
    iec_set_value(*result, str->length);

    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_left(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_string_left(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_right(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_string_right(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_mid(iec_t*, iec_t, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @return
 */
uint8_t iec_string_mid(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_concat(iec_t*, stack_t)
 * @brief
 *
 * @param result
 * @param list
 * @return
 */
uint8_t iec_string_concat(iec_t *result, stack_t list) {
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_insert(iec_t*, iec_t, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @return
 */
uint8_t iec_string_insert(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHARS,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_delete(iec_t*, iec_t, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @return
 */
uint8_t iec_string_delete(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_replace(iec_t*, iec_t, iec_t, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @return
 */
uint8_t iec_string_replace(iec_t *result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHAR,,,,,);
    iec_anytype_allowed(v3, ANY_INT,,,,,);
    iec_anytype_allowed(v4, ANY_INT,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_find(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_string_find(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_STRING,,,,,);
    iec_anytype_allowed(v2, ANY_CHAR,,,,,);
    return IEC_OK;
}

/**
 * @fn unsigned char iec_string_set(iec_t*, char*, bool, bool)
 * @brief
 *
 * @param result
 * @param str
 * @param wstr
 * @param hash
 * @return
 */
uint8_t iec_string_set(iec_t *result, char *str, bool wstr, bool hash) {
    if (wstr) {
        iec_totype(result, IEC_T_WSTRING);
    } else {
        iec_totype(result, IEC_T_STRING);
    }

    (*result)->value = malloc(sizeof(string_t));
    ((string_t*) ((*result)->value))->str = newStringWithLength2(&(str_t) { 0 }, str, strlen(str));

    if (hash) {
        ((string_t*) ((*result)->value))->hash = PMurHash32(STR_SEED_HASH, stringValue(((string_t*) ((*result)->value))->str),
                stringLength(((string_t*) ((*result)->value))->str));
    }

    return IEC_OK;
}

#endif /* IEC_STRING_H_ */
