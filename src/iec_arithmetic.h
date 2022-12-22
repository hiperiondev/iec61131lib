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

#ifndef IEC_ARITHMETIC_H_
#define IEC_ARITHMETIC_H_

#include <math.h>
#include <stdio.h>

#include "util_stack.h"
#include "iec_selection.h"

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters  Description
 *  ADD           ANY_MAGNITUDE           2-n         Addition
 *  MUL           ANY_MAGNITUDE           2-n         Multiplication
 *  SUB           ANY_MAGNITUDE           2           Subtraction
 *  DIV           ANY_MAGNITUDE, ANY_NUM  2           Division
 *  MOD           ANY_INT                 2           Modulo
 *  EXPT          ANY_NUM                 2           Raise to power
 */

/**
 * @fn uint8_t iec_add(iec_t*, stack_t*)
 * @brief
 *
 * @param result
 * @param list
 * @return
 */
uint8_t iec_add(iec_t *result, stack_t *list) {
    if (*result == NULL || list == NULL)
        return IEC_NLL;

    iec_t tmp = IEC_ALLOC;
    iec_init(&tmp, IEC_T_NULL);
    iec_move(result, (iec_t) stack_pop(*list));
    iec_anytype_allowed(*result, ANY_MAGNITUDE,,,,,);

    while (!stack_empty(*list)) {
        iec_move(&tmp, (iec_t) stack_pop(*list));
        iec_anytype_allowed(tmp, ANY_MAGNITUDE,,,,,);
        iec_type_promote(result, tmp->type);
        iec_set_value(*result, (iec_get_value(*result)) + (iec_get_value(tmp)));
    }

    iec_deinit(&tmp);
    return IEC_OK;
}

/**
 * @fn uint8_t iec_mul(iec_t*, stack_t*)
 * @brief
 *
 * @param result
 * @param list
 * @return
 */
uint8_t iec_mul(iec_t *result, stack_t *list) {
    if (*result == NULL || list == NULL)
        return IEC_NLL;

    iec_t tmp = IEC_ALLOC;
    iec_init(&tmp, IEC_T_NULL);
    iec_move(result, (iec_t) stack_pop(*list));
    iec_anytype_allowed(*result, ANY_MAGNITUDE,,,,,);

    while (!stack_empty(*list)) {
        iec_move(&tmp, (iec_t) stack_pop(*list));
        iec_anytype_allowed(tmp, ANY_MAGNITUDE,,,,,);
        iec_type_promote(result, tmp->type);
        iec_set_value(*result, (iec_get_value(*result)) * (iec_get_value(tmp)));
    }

    iec_deinit(&tmp);
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_MAGNITUDE,,,,,);
    iec_anytype_allowed(v2, ANY_MAGNITUDE,,,,,);

    iec_type_promote(result, v1->type);
    iec_type_promote(result, v2->type);
    iec_set_value(*result, (iec_get_value(v1)) - (iec_get_value(v2)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_div(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_div(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_MAGNITUDE,ANY_NUM,,,,);
    iec_anytype_allowed(v2, ANY_MAGNITUDE,ANY_NUM,,,,);
    if ((iec_get_value(v2)) == 0)
        return IEC_NAT;

    printf("type: %d\n", (*result)->type);
    iec_type_promote(result, v1->type);
    iec_type_promote(result, v2->type);
    printf("-type: %d\n", (*result)->type);
    float va, vb;
    va=iec_get_value(v1);
    vb=iec_get_value(v2);
    printf("%f/%f: %f\n", va, vb, va/vb);
    iec_set_value(*result, (iec_get_value(v1)) / (iec_get_value(v2)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_mod(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_mod(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_INT,,,,,);
    iec_anytype_allowed(v2, ANY_INT,,,,,);

    if ((iec_get_value(v2)) == 0) {
        iec_set_value(*result, 0);
        return IEC_OK;
    }

    iec_set_value(*result, (iec_get_value(v1) % iec_get_value(v2)));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_expt(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_expt(iec_t *result, iec_t v1, iec_t v2) {
    iec_anytype_allowed(v1, ANY_NUM,,,,,);
    iec_anytype_allowed(v2, ANY_NUM,,,,,);

    iec_type_promote(result, IEC_T_LREAL);
    iec_type_promote(&v1, IEC_T_LREAL);
    iec_type_promote(&v2, IEC_T_LREAL);

    iec_set_value(*result, ((iec_get_value(v1)) ^ (iec_get_value(v2))));

    return IEC_OK;
}

#endif /* IEC_ARITHMETIC_H_ */
