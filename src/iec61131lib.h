/**
 * @file iec61131lib.h
 * @brief main header
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

#ifndef IEC61131LIB_H_
#define IEC61131LIB_H_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "util_buffer_string.h"

/**
 * @def ALLOW_64BITS
 * @brief allow 64 bits data types
 *
 */
#define ALLOW_64BITS

/**
 * @def STR_SEED_HASH
 * @brief seed for string hash
 *
 */
#define STR_SEED_HASH      0x12345

/**
 * @enum IEC_ERRORS
 * @brief errors
 *
 */
enum IEC_ERRORS {
    IEC_OK  = 0x00, /**< ok */
    IEC_NAT = 0x01, /**< not allowed data type in operation */
    IEC_TRN = 0x02, /**< result function on variable are truncated */
    IEC_OOR = 0x03, /**< variable out of range (ex: string too long) */
    IEC_TND = 0x04, /**< data type not defined */
    IEC_NLL = 0x05, /**< parameter is NULL */
    IEC_TRU = 0x06, /**< result is true */
    IEC_FLS = 0x07, /**< result is false */
    IEC_ENL = 0x08, /**< element not in list or search behind length */
    // ... //
    IEC_ERR = 0xff, /**< generic error */
};

/**
 * @typedef iectype_t
 * @brief data types
 *
 */
typedef enum {
    IEC_T_NULL    = 0x00,  /**< not value */
    IEC_T_BOOL    = 0x01,  /**< bool */
    IEC_T_SINT    = 0x02,  /**< int8_t */
    IEC_T_USINT   = 0x03,  /**< uint8_t */
    IEC_T_BYTE    = 0x04,  /**< uint8_t */
    IEC_T_INT     = 0x05,  /**< int16_t */
    IEC_T_UINT    = 0x06,  /**< uint16_t */
    IEC_T_WORD    = 0x07,  /**< uint16_t */
    IEC_T_DINT    = 0x08,  /**< int32_t */
    IEC_T_UDINT   = 0x09,  /**< uint32_t */
    IEC_T_DWORD   = 0x0a,  /**< uint32_t */
#ifdef ALLOW_64BITS
    IEC_T_LINT    = 0x0b,  /**< int64_t */
    IEC_T_ULINT   = 0x0c,  /**< uint64_t */
    IEC_T_LWORD   = 0x0d,  /**< int64_t */
#else
    IEC_T_NDEF_0B = 0x0b,  /**< not defined */
    IEC_T_NDEF_0C = 0x0c,  /**< not defined */
    IEC_T_NDEF_0D = 0x0d,  /**< not defined */
#endif
    IEC_T_REAL    = 0x0e,  /**< float */
    IEC_T_LREAL   = 0x0f,  /**< double */
    IEC_T_TIME    = 0x10,  /**< time_t */
    IEC_T_DATE    = 0x11,  /**< date_t */
    IEC_T_TOD     = 0x12,  /**< tod_t */
#ifdef ALLOW_64BITS
    IEC_T_DT      = 0x13,  /**< dat_t */
#else
    IEC_T_NDEF_13 = 0x13,  /**< not defined */
#endif
    IEC_T_CHAR    = 0x14,  /**< char */
    IEC_T_WCHAR   = 0x15,  /**< wchar */
    IEC_T_STRING  = 0x16,  /**< string_t */
    IEC_T_WSTRING = 0x17,  /**< string_t */
#ifdef ALLOW_64BITS
    IEC_T_POINTER = 0x18,  /**< pointer_t */
#else
    IEC_T_NDEF_18 = 0x18,  /**< not defined */
#endif
    IEC_T_TABLE   = 0x19,  /**< table_t */
    IEC_T_USER    = 0x1a,  /**< user_t */
    IEC_T_R_EDGE  = 0x1b,  /**< bool */
    IEC_T_F_EDGE  = 0x1c,  /**< bool */
    IEC_T_TIMER   = 0x1d,  /**< timer_t */
    IEC_T_NDEF_1E = 0x1e,  /**< not defined */
    IEC_T_NDEF_1F = 0x1f,  /**< not defined */
} iectype_t;

/**
 * @typedef tt_t
 * @brief status flags
 *
 */
typedef enum {
    TT_MARK     = 0x01, /**< for gc */
    TT_PERSIST  = 0x02, /**< is persist */
    TT_RETAIN   = 0x04, /**< is retain */
    TT_MAINTAIN = 0x08, /**< is persist local */
    TT_CONSTANT = 0x10, /**< is constant */
    TT_INITILZD = 0x20, /**< value initialized */
    TT_FLAG1    = 0x40, /**< generic flag*/
    TT_FLAG2    = 0x80  /**< generic flag*/
} tt_t;

/**
 * @typedef date_t
 * @brief
 *
 */
typedef union date_t {
    struct {
         uint8_t day;   /**< */
         uint8_t month; /**< */
        uint16_t year;  /**< */
    } v;                /**< union */
    uint32_t dw_date;   /**< */
} date_t;

/**
 * @typedef tod_t
 * @brief
 *
 */
typedef union tod_t {
    struct {
        uint8_t csec; /**< */
        uint8_t sec;  /**< */
        uint8_t min;  /**< */
        uint8_t hour; /**< */
    } v;              /**< elements */
    uint32_t dw_tod;  /**< */
} tod_t;

