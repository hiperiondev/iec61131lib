/**
 * @file test.c
 * @brief tests
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

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>

#include "iec61131lib.h"
#include "iec_arithmetic.h"
#include "iec_bit_shift.h"
#include "iec_bitwise_boolean.h"
#include "iec_comparison.h"
#include "iec_conversion.h"
#include "iec_date_time.h"
#include "iec_mathematical.h"
#include "iec_selection.h"
#include "iec_string.h"
#include "iec_literals.h"
#include "iec_std_fun_blocks.h"

int main(void) {
    uint8_t res = 0;
    iec_t result = IEC_ALLOC;
    iec_t rst_tmp = IEC_ALLOC;
    iec_init(&result, IEC_T_NULL);
    iec_init(&rst_tmp, IEC_T_NULL);

    iec_t v1 = IEC_ALLOC;
    iec_t v2 = IEC_ALLOC;
    iec_t v3 = IEC_ALLOC;
    iec_t v4 = IEC_ALLOC;
    iec_init(&v1, IEC_T_INT);
    iec_init(&v2, IEC_T_INT);
    iec_init(&v3, IEC_T_INT);
    iec_init(&v4, IEC_T_INT);
    stack_t fstk = stack_create();

    printf("_  TEST BIT_SHIFT... ");

    iec_set_value(v1, 1000);
    iec_set_value(v2, 2);

    res = iec_shl(&result, v1, v2);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 4000);

    res = iec_shr(&result, v1, v2);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 250);

    res = iec_rol(&result, v1, v2);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 977);

    res = iec_ror(&result, v1, v2);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 500);

    printf("< OK >\n\n");
    /////////////////////////////////////

    printf("_  TEST SELECTION... ");

    iec_set_value(v1, 1000);
    iec_set_value(v2, 2);
    iec_set_value(result, 0);

    res = iec_move(&result, v1);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 1000);

    iec_totype(&v1, IEC_T_BOOL);
    iec_set_value(v1, 0);
    iec_set_value(v2, 100);
    iec_set_value(v3, 200);
    res = iec_sel(&result, v1, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 100);
    iec_set_value(v1, 1);
    res = iec_sel(&result, v1, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 200);

    iec_totype(&v1, IEC_T_INT);
    iec_set_value(v1, 7);
    iec_set_value(v2, 500);
    iec_set_value(v3, 200);

    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);

    res = iec_max(&result, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 500);
    assert(stack_empty(fstk) == 1);

    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);
    res = iec_max(&result, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 7);
    assert(stack_empty(fstk) == 1);

    res = iec_limit(&result, v2, v1, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 200);

    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);
    iec_set_value(v4, 2);
    res = iec_mux(&result, v4, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 7);
    assert(stack_empty(fstk) == 1);

    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);
    iec_set_value(v4, -5);
    res = iec_mux(&result, v4, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 7);
    assert(stack_empty(fstk) == 1);

    printf("< OK >\n\n");
    /////////////////////////////////////

    printf("_  TEST ARITHMETIC... ");

    iec_set_value(v1, 7);
    iec_set_value(v2, 500);
    iec_set_value(v3, 200);
    iec_set_value(v4, 100);
    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);
    stack_push(fstk, (void*) v4);

    res = iec_add(&result, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 807);
    assert(stack_empty(fstk) == 1);

    iec_set_value(v1, 7);
    iec_set_value(v2, 500);
    iec_set_value(v3, 200);
    iec_set_value(v4, 100);
    stack_push(fstk, (void*) v1);
    stack_push(fstk, (void*) v2);
    stack_push(fstk, (void*) v3);
    stack_push(fstk, (void*) v4);

    res = iec_mul(&result, &fstk);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 70000000);
    assert(stack_empty(fstk) == 1);

    res = iec_sub(&result, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 300);

    res = iec_div(&result, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 2);

    iec_type_promote(&v2, IEC_T_REAL);
    float v = iec_get_value(v2);
    printf("V: %f\n", v);
    res = iec_div(&result, v2, v3);
    assert(res == IEC_OK);
    float r = iec_get_value(result);
    printf("R: %f\n", r);

    assert((iec_get_value(result)) == 2.5);
    iec_totype(&v2, IEC_T_INT);
    iec_set_value(v2, 500);
    res = iec_mod(&result, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 100);

    iec_set_value(v2, 2)
    res = iec_mod(&result, v1, v2);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 49);

    printf("< OK >\n\n");
    /////////////////////////////////////

    printf("_  TEST MATHEMATICAL... ");

    iec_type_promote(&v2, IEC_T_REAL);
    iec_set_value(v2, -500);
    res = iec_abs(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 500);

    iec_set_value(v2, 500);
    res = iec_sqrt(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 22.36067962646484375);

    res = iec_ln(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 6.21460819244384765625);

    res = iec_log(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 2.6989700794219970703125);

    iec_set_value(v2, 7);
    res = iec_exp(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 1096.6331787109375);

    res = iec_sin(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.65698659420013427734375);

    res = iec_cos(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.753902256488800048828125);

    res = iec_tan(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.871447980403900146484375);

    iec_set_value(v2, 0.6);
    res = iec_asin(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.64350116252899169921875);

    res = iec_acos(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.927295207977294921875);

    res = iec_atan(&result, v2);
    assert(res == IEC_OK);
    assert((iec_get_value(result)) == 0.540419518947601318359375);

    printf("< OK >\n\n");
    /////////////////////////////////////

    printf("_  TEST LITERALS... ");

    str_t *str = NEW_STRING(255, "UINT#16#9_A");
    uint8_t datatype;
    uint8_t iectype;

    printf("\nstr: %s\n", str->value);
    datatype = iec_identify_literal(str, &iectype);

    printf("lit: %d, iectype: %d, str: %s\n", datatype, iectype, stringValue(str));

    clearString(str);
    concatChars(str, "-13.5e-2");
    printf("\nstr: %s\n", str->value);
    datatype = iec_identify_literal(str, &iectype);

    printf("lit: %d, iectype: %d, str: %s(%f)\n", datatype, iectype, stringValue(str), atof(stringValue(str)));

    clearString(str);
    concatChars(str, "BOOL#TRUE");
    printf("\nstr: %s\n", str->value);
    datatype = iec_identify_literal(str, &iectype);

    printf("lit: %d, iectype: %d, str: %s\n", datatype, iectype, stringValue(str));

    printf("< OK >\n\n");
    /////////////////////////////////////

    printf("_  TEST STRINGS... ");

    char strt[] = "This is a test";
    iec_string_set(&rst_tmp, strt, 0, 1);

    printf("\npp p:%p/%p/%p\n", (((string_t*) (rst_tmp->value))->str->value), strt, v4->value);
    //iec_totype(&v4, IEC_T_UDINT);
    printf(">pp p:%p/%p/%p\n", (((string_t*) (rst_tmp->value))->str->value), strt, v4->value);
    printf("nt: %d, (%s)\n", rst_tmp->type, (((string_t*) (rst_tmp->value))->str->value));
    str_t *str_tmp = iec_get_string(rst_tmp);
    printf("t: %d, l: %d(%s)(%s)\n", rst_tmp->type, stringLength(str_tmp), stringValue(str_tmp), (((string_t*) (rst_tmp->value))->str->value));
    printf("-pp p:%p/%p\n", (((string_t*) (rst_tmp->value))->str->value), strt);
    printf("< OK >\n\n");
    /////////////////////////////////////

    iec_deinit(&result);
    iec_deinit(&rst_tmp);
    iec_deinit(&v1);
    iec_deinit(&v2);
    iec_deinit(&v3);
    iec_deinit(&v4);
    stack_release(fstk);

    return 0;
}
