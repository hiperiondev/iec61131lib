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

/*
 * Summary:
 *
 *  Function        Parameter Type   Parameters     Description
 *
 *  SR                                              Set Dominant Bistable
 *                  S1  BOOL         Input          Sets the output Q1.
 *                  R   BOOL         Input          Resets the output Q1.
 *                  Q1  BOOL         Output         The output value.
 *
 *  RS                                              Reset Dominant Bistable
 *                  S   BOOL         Input          Sets the output Q1.
 *                  R1  BOOL         Input          Resets the output Q1.
 *                  Q1  BOOL         Output         The output value.
 *
 *  R_TRIG                                          Rising Edge Detector
 *                  CLK BOOL         Input          A rising edge sets the output Q for one execution.
 *                  Q   BOOL         Output         The output value.
 *
 *  F_TRIG                                          Falling Edge Detector
 *                  CLK BOOL         Input          A falling edge sets the output Q for one execution.
 *                  Q   BOOL         Output         The output value.
 *
 *  CTU                                             Counts up from zero to a preset value.
 *                  CU  BOOL         R_EDGE Input   A rising edge increments the counter value CV by 1.
 *                  R   BOOL         Input          Resets the output Q and the counter value CV.
 *                  PV  INT          Input          The counter limit value.
 *                  Q   BOOL         Output         Set to true when the counter value CV reaches PV.
 *                  CV  INT          Input          The current counter value.
 *
 *  CTD                                             Counts down from a preset value to zero.
 *                  CD  BOOL         R_EDGE Input   A rising edge decrements the counter value CV by 1.
 *                  LD  BOOL         Input          Resets the output Q and the counter value CV.
 *                  PV  INT          Input          The counter limit value.
 *                  Q   BOOL         Output         Set to true when the counter value CV reaches PV.
 *                  CV  INT          Input          The current counter value.
 *
 *  TP                                              Generate a fixed duration pulse.
 *                  IN  BOOL         Input          A rising edge starts the fixed duration pulse.
 *                  PT  TIME         Input          The duration of the pulse.
 *                  Q   BOOL         Output         Set to true during the pulse.
 *                  ET  TIME         Output         The elapsed time of the pulse.
 *
 *  TON                                             Turn an output on after a delay.
 *                  IN  BOOL         Input          A rising edge starts the timer.
 *                  PT  TIME         Input          The duration of timer.
 *                  Q   BOOL         Output         Set to true after delay PT.
 *                  ET  TIME         Output         The elapsed time of the timer.
 *
 *  TOF                                             Turn an output off after a delay.
 *                  IN  BOOL         Input          A rising edge starts the timer.
 *                  PT  TIME         Input          The duration of timer.
 *                  Q   BOOL         Output         Set to false after delay PT.
 *                  ET  TIME         Output         The elapsed time of the timer.
 */

#ifndef IEC_STANDARD_FUNCTION_BLOCKS_H_
#define IEC_STANDARD_FUNCTION_BLOCKS_H_

#include <stdbool.h>
#include <stdint.h>

#include "iec61131lib.h"
#include "fun_hardware.h"

uint8_t iec_sr(iec_t *q1, iec_t s1, iec_t r) {
    iec_type_allowed(s1, IEC_T_BOOL);
    iec_type_allowed(r, IEC_T_BOOL);

    iec_totype(q1, IEC_T_BOOL);
    (*q1)->tt = iec_set_maintain((*q1)->tt);

    bool q1_, s1_, r_;
    q1_ = iec_get_value((*q1));
    s1_ = iec_get_value(s1);
    r_ = iec_get_value(r);

    iec_set_value(*q1, (s1_ || (q1_ && !r_)));

    return IEC_OK;
}