#ifdef ALLOW_64BITS
/**
 * @typedef dat_t
 * @brief
 *
 */
typedef union dat_t {
    struct {
         tod_t tod;  /**< */
        date_t date; /**< */
    } v;             /**< elements */
    uint64_t dw_dat; /**< */
} dat_t;
#endif

/**
 * @typedef pointer_t
 * @brief
 *
 */
#ifdef ALLOW_64BITS
typedef uint64_t pointer_t;
#else
typedef uint32_t pointer_t;
#endif

/**
 * @typedef user_t
 * @brief
 *
 */
typedef struct user_t{
        void *data; /**< */
    uint32_t value; /**< */
} user_t;

/**
 * @typedef string_t
 * @brief
 *
 */
typedef struct string_t {
        bool wstring; /**< true if wide character type */
    uint32_t len;     /**< string length*/
    uint32_t hash;    /**< string hash*/
       str_t *str;    /**< string pointer*/
} string_t;

/**
 * @typedef table_t
 * @brief
 *
 */
typedef struct table_t {
    uint32_t len;    /**< */
        void *table; /**< */
} table_t;

/**
 * @typedef t_timer_t
 * @brief
 *
 */
typedef struct t_timer_t {
        bool q;         /**< output */
      time_t pt;        /**< preset time */
      time_t et;        /**< elapsed time */
        bool timer_run; /**< timer is running */
#ifdef ALLOW_64BITS
    uint64_t t0;        /**< start internal time */
#else
    uint32_t t0;        /**< start internal time */
#endif
} t_timer_t;

/**
 * @typedef iec_t
 * @brief main data container
 *
 */
typedef struct iec_t {
    iectype_t type;     /**< data type */
         tt_t tt;       /**< data tt */
     uint16_t any_type; /**< any type flags */
        void* value;    /**< data value */
} *iec_t;

/**
 * @brief size of types in bits
 */
static uint8_t IEC_T_SIZEOF[] = {
        0,                     /**< IEC_T_NULL */
        sizeof(bool) * 8,      /**< IEC_T_BOOL */
        sizeof(int8_t) * 8,    /**< IEC_T_SINT */
        sizeof(uint8_t) * 8,   /**< IEC_T_USINT */
        sizeof(uint8_t) * 8,   /**< IEC_T_BYTE */
        sizeof(int16_t) * 8,   /**< IEC_T_INT */
        sizeof(uint16_t) * 8,  /**< IEC_T_UINT */
        sizeof(uint16_t) * 8,  /**< IEC_T_WORD */
        sizeof(int32_t) * 8,   /**< IEC_T_DINT */
        sizeof(uint32_t) * 8,  /**< IEC_T_UDINT */
        sizeof(uint32_t) * 8,  /**< IEC_T_DWORD */
#ifdef ALLOW_64BITS
        sizeof(int64_t) * 8,   /**< IEC_T_LINT */
        sizeof(uint64_t) * 8,  /**< IEC_T_ULINT */
        sizeof(int64_t) * 8,   /**< IEC_T_LWORD */
#else
        0,
        0,
        0,
#endif
        sizeof(float) * 8,     /**< IEC_T_REAL */
        sizeof(double) * 8,    /**< IEC_T_LREAL */
        sizeof(time_t) * 8,    /**< IEC_T_TIME */
        sizeof(date_t) * 8,    /**< IEC_T_DATE */
        sizeof(tod_t) * 8,     /**< IEC_T_TOD */
#ifdef ALLOW_64BITS
        sizeof(dat_t) * 8,     /**< IEC_T_DT */
#else
        0,
#endif
        sizeof(char) * 8,      /**< IEC_T_CHAR */
        sizeof(wchar_t) * 8,   /**< IEC_T_WCHAR */
        sizeof(string_t) * 8,  /**< IEC_T_STRING */
        sizeof(string_t) * 8,  /**< IEC_T_WSTRING */
        sizeof(pointer_t) * 8, /**< IEC_T_POINTER */
        sizeof(table_t) * 8,   /**< IEC_T_TABLE */
        sizeof(user_t) * 8,    /**< IEC_T_USER */
        sizeof(bool) * 8,      /**< IEC_T_R_EDGE */
        sizeof(bool) * 8,      /**< IEC_T_F_EDGE */
        sizeof(t_timer_t) * 8, /**< IEC_T_TIMER */
        0,                     /**< IEC_T_NDEF_1E */
        0,                     /**< IEC_T_NDEF_1F */
};

///////////////////////////// MACROS ///////////////////////////

/**
 * @name utils
 * @brief internal utils
 *
 */
/**@{*/
#define CONCAT(a, b)          CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b)    a ## b
#define LABEL(base,x)         CONCAT(base, x)
#define sign(x)               (((x) > 0) - ((x) < 0))
#define IEC_ALLOC             malloc(sizeof(struct iec_t))
/**@}*/

/**
 * @name any types
 * @brief check any types
 *
 */
/**@{*/
#ifdef ALLOW_64BITS
#define ANY_BIT(x)            (x == IEC_T_BOOL || x == IEC_T_UINT || x == IEC_T_WORD || x == IEC_T_DWORD || x == IEC_T_LWORD)
#define ANY_UNSIGNED(x)       (x == IEC_T_USINT || x == IEC_T_UINT || x == IEC_T_UDINT || x == IEC_T_ULINT)
#define ANY_SIGNED(x)         (x == IEC_T_SINT || x == IEC_T_INT || x == IEC_T_DINT || x == IEC_T_LINT)
#define ANY_INT(x)            (x == IEC_T_SINT || x == IEC_T_INT || x == IEC_T_DINT || x == IEC_T_LINT || x == IEC_T_USINT || x == IEC_T_UINT \
                                || x == IEC_T_UDINT || x == IEC_T_ULINT)
