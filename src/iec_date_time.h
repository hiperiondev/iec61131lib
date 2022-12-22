/**
 * @file iec_date_time.h
 * @brief
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

#ifndef IEC_DATE_TIME_H_
#define IEC_DATE_TIME_H_

/*
 * Summary:
 *
 *  Function      Parameter Type          Parameters   Description
 *
 * ADD_DT_TIME                                         Adds an interval to a date and time value.
 * ADD_TOD_TIME                                        Adds an interval to a time of day value.
 * ADD_TIME                                            Adds two interval values.
 * CONCAT_DATE_TOD                                     Adds a time of day value to a date.
 * CONCAT_DATE                                         Constructs a DATE value from: Year, Month and Date values.
 * CONCAT_DT                                           Constructs a DATE_AND_TIME value from: Year, Month, Date, Hour, Minute, Second and Millisecond values.
 * CONCAT_TOD                                          Constructs a TIME_OF_DAY value from: Hour, Minute, Second and Millisecond values.
 * DAY_OF_WEEK                                         Returns the day of week of a DATE value.
 * DIVTIME                                             Divides an interval by a numeric value.
 * MULTIME                                             Multiplies an interval by a numeric value.
 * SPLIT_DATE                                          Extracts the fields from a DATE value.
 * SPLIT_DT                                            Extracts the fields from a DATE_AND_TIME value.
 * SPLIT_TOD                                           Extracts the fields from a TIME_OF_DAY value.
 * SUB_DATE_DATE                                       Subtracts two date values.
 * SUB_DT_DT                                           Subtracts two date and time values.
 * SUB_DT_TIME                                         Subtracts an interval from a date and time value.
 * SUB_TOD_TOD                                         Subtracts two time of day values.
 * SUB_TOD_TIME                                        Subtracts an interval from a time of day value.
 * SUB_TIME                                            Subtracts two interval values.
 *
 */

/**
 * @fn uint8_t iec_add_dt_time(iec_t *result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return status
 */
uint8_t iec_add_dt_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_add_tod_time(iec_t *result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_add_tod_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_add_time(iec_t *result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_add_time(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_concat_date_tod(iec_t *result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_concat_date_tod(iec_t *result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_concat_date(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return status
 */
uint8_t iec_concat_date(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_concat_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @param v5
 * @param v6
 * @param v7
 * @return status
 */
uint8_t iec_concat_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_concat_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @return status
 */
uint8_t iec_concat_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_day_of_week(iec_t result, iec_t v1)
 * @brief
 *
 * @param result
 * @param v1
 * @return status
 */
uint8_t iec_day_of_week(iec_t result, iec_t v1) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_divtime(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return status
 */
uint8_t iec_divtime(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_multime(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return status
 */
uint8_t iec_multime(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn iec_split_date(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @return
 */
uint8_t iec_split_date(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4) {
    return IEC_OK;
}

/**
 * @fn iec_split_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7, iec_t v8)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @param v5
 * @param v6
 * @param v7
 * @param v8
 * @return status
 */
uint8_t iec_split_dt(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5, iec_t v6, iec_t v7, iec_t v8) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_split_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @param v3
 * @param v4
 * @param v5
 * @return
 */
uint8_t iec_split_tod(iec_t result, iec_t v1, iec_t v2, iec_t v3, iec_t v4, iec_t v5) {
    return IEC_OK;
}

/**
 * @fn iec_sub_date_date(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_date_date(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub_dt_dt(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_dt_dt(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub_dt_time(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_dt_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub_tod_tod(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_tod_tod(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub_tod_time(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_tod_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

/**
 * @fn uint8_t iec_sub_time(iec_t result, iec_t v1, iec_t v2)
 * @brief
 *
 * @param result
 * @param v1
 * @param v2
 * @return
 */
uint8_t iec_sub_time(iec_t result, iec_t v1, iec_t v2) {
    return IEC_OK;
}

#endif /* IEC_DATE_TIME_H_ */
