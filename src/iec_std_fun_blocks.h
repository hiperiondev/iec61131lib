/**
 * @file iec_std_fun_blocks.h
 * @brief main header
 * @copyright 2022 Emiliano Augusto Gonzalez (hiperiondev). This project is released under MIT license.
 * Contact: egonzalez.hiperion@gmail.com
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
#include "iec_hardware.h"

/**
 * @fn uint8_t iec_sr(iec_t*, iec_t, iec_t)
 * @brief
 *
 * @param q1
 * @param s1
 * @param r
 * @return
 */
uint8_t iec_sr(iec_t *q1, iec_t s1, iec_t r) {
    iec_type_allowed(s1, IEC_T_BOOL);
    iec_type_allowed(r, IEC_T_BOOL);

    iec_totype(q1, IEC_T_BOOL);
    iec_set_maintain(*q1);

    iec_set_value(*q1, (iec_get_value(s1) || (iec_get_value((*q1)) && !(iec_get_value(r)))));

    return IEC_OK;
}

 /**
  * @fn uint8_t iec_rs(iec_t*, iec_t, iec_t)
  * @brief
  *
  * @param q1
  * @param s
  * @param r1
  * @return
  */
uint8_t iec_rs(iec_t *q1, iec_t s, iec_t r1) {
    iec_type_allowed(s, IEC_T_BOOL);
    iec_type_allowed(r1, IEC_T_BOOL);

    iec_totype(q1, IEC_T_BOOL);
    iec_set_maintain(*q1);

    iec_set_value(*q1, ((iec_get_value((*q1)) || iec_get_value(s)) && !(iec_get_value(r1))));

    return IEC_OK;
}

/**
 * @fn uint8_t iec_r_trig(iec_t*, iec_t)
 * @brief
 *
 * @param q
 * @param clk
 * @return
 */