#define ANY_DATE(x)           (x == IEC_T_DATE || x == IEC_T_DT)
#else
#define ANY_BIT(x)            (x == IEC_T_BOOL || x == IEC_T_UINT || x == IEC_T_WORD || x == IEC_T_DWORD || x == IEC_T_R_EDGE || x == IEC_T_F_EDGE)
#define ANY_UNSIGNED(x)       (x == IEC_T_USINT || x == IEC_T_UINT || x == IEC_T_UDINT)
#define ANY_SIGNED(x)         (x == IEC_T_SINT || x == IEC_T_INT || x == IEC_T_DINT)
#define ANY_INT(x)            (x == IEC_T_SINT || x == IEC_T_INT || x == IEC_T_DINT || x == IEC_T_USINT || x == IEC_T_UINT || x == IEC_T_UDINT)
#define ANY_DATE(x)           (x == IEC_T_DATE)
#endif
#define ANY_BOOL(x)           (x == IEC_T_BOOL || x == IEC_T_R_EDGE || x == IEC_T_F_EDGE)
#define ANY_REAL(x)           (x == IEC_T_REAL || x == IEC_T_LREAL)
#define ANY_NUM(x)            (ANY_INT(x) || ANY_REAL(x))
#define ANY_STRING(x)         (x == IEC_T_STRING || x == IEC_T_WSTRING)
#define ANY_ELEMENTARY(x)     (ANY_BIT(x) || ANY_NUM(x) || ANY_DATE(x) || ANY_STRING(x) || x == IEC_T_TIME)
#define ANY_MAGNITUDE(x)      ((ANY_INT(x) || ANY_REAL(x) || x == IEC_T_TIME) && !(x == IEC_T_NULL))
#define ANY_INTEGRAL(x)       (ANY_INT(x) || ANY_BIT(x))
#define ANY_CHAR(x)           (x == IEC_T_CHAR || x == IEC_T_WCHAR)
#define ANY_CHARS(x)          (ANY_CHAR(x) || ANY_STRING(x))
/**@}*/

/**
 * @name any type bit
 * @brief
 *
 */
/**@{*/
#define ANY_NUM_BIT           0x0001
#define ANY_DATE_BIT          0x0002
#define ANY_BIT_BIT           0x0004
#define ANY_REAL_BIT          0x0008
#define ANY_STRING_BIT        0x0010
#define ANY_ELEMENTARY_BIT    0x0020
#define ANY_MAGNITUDE_BIT     0x0040
#define ANY_INT_BIT           0x0080
#define ANY_INTEGRAL_BIT      0x0100
#define ANY_UNSIGNED_BIT      0x0200
#define ANY_SIGNED_BIT        0x0400
#define ANY_CHAR_BIT          0x0800
#define ANY_CHARS_BIT         0x1000
#define _BIT                  0
/**@}*/

/**
 * @name bit manipulation
 * @brief
 *
 */
/**@{*/
#define GET_BIT(v, b)         ((v >> b) & 1)
#define SET_BIT(v, b)         ((v) | (1 << b))
#define CLR_BIT(v, b)         ((v) & ~(1 << b))
#define GET_BIT_VB(v, b)      (v & b) ? 1 : 0
#define SET_BIT_VB(v, b)      ((v) | b)
#define CLR_BIT_VB(v, b)      ((v) & ~b)
/**@}*/

/**
 * @name tt manipulation
 * @brief
 *
 */
/**@{*/
#define iec_is_mark(v)           (GET_BIT_VB((v)->tt, TT_MARK))
#define iec_is_persist(v)        (GET_BIT_VB((v)->tt, TT_PERSIST))
#define iec_is_retain(v)         (GET_BIT_VB((v)->tt, TT_RETAIN))
#define iec_is_maintain(v)       (GET_BIT_VB((v)->tt, TT_MAINTAIN))
#define iec_is_constant(v)       (GET_BIT_VB((v)->tt, TT_CONSTANT))
#define iec_is_initialized(v)    (GET_BIT_VB((v)->tt, TT_INITILZD))
#define iec_is_flag1(v)          (GET_BIT_VB((v)->tt, TT_FLAG1))
#define iec_is_flag2(v)          (GET_BIT_VB((v)->tt, TT_FLAG2))
#define iec_set_mark(v)          ((v)->tt = SET_BIT_VB((v)->tt, TT_MARK))
#define iec_set_persist(v)       ((v)->tt = SET_BIT_VB((v)->tt, TT_PERSIST))
#define iec_set_retain(v)        ((v)->tt = SET_BIT_VB((v)->tt, TT_RETAIN))
#define iec_set_maintain(v)      ((v)->tt = SET_BIT_VB((v)->tt, TT_MAINTAIN))
#define iec_set_constant(v)      ((v)->tt = SET_BIT_VB((v)->tt, TT_CONSTANT))
#define iec_set_initialized(v)   ((v)->tt = SET_BIT_VB((v)->tt, TT_INITILZD))
#define iec_set_flag1(v)         ((v)->tt = SET_BIT_VB((v)->tt, TT_FLAG1))
#define iec_set_flag2(v)         ((v)->tt = SET_BIT_VB((v)->tt, TT_FLAG2))
#define iec_unset_mark(v)        ((v)->tt = CLR_BIT_VB((v)->tt, TT_MARK))
#define iec_unset_persist(v)     ((v)->tt = CLR_BIT_VB((v)->tt, TT_PERSIST))
#define iec_unset_retain(v)      ((v)->tt = CLR_BIT_VB((v)->tt, TT_RETAIN))
#define iec_unset_maintain(v)    ((v)->tt = CLR_BIT_VB((v)->tt, TT_MAINTAIN))
#define iec_unset_constant(v)    ((v)->tt = CLR_BIT_VB((v)->tt, TT_CONSTANT))
#define iec_unset_initialized(v) ((v)->tt = CLR_BIT_VB((v)->tt, TT_INITILZD))
#define iec_unset_flag1(v)       ((v)->tt = CLR_BIT_VB((v)->tt, TT_FLAG1))
#define iec_unset_flag2(v)       ((v)->tt = CLR_BIT_VB((v)->tt, TT_FLAG2))
/**@}*/

