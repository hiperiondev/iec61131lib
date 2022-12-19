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
 *  RS                                              Reset Dominant Bistable
 *                  S   BOOL         Input          Sets the output Q1.
 *                  R1  BOOL         Input          Resets the output Q1.
 *                  Q1  BOOL         Output         The output value.
 *  R_TRIG                                          Rising Edge Detector
 *                  CLK BOOL         Input          A rising edge sets the output Q for one execution.
 *                  Q   BOOL         Output         The output value.
 *  F_TRIG                                          Falling Edge Detector
 *                  CLK BOOL         Input          A falling edge sets the output Q for one execution.
 *                  Q   BOOL         Output         The output value.
 *  CTU                                             Counts up from zero to a preset value.
 *                  CU  BOOL         R_EDGE Input   A rising edge increments the counter value CV by 1.
 *                  R   BOOL         Input          Resets the output Q and the counter value CV.
 *                  PV  INT          Input          The counter limit value.
 *                  Q   BOOL         Output         Set to true when the counter value CV reaches PV.
 *                  CV  INT          Input          The current counter value.
 *  CTD                                             Counts down from a preset value to zero.
 *                  CD  BOOL         R_EDGE Input   A rising edge decrements the counter value CV by 1.
 *                  LD  BOOL         Input          Resets the output Q and the counter value CV.
 *                  PV  INT          Input          The counter limit value.
 *                  Q   BOOL         Output         Set to true when the counter value CV reaches PV.
 *                  CV  INT          Input          The current counter value.
 *  TP                                              Generate a fixed duration pulse.
 *                  IN  BOOL         Input          A rising edge starts the fixed duration pulse.
 *                  PT  TIME         Input          The duration of the pulse.
 *                  Q   BOOL         Output         Set to true during the pulse.
 *                  ET  TIME         Output         The elapsed time of the pulse.
 *  TON                                             Turn an output on after a delay.
 *                  IN  BOOL         Input          A rising edge starts the timer.
 *                  PT  TIME         Input          The duration of timer.
 *                  Q   BOOL         Output         Set to true after delay PT.
 *                  ET  TIME         Output         The elapsed time of the timer.
 *  TOF                                             Turn an output off after a delay.
 *                  IN  BOOL         Input          A rising edge starts the timer.
 *                  PT  TIME         Input          The duration of timer.
 *                  Q   BOOL         Output         Set to false after delay PT.
 *                  ET  TIME         Output         The elapsed time of the timer.
 */

#ifndef IEC_STANDARD_FUNCTION_BLOCKS_H_
#define IEC_STANDARD_FUNCTION_BLOCKS_H_



#endif /* IEC_STANDARD_FUNCTION_BLOCKS_H_ */
