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

#ifndef IEC_LITERALS_H_
#define IEC_LITERALS_H_

#include <ctype.h>
#include <string.h>

#include "util_buffer_string.h"

enum LITERALS {
    IEC_LIT_BOOLEAN,       // 0x00
    IEC_LIT_DURATION,      // 0x01
    IEC_LIT_DATE,          // 0x02
    IEC_LIT_TIME_OF_DAY,   // 0x03
    IEC_LIT_DATE_AND_TIME, // 0x04
    IEC_LIT_INTEGER,       // 0x05
    IEC_LIT_REAL,          // 0x06
    IEC_LIT_REAL_EXP,      // 0x07
    IEC_LIT_BASE2,         // 0x08
    IEC_LIT_BASE8,         // 0x09
    IEC_LIT_BASE16,        // 0x0a
    /* ... */
    IEC_LIT_NONE = 0xff    // 0xff
};

const char *IEC_DATATYPE_PFX[] = {
    "2#",            // 0
    "8#",            //
    "16#",           //
    "T#",            //
    "TIME#",         //
    "D#",            //
    "DATE#",         //
    "TOD#",          //
    "TIME_OF_DAY#",  //
    "DT#",           //
    "DATE_AND_TIME#" // 10
};

const uint8_t IEC_LITERAL_TYPE[]= {
    IEC_LIT_BASE2,
    IEC_LIT_BASE8,
    IEC_LIT_BASE16,
    IEC_LIT_DURATION,
    IEC_LIT_DURATION,
    IEC_LIT_DATE,
    IEC_LIT_DATE,
    IEC_LIT_TIME_OF_DAY,
    IEC_LIT_TIME_OF_DAY,
    IEC_LIT_DATE_AND_TIME,
    IEC_LIT_DATE_AND_TIME
};


const char *IEC_IECTYPE_PFX[] = {
    "?#",       // 0
    "BOOL#",    //
    "SINT#",    //
    "USINT#",   //
    "BYTE#",    //
    "INT#",     //
    "UINT#",    //
    "WORD#",    //
    "DINT#",    //
    "UDINT#",   //
    "DWORD#",   //
#ifdef ALLOW_64BITS
    "LINT#",    //
    "ULINT#",   //
    "LWORD#",   //
#else
    "?#",       //
    "?#",       //
    "?#",       //
#endif
    "REAL#",    //
    "LREAL#",   //
    "TIME#",    //
    "DATE#",    //
    "TOD#",     //
#ifdef ALLOW_64BITS
    "DT#",      //
#else
    "?#",       //
#endif
    "CHAR#",    //
    "WCHAR#",   //
    "STRING#",  //
    "WSTRING#", //
#ifdef ALLOW_64BITS
    "POINTER#", //
#else
    "?#",       //
#endif
    "TABLE#",   //
    "USER#",    //
    "?#",       //
    "?#",       //
    "?#",       //
    "?#",       //
    "?#",       // 31
};

uint8_t iec_identify_literal(BufferString *str, uint8_t *iectype) {
    uint8_t n;

    trimAll(str);
    toUpperCase(str);

    // replace boolean type
    replaceAllOccurrences(str, "TRUE", "1");
    replaceAllOccurrences(str, "FALSE", "0");

    // delete _
    BufferString *tmp = EMPTY_STRING(255);
    while(indexOfChar(str, '_', 0) != -1) {
        substringAfter(str, tmp, "_");
        substringBefore(str, str, "_");
        concatString(str, tmp);
    }

    // search typed literal
    *iectype = IEC_LIT_NONE;
    for (n = 0; n < 32; n++) {
        if (isStringStartsWith(str, IEC_IECTYPE_PFX[n], 0)) {
            *iectype = n;
            break;
        }
    }
    if(*iectype != IEC_LIT_NONE)
        substringAfter(str, str, "#");

    if (*iectype < IEC_LIT_INTEGER)
        return IEC_LIT_NONE;

    // search data prefix
    uint8_t datatype = IEC_LIT_NONE;
    for (n = 0; n < 10; n++) {
        if (isStringStartsWith(str, IEC_DATATYPE_PFX[n], 0)) {
            datatype = n;
            break;
        }
    }
    if (datatype != IEC_LIT_NONE) {
        substringAfter(str, str, "#");
        return IEC_LITERAL_TYPE[datatype];
    }

    if ((indexOfChar(str, 'e', 0) != -1) || (indexOfChar(str, 'E', 0) != -1))
        return IEC_LIT_REAL_EXP;

    if (indexOfChar(str, '.', 0) != -1)
        return IEC_LIT_REAL;

    return IEC_LIT_INTEGER;
}

void literal_toiec(iec_t *result, BufferString str) {
    uint8_t datatype;
    uint8_t iectype;

    datatype = iec_identify_literal(&str, &iectype);

    switch (datatype) {
        case IEC_LIT_BOOLEAN:

            break;
        case IEC_LIT_DURATION:

            break;
        case IEC_LIT_DATE:

            break;
        case IEC_LIT_TIME_OF_DAY:

            break;
        case IEC_LIT_DATE_AND_TIME:

            break;
        case IEC_LIT_INTEGER:

            break;
        case IEC_LIT_REAL:

            break;
        case IEC_LIT_REAL_EXP:

            break;
        case IEC_LIT_BASE2:

            break;
        case IEC_LIT_BASE8:

            break;
        case IEC_LIT_BASE16:

            break;
        default:

    }

}

#endif /* IEC_LITERALS_H_ */
