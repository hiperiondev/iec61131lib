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

#ifndef IEC_SELECTION_H_
#define IEC_SELECTION_H_

#include "iec_stack.h"

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 * MOVE           ANY                     1            Assign one value to another.
 * SEL            1:BOOL;2,3:ANY          3            Returns one of two values depending on a BOOL value.
 * MAX            ANY_NUM                 1-n          Returns the highest value input.
 * MIN            ANY_NUM                 1-n          Returns the lowest value input.
 * LIMIT          ANY_NUM                 3            Returns a value limited to a maximum or minimum.
 * MUX            1:ANY_INT, 2-n:ANY      2-n          Return one of N values depending on an integer selector value.
 */

uint8_t iec_move(iec_t *to, iec_t from) {
    iec_destroy((*to));
    (*to) = iec_new(from->type);
    (*to)->tt = from->tt;
    iec_set_value((*to), iec_get_value(from));

    return IEC_OK;
}

uint8_t iec_sel(iec_t *result, iec_t v1, iec_t v2, iec_t v3) {
    iec_type_allowed(v1, IEC_T_BOOL);

    if (iec_get_value(v1))
        iec_move(result, v3);
    else
        iec_move(result, v2);

    return IEC_OK;
}

uint8_t iec_max(iec_t *result, stack_t *list) {
    if (*result == NULL || *list == NULL)
        return IEC_NLL;

    iec_t tmp = iec_new(IEC_T_NULL);
    iec_move(result, (iec_t) stack_pop(*list));
    iec_anytype_allowed(*result, ANY_NUM,,,,,);

    while (!stack_empty(*list)) {
        iec_move(&tmp, (iec_t) stack_pop(*list));
        iec_anytype_allowed(tmp, ANY_NUM,,,,,);
        if ((iec_get_value(*result)) < (iec_get_value(tmp))) {
            iec_move(result, tmp);
        }
    }

    iec_destroy(tmp);
    return IEC_OK;
}

uint8_t iec_min(iec_t *result, stack_t *list) {
    if (*result == NULL || list == NULL)
        return IEC_NLL;

    iec_t tmp = iec_new(IEC_T_NULL);
    iec_move(result, (iec_t) stack_pop(*list));
    iec_anytype_allowed(tmp, ANY_NUM,,,,,);

    while (!stack_empty(*list)) {
        iec_move(&tmp, (iec_t) stack_pop(*list));
        iec_anytype_allowed(*result, ANY_NUM,,,,,);
        if ((iec_get_value(*result)) > (iec_get_value(tmp))) {
            iec_move(result, tmp);
        }
    }

    iec_destroy(tmp);
    return IEC_OK;
}

uint8_t iec_limit(iec_t *result, iec_t v, iec_t min, iec_t max) {
    iec_anytype_allowed(v, ANY_NUM,,,,,);
    iec_anytype_allowed(min, ANY_NUM,,,,,);
    iec_anytype_allowed(max, ANY_NUM,,,,,);

    if ((iec_get_value(v)) < (iec_get_value(min)))
        iec_move(result, min);
    else if ((iec_get_value(v)) > (iec_get_value(max)))
        iec_move(result, max);
    else
        iec_move(result, v);

    return IEC_OK;
}

uint8_t iec_mux(iec_t *result, iec_t v1, stack_t *list) {
    iec_anytype_allowed(v1, ANY_INT,,,,,);

    if (iec_get_value(v1) <= 0) {
        iec_move(result, (iec_t) stack_pop(*list));
        stack_flush(*list);
        return IEC_OK;
    }

    maxuint_t cnt = iec_get_value(v1);
    while (!stack_empty(*list)) {
        if (cnt-- == 0)
            break;
        iec_move(result, (iec_t) stack_pop(*list));
    }

    stack_flush(*list);

    return IEC_OK;
}

#endif /* IEC_SELECTION_H_ */