/**
 * @def MAX_TYPE
 * @brief
 *
 */
#define MAX_TYPE(a,b)               \
            (a)->type > (b)->type ? \
            (a)->type : (b)->type

/**
 * @def IS_TRUNCATED
 * @brief
 *
 */
#define IS_TRUNCATED(a,b)                 \
            (a)->type > (b)->type ? 0 : 1

/**
 * @name iec_get_value
 * @brief
 *
 */
/**@{*/
#define iec_get_value(data)                                                         \
            ((data)->type == IEC_T_BOOL)                                            \
              || ((data)->type == IEC_T_R_EDGE)                                     \
              || ((data)->type == IEC_T_F_EDGE)  ? *((bool*)((data)->value))      : \
            ((data)->type == IEC_T_SINT)         ? *((int8_t*)((data)->value))    : \
            ((data)->type == IEC_T_USINT                                            \
              || (data)->type == IEC_T_BYTE)     ? *((uint8_t*)((data)->value))   : \
            ((data)->type == IEC_T_INT)          ? *((int16_t*)((data)->value))   : \
            ((data)->type == IEC_T_UINT)                                            \
              || ((data)->type == IEC_T_WORD)    ? *((uint16_t*)((data)->value))  : \
            ((data)->type == IEC_T_DINT)         ? *((int32_t*)((data)->value))   : \
            ((data)->type == IEC_T_UDINT)                                           \
              || ((data)->type == IEC_T_DWORD)   ? *((uint32_t*)((data)->value))  : \
            ((data)->type == IEC_T_REAL)         ? *((float*)((data)->value))     : \
            ((data)->type == IEC_T_TIME)                                            \
              || ((data)->type == IEC_T_LREAL)   ? *((double*)((data)->value))    : \
            GV_64(data)
#ifdef ALLOW_64BITS
#define GV_64(data)                                                                 \
            ((data)->type == IEC_T_ULINT)      ? *((uint64_t*)((data)->value))    : \
            ((data)->type == IEC_T_LINT)                                            \
              || ((data)->type == IEC_T_LWORD) ? *((int64_t*)((data)->value))     : \
            ((data)->type == IEC_T_POINTER)    ? *((pointer_t*)((data)->value))   : \
            0
#else
#define GV_64(data) 0
#endif
/**@}*/

/**
 * @name iec_get_value_type
 * @brief
 *
 */
/**@{*/
#define iec_get_value_type(data, type)                                       \
            (type == IEC_T_BOOL)                                             \
              || (type == IEC_T_R_EDGE)                                      \
              || (type == IEC_T_F_EDGE)  ? *((bool*)(data))               : \
            (type == IEC_T_SINT)         ? *((int8_t*)((data)))            : \
            (type == IEC_T_USINT                                             \
              || type == IEC_T_BYTE)     ? *((uint8_t*)((data)))           : \
            (type == IEC_T_INT)          ? *((int16_t*)((data)))           : \
            (type == IEC_T_UINT)                                             \
              || (type == IEC_T_WORD)    ? *((uint16_t*)((data)))          : \
            (type == IEC_T_DINT)         ? *((int32_t*)((data)))           : \
            (type == IEC_T_UDINT)                                            \
              || (type == IEC_T_DWORD)   ? *((uint32_t*)((data)))          : \
            (type == IEC_T_REAL)         ? *((float*)((data)))             : \
            (type == IEC_T_TIME)                                             \
              || (type == IEC_T_LREAL)   ? *((double*)((data)))            : \
            GVT_64(data, type)
#ifdef ALLOW_64BITS
#define GVT_64(data, type)                                                   \
            (type == IEC_T_ULINT)      ? *((uint64_t*)((data)))            : \
            (type == IEC_T_LINT)                                             \
              || (type == IEC_T_LWORD) ? *((int64_t*)((data)))             : \
            (type == IEC_T_POINTER)    ? *((pointer_t*)((data)))           : \
            0
#else
#define GVT_64(data, type) 0
#endif
/**@}*/

/**
 * @name iec_get_valuep
 * @brief
 *
 */
