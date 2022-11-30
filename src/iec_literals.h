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

#include <stdstring.h>

enum LITERALS {
    IEC_LIT_INTEGER,       // 0x00
    IEC_LIT_REAL,          // 0x01
    IEC_LIT_REAL_EXP,      // 0x02
    IEC_LIT_BASE2,         // 0x03
    IEC_LIT_BASE8,         // 0x04
    IEC_LIT_BASE16,        // 0x05
    IEC_LIT_BOOLEAN,       // 0x06
    IEC_LIT_DURATION,      // 0x07
    IEC_LIT_DATE,          // 0x08
    IEC_LIT_TIME_OF_DAY,   // 0x09
    IEC_LIT_DATE_AND_TIME, // 0x0a
};

const char *IEC_TYPES_STR[] = {
    "NULL",    // 0
    "BOOL",    //
    "SINT",    //
    "USINT",   //
    "BYTE",    //
    "INT",     //
    "UINT",    //
    "WORD",    //
    "DINT",    //
    "UDINT",   //
    "DWORD",   //
#ifdef ALLOW_64BITS
    "LINT",    //
    "ULINT",   //
    "LWORD",   //
#else
    "NULL",    //
    "NULL",    //
    "NULL",    //
#endif
    "REAL",    //
    "LREAL",   //
    "TIME",    //
    "DATE",    //
    "TOD",     //
#ifdef ALLOW_64BITS
    "DT",      //
#else
    "NULL",    //
#endif
    "CHAR",    //
    "WCHAR",   //
    "STRING",  //
    "WSTRING", //
#ifdef ALLOW_64BITS
    "POINTER", //
#else
    "NDEF",    //
#endif
    "TABLE",   //
    "USER",    //
    "NULL",    //
    "NULL",    //
    "NULL",    //
    "NULL",    //
    "NULL",    // 31
};

char* identify_literal(char *str, uint8_t *lit, uint8_t *typed) {

}

#endif /* IEC_LITERALS_H_ */