uint8_t iec_r_trig(iec_t *q, iec_t clk) {
    iec_type_allowed(clk, IEC_T_BOOL);

    iec_totype(q, IEC_T_BOOL);
    iec_set_maintain(*q);

    iec_set_value(*q, (iec_get_value(clk) && !(iec_is_flag1(*q))));
    if (iec_get_value(clk))
        iec_set_flag1(*q);
    else
        iec_unset_flag1(*q);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_f_trig(iec_t*, iec_t)
 * @brief
 *
 * @param q
 * @param clk
 * @return
 */
uint8_t iec_f_trig(iec_t *q, iec_t clk) {
    iec_type_allowed(clk, IEC_T_BOOL);

    iec_totype(q, IEC_T_BOOL);
    iec_set_maintain(*q);

    iec_set_value(*q, (!iec_get_value(clk) && !(iec_is_flag1(*q))));
    if (iec_get_value(clk))
        iec_unset_flag1(*q);
    else
        iec_set_flag1(*q);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_ctu(iec_t*, iec_t, iec_t, iec_t, iec_t*)
 * @brief
 *
 * @param q
 * @param cu
 * @param r
 * @param pv
 * @param cv
 * @return
 */
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

/**
 * @fn uint8_t iec_ctd(iec_t*, iec_t, iec_t, iec_t, iec_t*)
 * @brief
 *
 * @param q
 * @param cd
 * @param ld
 * @param pv
 * @param cv
 * @return
 */
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

/**
 * @fn uint8_t iec_initialize_timer(iec_t*, iec_t)
 * @brief
 *
 * @param timer
 * @param pt
 * @return
 */
uint8_t iec_initialize_timer(iec_t *timer, iec_t pt) {
    iec_type_allowed(*timer, IEC_T_TIMER);
    iec_type_allowed(pt, IEC_T_TIME);

    iec_timer(*timer)->q = false;
    iec_timer(*timer)->pt = iec_get_value(pt);
    iec_timer(*timer)->et = 0;
    iec_timer(*timer)->timer_run = false;
    iec_timer(*timer)->t0 = 0;

    iec_set_initialized(*timer);

    return IEC_OK;
}

/**
 * @fn uint8_t iec_tp(iec_t*, iec_t, iec_t, iec_t*)
 * @brief
 *
 * @param timer
 * @param in
 * @param pt
 * @param et
 * @return
 */
uint8_t iec_tp(iec_t *timer, iec_t in, iec_t pt, iec_t *et) {
    iec_type_allowed(*timer, IEC_T_TIMER);

    if (!iec_is_initialized(*timer))
        iec_initialize_timer(timer, pt);

    if (iec_get_value(in)) {
        if (iec_timer(*timer)->t0 == 0) {
            iec_timer(*timer)->t0 = hw_millis();
        }
    }

    if (iec_timer(*timer)->t0 > 0) {
        iec_timer(*timer)->et = hw_millis() - iec_timer(*timer)->t0;
        if (iec_timer(*timer)->et >= iec_timer(*timer)->pt) {
            iec_timer(*timer)->et = iec_timer(*timer)->pt;
        }
    }

    if (!iec_get_value(in) && iec_timer(*timer)->et == iec_timer(*timer)->pt) {
        iec_timer(*timer)->t0 = 0;
        iec_timer(*timer)->et = 0;
    }

    iec_timer(*timer)->q = iec_timer(*timer)->et > 0 && iec_timer(*timer)->et < iec_timer(*timer)->pt;

    if (*et != NULL) {
        iec_type_allowed(*et, IEC_T_TIME);
        iec_set_value(*et, iec_timer(*timer)->et);
    }

    return IEC_OK;
}

/**
 * @fn uint8_t iec_ton(iec_t*, iec_t, iec_t, iec_t*)
 * @brief
 *
 * @param timer
 * @param in
 * @param pt
 * @param et
 * @return
 */
uint8_t iec_ton(iec_t *timer, iec_t in, iec_t pt, iec_t *et) {
    iec_type_allowed(*timer, IEC_T_TIMER);

    if (!iec_is_initialized(*timer))
        iec_initialize_timer(timer, pt);

    if (!iec_get_value(in)) {
        iec_timer(*timer)->et = 0;
        iec_timer(*timer)->t0 = 0;
        iec_timer(*timer)->q = false;
    } else {
        if (iec_timer(*timer)->t0 == 0) {
            iec_timer(*timer)->t0 = hw_millis();
        }
        iec_timer(*timer)->et = hw_millis() - iec_timer(*timer)->t0;
        if (iec_timer(*timer)->et >= iec_timer(*timer)->pt) {
            iec_timer(*timer)->et = iec_timer(*timer)->pt;
            iec_timer(*timer)->q = true;
        }
    }

    if (*et != NULL) {
        iec_type_allowed(*et, IEC_T_TIME);
        iec_set_value(*et, iec_timer(*timer)->et);
    }

    return IEC_OK;
}

/**
 * @fn uint8_t iec_tof(iec_t*, iec_t, iec_t, iec_t*)
 * @brief
 *
 * @param timer
 * @param in
 * @param pt
 * @param et
 * @return
 */
uint8_t iec_tof(iec_t *timer, iec_t in, iec_t pt, iec_t *et) {
    iec_type_allowed(*timer, IEC_T_TIMER);

    if (!iec_is_initialized(*timer))
        iec_initialize_timer(timer, pt);

    if (iec_get_value(in)) {
        iec_timer(*timer)->et = 0;
        iec_timer(*timer)->t0 = 0;
        iec_timer(*timer)->q = true;
    } else {
        if (iec_timer(*timer)->t0 == 0) {
            iec_timer(*timer)->t0 = hw_millis();
        }
        iec_timer(*timer)->et = hw_millis() - iec_timer(*timer)->t0;
    }

    if (iec_timer(*timer)->t0 >= iec_timer(*timer)->pt) {
        iec_timer(*timer)->et = iec_timer(*timer)->pt;
        iec_timer(*timer)->q = false;
    }

    if (*et != NULL) {
        iec_type_allowed(*et, IEC_T_TIME);
        iec_set_value(*et, iec_timer(*timer)->et);
    }

    return IEC_OK;
}

#endif /* IEC_STANDARD_FUNCTION_BLOCKS_H_ */