/**@{*/
#define iec_get_valuep(data)                                                     \
            ((data)->type == IEC_T_BOOL)                                         \
			  || ((data)->type == IEC_T_R_EDGE)                                  \
			  || ((data)->type == IEC_T_F_EDGE)  ? ((bool*)(data)->value)      : \
            ((data)->type == IEC_T_SINT)         ? ((int8_t*)(data)->value)    : \
            ((data)->type == IEC_T_USINT                                         \
              || (data)->type == IEC_T_BYTE)     ? ((uint8_t*)(data)->value)   : \
            ((data)->type == IEC_T_INT)          ? ((int16_t*)(data)->value)   : \
            ((data)->type == IEC_T_UINT)                                         \
              || ((data)->type == IEC_T_WORD)    ? ((uint16_t*)(data)->value)  : \
            ((data)->type == IEC_T_DINT)         ? ((int32_t*)(data)->value)   : \
            ((data)->type == IEC_T_UDINT)                                        \
              || ((data)->type == IEC_T_DWORD)   ? ((uint32_t*)(data)->value)  : \
            ((data)->type == IEC_T_REAL)         ? ((float*)(data)->value)     : \
            ((data)->type == IEC_T_TIME)         ? ((double*)(data)->value)    : \
            ((data)->type == IEC_T_LREAL)        ? ((double*)(data)->value)    : \
            GVP_64(data)
#ifdef ALLOW_64BITS
#define GVP_64(data)                                                             \
            ((data)->type == IEC_T_ULINT)      ? ((uint64_t*)(data)->value)    : \
            ((data)->type == IEC_T_LINT)                                         \
              || ((data)->type == IEC_T_LWORD) ? ((int64_t*)(data)->value)     : \
            ((data)->type == IEC_T_POINTER)    ? ((pointer_t*)(data)->value)   : \
            0
#else
#define GVP_64(data) 0
#endif
/**@}*/

/**
 * @name iec_get_tovoid
 * @brief
 *
 */
/**@{*/
#define iec_get_tovoid(data, var)                                          \
		    maxuint_t CONCAT(var, _) = 0;                                  \
		    void *var = &CONCAT(var, _);                                   \
            switch ((data)->type) {                                        \
                case IEC_T_F_EDGE:                                         \
                case IEC_T_R_EDGE:                                         \
                case IEC_T_BOOL:                                           \
                    *((bool*)(var)) = *((bool*)((data)->value));           \
                    break;                                                 \
                case IEC_T_SINT:                                           \
                    *((int8_t*)(var)) = *((int8_t*)((data)->value));       \
                    break;                                                 \
                case IEC_T_USINT:                                          \
                case IEC_T_BYTE:                                           \
                    *((uint8_t*)(var)) = *((uint8_t*)((data)->value));     \
                    break;                                                 \
                case IEC_T_INT:                                            \
                    *((int16_t*)(var)) = *((int16_t*)((data)->value));     \
                    break;                                                 \
                case IEC_T_UINT:                                           \
                case IEC_T_WORD:                                           \
                    *((uint16_t*)(var)) = *((uint16_t*)((data)->value));   \
                    break;                                                 \
                case IEC_T_DINT:                                           \
                    *((int32_t*)(var)) = *((int32_t*)((data)->value));     \
                    break;                                                 \
                case IEC_T_UDINT:                                          \
                case IEC_T_DWORD:                                          \
                    *((uint32_t*)(var)) = *((uint32_t*)((data)->value));   \
                    break;                                                 \
                case IEC_T_REAL:                                           \
                    *((float*)(var)) = *((float*)((data)->value));         \
                    break;                                                 \
                case IEC_T_LREAL:                                          \
                    *((double*)(var)) = *((double*)((data)->value));       \
                    break;                                                 \
                case IEC_T_TIME:                                           \
                    *((double*)(var)) = *((double*)((data)->value));       \
                    break;                                                 \
                case IEC_T_CHAR:                                           \
                    *((char*)(var)) = *((char*)((data)->value));           \
                    break;                                                 \
                case IEC_T_WCHAR:                                          \
                    *((wchar_t*)(var)) = *((wchar_t*)((data)->value));     \
                    break;                                                 \
                GTV_64(data, var)                                          \
                default:                                                   \
                    *((bool*)(var)) = 0;                                   \
                    break;                                                 \
            }
#ifdef ALLOW_64BITS
#define GTV_64(data, var)                                                  \
            case IEC_T_ULINT:                                              \
                *((uint64_t*)(var)) = *((uint64_t*)((data)->value));       \
                break;                                                     \
            case IEC_T_LINT:                                               \
            case IEC_T_LWORD:                                              \
                *((int64_t*)(var)) = *((int64_t*)((data)->value));         \
                break;                                                     \
            case IEC_T_POINTER:                                            \
                *((pointer_t*)(var)) = *((pointer_t*)((data)->value));     \
                break;
#define maxuint_t  uint64_t
#else
#define GTV_64(data, var)
#define maxuint_t uint32_t
#endif
/**@}*/

/**
 * @def iec_get_string
 * @brief
 *
 */
#define iec_get_string(data)  (((string_t*) (data->value))->str)

/**
 * @name iec_set_value
 * @brief
 *
 */