uint8_t iec_rs(iec_t *q1, iec_t s, iec_t r1) {
    iec_type_allowed(s, IEC_T_BOOL);
    iec_type_allowed(r1, IEC_T_BOOL);

    iec_totype(q1, IEC_T_BOOL);
    (*q1)->tt = iec_set_maintain((*q1)->tt);

    bool q1_, s_, r1_;
    q1_ = iec_get_value((*q1));
    s_ = iec_get_value(s);
    r1_ = iec_get_value(r1);

    iec_set_value(*q1, ((q1_ || s_) && !r1_));

    return IEC_OK;
}

uint8_t iec_r_trig(iec_t *q, iec_t clk) {
    iec_type_allowed(clk, IEC_T_BOOL);

    iec_totype(q, IEC_T_BOOL);
    (*q)->tt = iec_set_maintain((*q)->tt);

    bool clk_, m;
    clk_ = iec_get_value(clk);
    m = iec_is_flag1((*q)->tt);

    iec_set_value(*q, (clk_ && !m));
    (*q)->tt = clk ? iec_set_flag1((*q)->tt) : iec_unset_flag1((*q)->tt);

    return IEC_OK;
}

uint8_t iec_f_trig(iec_t *q, iec_t clk) {
    iec_type_allowed(clk, IEC_T_BOOL);

    iec_totype(q, IEC_T_BOOL);
    (*q)->tt = iec_set_maintain((*q)->tt);

    bool clk_, m;
    clk_ = iec_get_value(clk);
    m = iec_is_flag1((*q)->tt);

    iec_set_value(*q, (!clk_ && !m));
    (*q)->tt = clk ? iec_unset_flag1((*q)->tt) : iec_set_flag1((*q)->tt);

    return IEC_OK;
}

uint8_t iec_ctu(iec_t *q, iec_t cu, iec_t r, iec_t pv, iec_t *cv) {
    iec_type_allowed(cu, IEC_T_R_EDGE);
    iec_type_allowed(r, IEC_T_BOOL);
    iec_type_allowed(pv, IEC_T_INT);
    iec_type_allowed(*cv, IEC_T_INT);

    iec_totype(q, IEC_T_BOOL);

    if (iec_get_value(r)) {
        iec_set_value(*cv, 0);
    } else if (iec_get_value(cu) && (iec_get_value(*cv) < iec_get_value(pv)))
        iec_set_value(*cv, iec_get_value(*cv) + 1);

    iec_set_value(*q, iec_get_value(*cv) >= iec_get_value(pv))

    return IEC_OK;
}

uint8_t iec_ctd(iec_t *q, iec_t cd, iec_t ld, iec_t pv, iec_t *cv) {
    iec_type_allowed(cd, IEC_T_R_EDGE);
    iec_type_allowed(ld, IEC_T_BOOL);
    iec_type_allowed(pv, IEC_T_INT);
    iec_type_allowed(*cv, IEC_T_INT);

    iec_totype(q, IEC_T_BOOL);

    if (iec_get_value(ld)) {
        iec_set_value(*cv, iec_get_value(pv));
    } else if (iec_get_value(cd) && (iec_get_value(*cv) > 0))
        iec_set_value(*cv, iec_get_value(*cv) - 1);

    iec_set_value(*q, iec_get_value(*cv) <= 0)

    return IEC_OK;
}

uint8_t iec_tp(iec_t *q, iec_t in, iec_t pt, iec_t et) {


    return IEC_OK;
}

uint8_t iec_ton(iec_t *timer, iec_t in, iec_t pt, iec_t et) {
    iec_type_allowed(in, IEC_T_BOOL);
    iec_type_allowed(pt, IEC_T_TIME);
    iec_type_allowed(et, IEC_T_TIME);
    iec_type_allowed(*timer, IEC_T_TIMER);


    return IEC_OK;
}
uint8_t iec_tof(iec_t *q, iec_t in, iec_t pt, iec_t et) {

    return IEC_OK;
}

#endif /* IEC_STANDARD_FUNCTION_BLOCKS_H_ */
