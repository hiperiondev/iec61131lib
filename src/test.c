/*
 * Project Site: https://github.com/hiperiondev/iec61131lib
 *
 * This is based on other projects:
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

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

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

int main(void) {
    uint8_t res = 0;
    iec_t result = iec_new(IEC_T_NULL);
    iec_t v1 = iec_new(IEC_T_INT);
    iec_t v2 = iec_new(IEC_T_INT);
    iec_t v3 = iec_new(IEC_T_INT);
    iec_t v4 = iec_new(IEC_T_INT);
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

    iec_totype(v1, IEC_T_BOOL);
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

    iec_totype(v1, IEC_T_INT);
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
    iec_type_promote(v2, IEC_T_REAL);
    res = iec_div(&result, v2, v3);
    assert(res == IEC_OK);
    assert(iec_get_value(result) == 2.5);
    iec_totype(v2, IEC_T_INT);
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

    printf("-- missing -- ");

    printf("< OK >\n\n");
    /////////////////////////////////////

    iec_destroy(v1);
    iec_destroy(v2);
    iec_destroy(v3);
    iec_destroy(v4);
    stack_release(fstk);

    return 0;
}