/**@{*/
#define iec_set_value(data, val)                          \
            switch ((data)->type) {                       \
                case IEC_T_F_EDGE:                        \
                case IEC_T_R_EDGE:                        \
                case IEC_T_BOOL:                          \
				    *((bool*)((data)->value)) = val;      \
                    break;                                \
                case IEC_T_SINT:                          \
                    *((int8_t*)((data)->value)) = val;    \
                    break;                                \
                case IEC_T_USINT:                         \
                case IEC_T_BYTE:                          \
                    *((uint8_t*)((data)->value)) = val;   \
                    break;                                \
                case IEC_T_INT:                           \
                    *((int16_t*)((data)->value)) = val;   \
                    break;                                \
                case IEC_T_UINT:                          \
                case IEC_T_WORD:                          \
                    *((uint16_t*)((data)->value)) = val;  \
                    break;                                \
                case IEC_T_DINT:                          \
                    *((int32_t*)((data)->value)) = val;   \
                    break;                                \
                case IEC_T_UDINT:                         \
                case IEC_T_DWORD:                         \
                    *((uint32_t*)((data)->value)) = val;  \
                    break;                                \
                case IEC_T_REAL:                          \
				    *((float*)((data)->value)) = val;     \
				    break;                                \
                case IEC_T_LREAL:                         \
                    *((double*)((data)->value)) = val;    \
                    break;                                \
                case IEC_T_TIME:                          \
                    *((double*)((data)->value)) = val;    \
                    break;                                \
                case IEC_T_CHAR:                          \
                    *((char*)((data)->value)) = val;      \
                    break;                                \
                case IEC_T_WCHAR:                         \
                    *((wchar_t*)((data)->value)) = val;   \
                    break;                                \
                SV_64(data, val)                          \
                default:                                  \
                    (data)->value = NULL;                 \
            }
#ifdef ALLOW_64BITS
#define SV_64(data, val)                                  \
            case IEC_T_ULINT:                             \
                *((uint64_t*)((data)->value)) = val;      \
                break;                                    \
            case IEC_T_LINT:                              \
            case IEC_T_LWORD:                             \
                *((int64_t*)((data)->value)) = val;       \
                break;                                    \
            case IEC_T_POINTER:                           \
                *((pointer_t*)((data)->value)) = val;     \
                break;
#else
#define SV_64(data, val)
#endif
/**@}*/

/**
 * @name iec_set_value_type
 * @brief
 *
 */
/**@{*/
#define iec_set_value_type(data, val, type)     \
            switch (type) {                     \
                case IEC_T_F_EDGE:              \
                case IEC_T_R_EDGE:              \
                case IEC_T_BOOL:                \
                    *((bool*)(data)) = val;     \
                    break;                      \
                case IEC_T_SINT:                \
                    *((int8_t*)(data)) = val;   \
                    break;                      \
                case IEC_T_USINT:               \
                case IEC_T_BYTE:                \
                    *((uint8_t*)(data)) = val;  \
                    break;                      \
                case IEC_T_INT:                 \
                    *((int16_t*)(data)) = val;  \
                    break;                      \
                case IEC_T_UINT:                \
                case IEC_T_WORD:                \
                    *((uint16_t*)(data)) = val; \
                    break;                      \
                case IEC_T_DINT:                \
                    *((int32_t*)(data)) = val;  \
                    break;                      \
                case IEC_T_UDINT:               \
                case IEC_T_DWORD:               \
                    *((uint32_t*)(data)) = val; \
                    break;                      \
                case IEC_T_REAL:                \
                    *((float*)(data)) = val;    \
                    break;                      \
                case IEC_T_LREAL:               \
                    *((double*)(data)) = val;   \
                    break;                      \
                case IEC_T_TIME:                \
                    *((double*)(data)) = val;   \
                    break;                      \
                case IEC_T_CHAR:                \
                    *((char*)(data)) = val;     \
                    break;                      \
                case IEC_T_WCHAR:               \
                    *((wchar_t*)(data)) = val;  \
                    break;                      \
                SVT_64(data, val)               \
                default:                        \
                    (data) = NULL;              \
            }
#ifdef ALLOW_64BITS
#define SVT_64(data, val)                       \
            case IEC_T_ULINT:                   \
                *((uint64_t*)(data)) = val;     \
                break;                          \
            case IEC_T_LINT:                    \
            case IEC_T_LWORD:                   \
                *((int64_t*)(data)) = val;      \
                break;                          \
            case IEC_T_POINTER:                 \
                *((pointer_t*)(data)) = val;    \
                break;
#else
#define SVT_64(data, val)
#endif
/**@}*/

/**
 * @name iec_set_fromvoid
 * @brief
 *
 */
/**@{*/
#define iec_set_fromvoid(data, val)                                     \
            switch ((data)->type) {                                     \
                case IEC_T_F_EDGE:                                      \
                case IEC_T_R_EDGE:                                      \
                case IEC_T_BOOL:                                        \
                    *((bool*)((data)->value)) = *((bool*)val);          \
                    break;                                              \
                case IEC_T_SINT:                                        \
                    *((int8_t*)((data)->value)) = *((int8_t*)val);      \
                    break;                                              \
                case IEC_T_USINT:                                       \
                case IEC_T_BYTE:                                        \
                    *((uint8_t*)((data)->value)) = *((uint8_t*)val);    \
                    break;                                              \
                case IEC_T_INT:                                         \
                    *((int16_t*)((data)->value)) = *((int16_t*)val);    \
                    break;                                              \
                case IEC_T_UINT:                                        \
                case IEC_T_WORD:                                        \
                    *((uint16_t*)((data)->value)) = *((uint16_t*)val);  \
                    break;                                              \
                case IEC_T_DINT:                                        \
                    *((int32_t*)((data)->value)) = *((int32_t*)val);    \
                    break;                                              \
                case IEC_T_UDINT:                                       \
                case IEC_T_DWORD:                                       \
                    *((uint32_t*)((data)->value)) = *((uint32_t*)val);  \
                    break;                                              \
                case IEC_T_REAL:                                        \
                    *((float*)((data)->value)) = *((float*)val);        \
                    break;                                              \
                case IEC_T_LREAL:                                       \
                    *((double*)((data)->value)) = *((double*)val);      \
                    break;                                              \
                case IEC_T_TIME:                                        \
                    *((double*)((data)->value)) = *((double*)val);      \
                    break;                                              \
                case IEC_T_CHAR:                                        \
                    *((char*)((data)->value)) = *((char*)val);          \
                    break;                                              \
                case IEC_T_WCHAR:                                       \
                    *((wchar_t*)((data)->value)) = *((wchar_t*)val);    \
                    break;                                              \
                SFV_64                                                  \
                default:                                                \
                    (data)->value = NULL;                               \
            }
#ifdef ALLOW_64BITS
#define SFV_64                                                          \
            case IEC_T_ULINT:                                           \
                *((uint64_t*)((data)->value)) = *((uint64_t*)val);      \
                break;                                                  \
            case IEC_T_LINT:                                            \
            case IEC_T_LWORD:                                           \
                *((int64_t*)((data)->value)) = *((int64_t*)val);        \
                break;                                                  \
            case IEC_T_POINTER:                                         \
                *((pointer_t*)((data)->value)) = *((pointer_t*)val);    \
                break;
#else
#define SFV_64
#endif
/**@}*/

/**
 * @def IEC_ANYTYPE
 * @brief mask for type
 *
 */
#define IEC_ANYTYPE(type)                  \
              (ANY_NUM(type))              \
            | (ANY_DATE(type)       << 1)  \
            | (ANY_BIT(type)        << 2)  \
            | (ANY_REAL(type)       << 3)  \
            | (ANY_STRING(type)     << 4)  \
            | (ANY_ELEMENTARY(type) << 5)  \
            | (ANY_MAGNITUDE(type)  << 6)  \
            | (ANY_INT(type)        << 7)  \
            | (ANY_INTEGRAL(type)   << 8)  \
            | (ANY_UNSIGNED(type)   << 9)  \
            | (ANY_SIGNED(type)     << 10) \
            | (ANY_CHAR(type)       << 11) \
            | (ANY_CHARS(type)      << 12)

/**
 * @def iec_anytype_allowed
 * @brief check if any_type if allowed
 *
 */
#define iec_anytype_allowed(data, A, B, C, D, E, F)                                                                             \
            if((data) == NULL || !((data)->any_type & (A ## _BIT | B ## _BIT | C ## _BIT | D ## _BIT | E ## _BIT | F ## _BIT))) \
                return IEC_NAT

/**
 * @def iec_type_allowed
 * @brief check for type allowed
 *
 */
#define iec_type_allowed(data, A)                      \
            if(data == NULL || !((data)->type == (A))) \
                return IEC_NAT

/**
 * @def iec_fit
 * @brief return true if value fit in type
 * @todo INCOMPLETE
 */
#define iec_fit(data, value)                                                                                              \
            ((data)->type == IEC_T_BOOL)                                                                                  \
              || ((data)->type == IEC_T_F_EDGE)                                                                           \
              || ((data)->type == IEC_T_R_EDGE) ? (value >= UCHAR_MIN) && (value <= UCHAR_MAX) && (round(val) == value) : \
            ((data)->type == IEC_T_SINT)        ? (value >= SCHAR_MIN) && (value <= SCHAR_MAX) && (round(val) == value) : \
            ((data)->type == IEC_T_USINT                                                                                  \
              || (data)->type == IEC_T_BYTE)    ? (value >= UCHAR_MIN) && (value <= UCHAR_MAX) && (round(val) == value) : \
            ((data)->type == IEC_T_INT)         ? (value >= INT_MIN) && (value <= INT_MAX) && (round(val) == value)     : \
            ((data)->type == IEC_T_UINT)                                                                                  \
              || ((data)->type == IEC_T_WORD)   ? (value >= UINT_MIN) && (value <= UINT_MAX) && (round(val) == value)   : \
            ((data)->type == IEC_T_DINT)        ? (value >= LONG_MIN) && (value <= LONG_MAX) && (round(val) == value)   : \
            ((data)->type == IEC_T_UDINT)                                                                                 \
              || ((data)->type == IEC_T_DWORD)  ? (value >= ULONG_MIN) && (value <= ULONG_MAX) && (round(val) == value) : \
            ((data)->type == IEC_T_REAL)        ? 0 :                                                                     \
            ((data)->type == IEC_T_TIME)        ? 0 :                                                                     \
            ((data)->type == IEC_T_LREAL)       ? 0 :                                                                     \
            FT_64(data)
#ifdef ALLOW_64BITS
#define FT_64(data)                                                                                                       \
            ((data)->type == IEC_T_ULINT)       ? 0  :                                                                    \
            ((data)->type == IEC_T_LINT)                                                                                  \
              || ((data)->type == IEC_T_LWORD)  ? 0  :                                                                    \
            ((data)->type == IEC_T_POINTER)     ? 0  :                                                                    \
            0
#else
#define FT_64(data) 0
#endif

/**
 * @def iec_timer
 * @brief
 *
 */
#define iec_timer(v)  ((t_timer_t*)((v)->value))
////////////////////////////////////////////////////////////////

/**
 * @fn static inline void iec_new_value(void **nw, iectype_t type)
 * @brief
 *
 * @param nw
 * @param type
 */
static inline void iec_new_value(void **nw, iectype_t type) {
    switch (type) {
        case IEC_T_F_EDGE:
        case IEC_T_R_EDGE:
        case IEC_T_BOOL:
            (*nw) = malloc(sizeof(bool));
            break;

        case IEC_T_SINT:
            (*nw) = malloc(sizeof(int8_t));
            break;

        case IEC_T_USINT:
        case IEC_T_BYTE:
            (*nw) = malloc(sizeof(uint8_t));
            break;

        case IEC_T_INT:
            (*nw) = malloc(sizeof(int16_t));
            break;

        case IEC_T_UINT:
        case IEC_T_WORD:
            (*nw) = malloc(sizeof(uint16_t));
            break;

        case IEC_T_DINT:
            (*nw) = malloc(sizeof(int32_t));
            break;

        case IEC_T_UDINT:
        case IEC_T_DWORD:
            (*nw) = malloc(sizeof(uint32_t));
            break;

        case IEC_T_REAL:
            (*nw) = malloc(sizeof(float));
            break;

        case IEC_T_LREAL:
            (*nw) = malloc(sizeof(double));
            break;

        case IEC_T_TIME:
            (*nw) = malloc(sizeof(double));
            break;

        case IEC_T_DATE:
            (*nw) = malloc(sizeof(date_t));
            break;

        case IEC_T_TOD:
            (*nw) = malloc(sizeof(tod_t));
            break;

        case IEC_T_CHAR:
            (*nw) = malloc(sizeof(char));
            break;

        case IEC_T_WCHAR:
            (*nw) = malloc(sizeof(wchar_t));
            break;

        case IEC_T_STRING:
        case IEC_T_WSTRING:
            (*nw) = malloc(sizeof(string_t));
            break;
#ifdef ALLOW_64BITS
        case IEC_T_DT:
            (*nw) = malloc(sizeof(dat_t));
            break;

        case IEC_T_ULINT:
            (*nw) = malloc(sizeof(uint64_t));
            break;

        case IEC_T_LINT:
        case IEC_T_LWORD:
            (*nw) = malloc(sizeof(int64_t));
            break;
#endif
        case IEC_T_POINTER:
            (*nw) = malloc(sizeof(pointer_t));
            break;

        case IEC_T_TABLE:
            (*nw) = malloc(sizeof(table_t));
            break;

        case IEC_T_USER:
            (*nw) = malloc(sizeof(user_t));
            break;
        case IEC_T_TIMER:
            (*nw) = malloc(sizeof(t_timer_t));
            break;

        default:
            (*nw) = NULL;
            break;
    }
}

/**
 * @fn static inline void iec_init(iec_t *nw, iectype_t type)
 * @brief create new value
 *
 * @param nw
 * @param type
 */
static inline void iec_init(iec_t *nw, iectype_t type) {
    (*nw)->type = type;
    (*nw)->any_type = IEC_ANYTYPE(type);
    (*nw)->tt = 0;
    iec_new_value(&((*nw)->value), type);
}

/**
 * @fn static inline void iec_free_value(iec_t *var)
 * @brief
 *
 * @param var
 */
static inline void iec_free_value(iec_t *var) {
    if ((*var) == NULL)
        return;
    if ((*var)->type != IEC_T_NULL)
        free((*var)->value);
}

/**
 * @fn static inline void iec_deinit(iec_t *var)
 * @brief
 *
 * @param var
 */
static inline void iec_deinit(iec_t *var) {
    iec_free_value(var);
    free(*var);
}

/**
 * @fn static inline void iec_totype(iec_t *data, uint8_t tpy)
 * @brief
 *
 * @param data
 * @param tpy
 */
static inline void iec_totype(iec_t *data, uint8_t tpy) {
    void *_tmp_ = NULL;
    uint8_t tp_old = (*data)->type;

    if (ANY_NUM(tp_old) || ANY_BOOL(tp_old)) {
        iec_new_value(&_tmp_, tp_old);
        iec_set_value_type(_tmp_, iec_get_value(*data), tp_old);
    }

    (*data)->type = tpy;
    (*data)->any_type = IEC_ANYTYPE(tpy);

    iec_free_value(data);
    if (!ANY_STRING(tp_old)) {
        iec_new_value(&((*data)->value), tpy);
    }

    if (ANY_NUM(tp_old) || ANY_BOOL(tp_old)) {
        iec_set_value((*data), iec_get_value_type(_tmp_, tp_old));
        free(_tmp_);
    }
}

/**
 * @fn static inline void iec_type_promote(iec_t *data, uint8_t tpy)
 * @brief
 *
 * @param data
 * @param tpy
 */
static inline void iec_type_promote(iec_t *data, uint8_t tpy) {
    if ((*data)->type < tpy) {
        iec_totype(data, tpy);
    }
}

#endif /* IEC61131LIB_H_ */
