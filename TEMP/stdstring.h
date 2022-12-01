/// # String library
/// C string utils library (STB style, header-only). Features:
/// - String expression evaluator (`streval`)
/// - String formatters (to heap buffers) (`strcpyf*`, `strcatf*`)
/// - String formatters (to temporary buffers) (`strf*`)
/// - String fuzzy search (`strscore`, `strfuzzy`)
/// - String regular expression (`strregex [c?^$*]`)
/// - String 64-bit hashing (both compile-time and runtime) (`strhash`)
/// - String interning (quarks) (`strput`, `strget`)
/// - String matching (`strsub`, `strfindl`, `strfindr`, `strbegin`, `strend`, `strmatch`, `streq`, `streqi`)
/// - String splitting (with and without allocations) (`strsplit`, `strchop`, `strjoin`)
/// - String options parsing (`stropt`, `stropti`, `stroptf`)
/// - String trim utils (`strdel`, `strtrimws`, `strtrimblf/bff`, `strtrimrlfe/ffe`)
/// - String transform utils (`strrepl`, `strremap`, `strlower`, `strupper`, `strrev`)
/// - String normalization utils (`strnorm`)
/// - String conversion utils (`strint`, `strhuman`, `strrobot`)
/// - String unicode utils (`strutf8`, `strutf32`, `strwiden`, `strshorten`)
/// - [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).
/// 
/// # Homepage
/// - https://github.com/r-lyeh/stdstring.h
///
/// # Changelog
/// - 2018.1 (v1.0.4): Fix API() macro; Add new transform utils; Rename a few functions.
/// - 2018.1 (v1.0.3): Add `strnorm()`, `strjoin()`. Fix `strcpyf()`.
/// - 2018.1 (v1.0.2): Add `stropt*()` options parser.
/// - 2018.1 (v1.0.1): Fix wrong version of strcatf() in first commit. Cosmetics.
/// - 2018.1 (v1.0.0): Initial release.
///
/// # Credits
/// - Using Rob Pike's regular expression (apparently public domain).
/// - Using Sam Hocevar's preprocessor trick (apparently public domain).
/// - Using Bob Stout's transform utils (public domain).
/// - Using Sean Barrett and Jeff Roberts' string formatters (unlicensed).
/// - Using Werner Stoop's expression evaluator (unlicensed).
/// - Using Dimitri Diakopoulos' & Sean Barrett's unicode stuff (unlicensed).
///
/// # License
/// - rlyeh, unlicensed (~public domain).
/// 

// API ------------------------------------------------------------------------

#ifdef API

API(string,

/// # API
/// ## String expression evaluator
/// - Evaluates a mathematical expression. Returns number value, or NaN if error.
/// - Note: To check for NaN use `isnan(ret)` or `bool error = (ret != ret);`
///<C
ABI      double        streval(const char *expression);

/// ## String fuzzy completion
/// - Compares two strings. Returns string matching score (higher is better).
/// - Fuzzy search a word into a list of given words. Returns best match or empty string (if none).
///<C
ABI      int           strscore(const char *string1, const char *string2);
ABI      const char *  strfuzzy(const char *string, int num, const char *words[]);

/// ## String regular expression
/// - Regular expression matching. returns non-zero if found.
///   - `c` matches any literal character c.
///   - `?` matches any single character.
///   - `^` matches the beginning of the input string.
///   - `$` matches the end of the input string.
///   - `*` matches zero or more occurrences of the previous character.
/// - Return true if string matches wildcard pattern expression (?*).
///<C
ABI      int           strregex(const char *string, const char *regex);
ABI      bool          strmatch(const char *string, const char *substring);

/// ## String hashing
/// - Runtime string hash. Returns 64-bit hash of given string.
/// - Compile-time string hash macro. Returns 64-bit hash of given string.
/// - Note: Macro requires code optimizations enabled (`-O3` for gcc, `/O2` for MSVC).
///<C
ABI      uint64_t      strhash(const char *string);
ABI      uint64_t      STRHASH(const char *string);

/// ## String interning dictionary (quarks)
/// - Insert string into dictionary (if not exists). Returns quark ID, or 0 if empty string.
/// - Retrieve previously interned string. ID#0 returns empty string always.
///<C
ABI      int           strput(const char *string);
ABI      const char *  strget(int quark);

/// ## String matching
/// - Extract substring from position. Negative positions are relative to end of string.
/// - Search substring from beginning (left). Returns end-of-string if not found.
/// - Search substring from end (right). Returns end-of-string if not found.
/// - Return true if string starts with substring.
/// - Return true if string ends with substring.
/// - Return true if strings are equal.
/// - Return true if strings are equal (case insensitive).
///<C
ABI      const char*   strsub  (const char *string, int position);
ABI      const char*   strfindl(const char *string, const char *substring);
ABI      const char*   strfindr(const char *string, const char *substring);
ABI      bool          strbegin(const char *string, const char *substring);
ABI      bool          strend  (const char *string, const char *substring);
ABI      bool          streq   (const char *string, const char *substring);
ABI      bool          streqi  (const char *string, const char *substring);

/// ## String normalization
/// - Normalize resource identificator. Normalized uris have deterministic string hashes.
///<C
ABI TEMP char *        strnorm (const char *uri);

/// ## String conversion utils
/// - Convert a string to integer.
/// - Convert number to human readable string (`12000000 -> 12M`)
/// - Convert human readable string to number (`12M -> 12000000`)
///<C
ABI      int64_t       strint  (const char *string);
ABI TEMP char*         strhuman(uint64_t number);
ABI      uint64_t      strrobot(const char *string);

/// ## String options parsing
/// - Parse argc/argv looking for comma-separated values. Returns matching string or `defaults`.
/// - Parse argc/argv looking for comma-separated values. Returns matching integer or `defaults`.
/// - Parse argc/argv looking for comma-separated values. Returns matching floating or `defaults`.
///<C
ABI      const char *  stropt (const char *defaults, const char *options_csv);
ABI      int64_t       stropti(int64_t defaults, const char *options_csv);
ABI      double        stroptf(double defaults, const char *options_csv);

/// ## String format (temporary buffers)
/// - Format a C-style formatted string. Returns temporary buffer (do not `free()`).
/// - Format a C-style formatted valist. Returns temporary buffer (do not `free()`).
/// - Note: 16 buffers are handled internally so that nested calls are safe within reasonable limits.
///<C
ABI TEMP char *        strf (const char *format, ...);
ABI TEMP char *        strfv(const char *format, va_list list);

/// ## String format (heap buffers)
/// - Assign a C-style formatted string. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Assign a C-style formatted valist. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Concat a C-style formatted string. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Concat a C-style formatted valist. Reallocates input buffer (will create buffer if `str` is NULL).
///<C
ABI HEAP char *        strcpyf (INOUT char **string, const char *format, ...);
ABI HEAP char *        strcpyfv(INOUT char **string, const char *format, va_list list);
ABI HEAP char *        strcatf (INOUT char **string, const char *format, ...);
ABI HEAP char *        strcatfv(INOUT char **string, const char *format, va_list list);

/// ## String splitting
/// - Check delimiters and split string into tokens. Function never allocates.
/// - Check delimiters and split string into tokens. Returns null-terminated list.
/// - Join tokens into a string.
///<C
ABI      int           strchop (const char *string, const char *delimiters, int avail, const char *tokens[]);
ABI HEAP char**        strsplit(const char *string, const char *delimiters);
ABI HEAP char*         strjoin (INOUT char **out, char *tokens[], const char *separator);

/// ## String trimming
/// - Delete substring from a string.
/// - Trim characters from begin of string to first-find (`b-str-str-e` to `x-xxx-str-e`).
/// - Trim characters from begin of string to last-find (`b-str-str-e` to `x-xxx-xxx-e`).
/// - Trim characters from first-find to end of string (`b-str-str-e` to `b-xxx-xxx-x`).
/// - Trim characters from last-find to end of string (`b-str-str-e` to `b-str-xxx-x`).
/// - Trim leading, trailing and excess embedded whitespaces.
///<C
ABI      char*         strdel    (char *string, const char *substring);
ABI      char*         strtrimbff(char *string, const char *substring);
ABI      char*         strtrimblf(char *string, const char *substring);
ABI      char*         strtrimffe(char *string, const char *substring);
ABI      char*         strtrimlfe(char *string, const char *substring);
ABI      char*         strtrimws (char *string);

/// ## String transforms
/// - Replace a substring in a string.
/// - Remap specific characters in a string from a given set to another one. Length of both sets must be identical.
/// - Convert a string to lowercase (ANSI only, not utf8/locale aware!).
/// - Convert a string to uppercase (ANSI only, not utf8/locale aware!).
/// - Reverse a string in-place.
///<C
ABI HEAP char*         strrepl   (INOUT char **string, const char *target, const char *replace);
ABI      char*         strremap  (INOUT char *string, const char srcs[], const char dsts[]);
ABI      char*         strlower  (char *string);
ABI      char*         strupper  (char *string);
ABI      char*         strrev    (char *string);

/// ## String unicode utils
/// - Extract 32bit codepoint from string. Also advances input string to next codepoint.
/// - Convert 32bit codepoint to utf8 string.
/// - Convert utf8 to utf16 string.
/// - Convert utf16 to utf8 string.
///<C
ABI      uint32_t      strutf32(INOUT const char **utf8);
ABI TEMP char *        strutf8(uint32_t codepoint);
ABI TEMP wchar_t*      strwiden(const char *utf8);
ABI TEMP char*         strshorten(const wchar_t *utf16);
///>

);

#endif

// HEADER ---------------------------------------------------------------------

#ifndef STDSTRING_H
#define STDSTRING_H

#define STDSTRING_IMPLEMENTATION

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>

#ifndef AVA
// symbol visiblity, abi and linkage
//#ifdef __cplusplus
//   #define ABI extern "C"
//   #else
//#define ABI
//#endif
//#define API(name,...)   __VA_ARGS__
// code annonations
#define HEAP           /* heap pointer. must free() after use */
#define TEMP           /* temporary stack pointer. do not free() after use */
#define INOUT          /* both input and output argument */
#define OPTIONAL       /* optional argument */
// mem wrappers
#define REALLOC(p, sz) realloc((p), (sz))
#define MALLOC(sz)     REALLOC(0, (sz))
#define CALLOC(n, m)   memset(MALLOC((n)*(m)), 0, (n)*(m))
#define FREE(p)        REALLOC(p, 0)
#define STRDUP(s)      strdup(s)
// compiler stuff
#ifdef _MSC_VER
   #define builtin(x)     __declspec(x)
   #else
#define builtin(x)     __##x
#endif
// raii perf/profiler
#define $
#endif

#include __FILE__

#define STRHASH(str)                  STRHASH64(0,131ull,str,0)
#define STRHASH64(hsh,mul,str,idx)    STRHASH16(STRHASH16(STRHASH16(STRHASH16(hsh,mul,str,idx+48),mul,str,idx+32),mul,str,idx+16),mul,str,idx)
#define STRHASH16(hsh,mul,str,idx)    STRHASH04(STRHASH04(STRHASH04(STRHASH04(hsh,mul,str,idx+12),mul,str,idx+ 8),mul,str,idx+ 4),mul,str,idx)
#define STRHASH04(hsh,mul,str,idx)    STRHASH01(STRHASH01(STRHASH01(STRHASH01(hsh,mul,str,idx+ 3),mul,str,idx+ 2),mul,str,idx+ 1),mul,str,idx)
#define STRHASH01(hsh,mul,str,idx)    ((STRHASHCHR(str,idx) ^ hsh) * mul)
#define STRHASHCHR(str,idx)           ((unsigned)str[(idx)<STRHASHLEN(str)?STRHASHLEN(str)-1-(idx):STRHASHLEN(str)])
#define STRHASHLEN(str)               (sizeof(str)-1)

// IMPLEMENTATION -------------------------------------------------------------

#ifdef STDSTRING_IMPLEMENTATION

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// String symbol that holds whole api declarations
// Useful for function-foreign interface (FFI) and related script bindings.

//ABI const char* const strapi() {
//#undef  API
//#define API(name, ...) #__VA_ARGS__
//    return 0;
//#include __FILE__
//    ;
//}

#ifdef APIDEMO
#include <stdio.h>
int main() {
    puts(strapi());
}
#endif

#define STB_SPRINTF_DECORATE(name) str##name
#define STB_SPRINTF_IMPLEMENTATION

// stb_sprintf - v1.03 - public domain snprintf() implementation
// originally by Jeff Roberts / RAD Game Tools, 2015/10/20
// http://github.com/nothings/stb
//
// allowed types:  sc uidBboXx p AaGgEef n
// lengths      :  h ll j z t I64 I32 I
//
// Contributors:
//    Fabian "ryg" Giesen (reformatting)
//
// Contributors (bugfixes):
//    github:d26435
//    github:trex78
//    Jari Komppa (SI suffixes)
//
// LICENSE:
//
//   See end of file for license information.

#ifndef STB_SPRINTF_H_INCLUDE
#define STB_SPRINTF_H_INCLUDE

/*
 Single file sprintf replacement.

 Originally written by Jeff Roberts at RAD Game Tools - 2015/10/20.
 Hereby placed in public domain.

 This is a full sprintf replacement that supports everything that
 the C runtime sprintfs support, including float/double, 64-bit integers,
 hex floats, field parameters (%*.*d stuff), length reads backs, etc.

 Why would you need this if sprintf already exists?  Well, first off,
 it's *much* faster (see below). It's also much smaller than the CRT
 versions code-space-wise. We've also added some simple improvements
 that are super handy (commas in thousands, callbacks at buffer full,
 for example). Finally, the format strings for MSVC and GCC differ
 for 64-bit integers (among other small things), so this lets you use
 the same format strings in cross platform code.

 It uses the standard single file trick of being both the header file
 and the source itself. If you just include it normally, you just get
 the header file function definitions. To get the code, you include
 it from a C or C++ file and define STB_SPRINTF_IMPLEMENTATION first.

 It only uses va_args macros from the C runtime to do it's work. It
 does cast doubles to S64s and shifts and divides U64s, which does
 drag in CRT code on most platforms.

 It compiles to roughly 8K with float support, and 4K without.
 As a comparison, when using MSVC static libs, calling sprintf drags
 in 16K.

 API:
 ====
 int stbsp_sprintf( char * buf, char const * fmt, ... )
 int stbsp_snprintf( char * buf, int count, char const * fmt, ... )
 Convert an arg list into a buffer.  stbsp_snprintf always returns
 a zero-terminated string (unlike regular snprintf).

 int stbsp_vsprintf( char * buf, char const * fmt, va_list va )
 int stbsp_vsnprintf( char * buf, int count, char const * fmt, va_list va )
 Convert a va_list arg list into a buffer.  stbsp_vsnprintf always returns
 a zero-terminated string (unlike regular snprintf).

 int stbsp_vsprintfcb( STBSP_SPRINTFCB * callback, void * user, char * buf, char const * fmt, va_list va )
 typedef char * STBSP_SPRINTFCB( char const * buf, void * user, int len );
 Convert into a buffer, calling back every STB_SPRINTF_MIN chars.
 Your callback can then copy the chars out, print them or whatever.
 This function is actually the workhorse for everything else.
 The buffer you pass in must hold at least STB_SPRINTF_MIN characters.
 // you return the next buffer to use or 0 to stop converting

 void stbsp_set_separators( char comma, char period )
 Set the comma and period characters to use.

 FLOATS/DOUBLES:
 ===============
 This code uses a internal float->ascii conversion method that uses
 doubles with error correction (double-doubles, for ~105 bits of
 precision).  This conversion is round-trip perfect - that is, an atof
 of the values output here will give you the bit-exact double back.

 One difference is that our insignificant digits will be different than
 with MSVC or GCC (but they don't match each other either).  We also
 don't attempt to find the minimum length matching float (pre-MSVC15
 doesn't either).

 If you don't need float or doubles at all, define STB_SPRINTF_NOFLOAT
 and you'll save 4K of code space.

 64-BIT INTS:
 ============
 This library also supports 64-bit integers and you can use MSVC style or
 GCC style indicators (%I64d or %lld).  It supports the C99 specifiers
 for size_t and ptr_diff_t (%jd %zd) as well.

 EXTRAS:
 =======
 Like some GCCs, for integers and floats, you can use a ' (single quote)
 specifier and commas will be inserted on the thousands: "%'d" on 12345
 would print 12,345.

 For integers and floats, you can use a "$" specifier and the number
 will be converted to float and then divided to get kilo, mega, giga or
 tera and then printed, so "%$d" 1000 is "1.0 k", "%$.2d" 2536000 is
 "2.53 M", etc. For byte values, use two $:s, like "%$$d" to turn
 2536000 to "2.42 Mi". If you prefer JEDEC suffixes to SI ones, use three
 $:s: "%$$$d" -> "2.42 M". To remove the space between the number and the
 suffix, add "_" specifier: "%_$d" -> "2.53M".

 In addition to octal and hexadecimal conversions, you can print
 integers in binary: "%b" for 256 would print 100.

 PERFORMANCE vs MSVC 2008 32-/64-bit (GCC is even slower than MSVC):
 ===================================================================
 "%d" across all 32-bit ints (4.8x/4.0x faster than 32-/64-bit MSVC)
 "%24d" across all 32-bit ints (4.5x/4.2x faster)
 "%x" across all 32-bit ints (4.5x/3.8x faster)
 "%08x" across all 32-bit ints (4.3x/3.8x faster)
 "%f" across e-10 to e+10 floats (7.3x/6.0x faster)
 "%e" across e-10 to e+10 floats (8.1x/6.0x faster)
 "%g" across e-10 to e+10 floats (10.0x/7.1x faster)
 "%f" for values near e-300 (7.9x/6.5x faster)
 "%f" for values near e+300 (10.0x/9.1x faster)
 "%e" for values near e-300 (10.1x/7.0x faster)
 "%e" for values near e+300 (9.2x/6.0x faster)
 "%.320f" for values near e-300 (12.6x/11.2x faster)
 "%a" for random values (8.6x/4.3x faster)
 "%I64d" for 64-bits with 32-bit values (4.8x/3.4x faster)
 "%I64d" for 64-bits > 32-bit values (4.9x/5.5x faster)
 "%s%s%s" for 64 char strings (7.1x/7.3x faster)
 "...512 char string..." ( 35.0x/32.5x faster!)
 */

#if defined(__has_feature)
   #if __has_feature(address_sanitizer)
      #define STBI__ASAN __attribute__((no_sanitize("address")))
   #endif
#endif
#ifndef STBI__ASAN
#define STBI__ASAN
#endif

#ifdef STB_SPRINTF_STATIC
#define STBSP__PUBLICDEC static
#define STBSP__PUBLICDEF static STBI__ASAN
#else
#ifdef __cplusplus
#define STBSP__PUBLICDEC extern "C"
#define STBSP__PUBLICDEF extern "C" STBI__ASAN
#else
#define STBSP__PUBLICDEC extern
#define STBSP__PUBLICDEF STBI__ASAN
#endif
#endif

#include <stdarg.h> // for va_list()

#ifndef STB_SPRINTF_MIN
#define STB_SPRINTF_MIN 512 // how many characters per callback
#endif
typedef char* STBSP_SPRINTFCB(char *buf, void *user, int len);

#ifndef STB_SPRINTF_DECORATE
#define STB_SPRINTF_DECORATE(name) stbsp_##name // define this before including if you want to change the names
#endif

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintf)(char *buf, char const *fmt, va_list va);
STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsnprintf)(char *buf, int count, char const *fmt, va_list va);
STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(sprintf)(char *buf, char const *fmt, ...);
STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(snprintf)(char *buf, int count, char const *fmt, ...);

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintfcb)(STBSP_SPRINTFCB *callback, void *user, char *buf, char const *fmt, va_list va);
STBSP__PUBLICDEF void STB_SPRINTF_DECORATE(set_separators)(char comma, char period);

#endif // STB_SPRINTF_H_INCLUDE

#ifdef STB_SPRINTF_IMPLEMENTATION

#include <stdlib.h> // for va_arg()

#define stbsp__uint32 unsigned int
#define stbsp__int32 signed int

#ifdef _MSC_VER
#define stbsp__uint64 unsigned __int64
#define stbsp__int64 signed __int64
#else
#define stbsp__uint64 unsigned long long
#define stbsp__int64 signed long long
#endif
#define stbsp__uint16 unsigned short

#ifndef stbsp__uintptr
#if defined(__ppc64__) || defined(__aarch64__) || defined(_M_X64) || defined(__x86_64__) || defined(__x86_64)
#define stbsp__uintptr stbsp__uint64
#else
#define stbsp__uintptr stbsp__uint32
#endif
#endif

#ifndef STB_SPRINTF_MSVC_MODE // used for MSVC2013 and earlier (MSVC2015 matches GCC)
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define STB_SPRINTF_MSVC_MODE
#endif
#endif

#ifdef STB_SPRINTF_NOUNALIGNED // define this before inclusion to force stbsp_sprintf to always use aligned accesses
#define STBSP__UNALIGNED(code)
#else
#define STBSP__UNALIGNED(code) code
#endif

#ifndef STB_SPRINTF_NOFLOAT
// internal float utility functions
static stbsp__int32 stbsp__real_to_str(char const **start, stbsp__uint32 *len, char *out, stbsp__int32 *decimal_pos, double value, stbsp__uint32 frac_digits);
static stbsp__int32 stbsp__real_to_parts(stbsp__int64 *bits, stbsp__int32 *expo, double value);
#define STBSP__SPECIAL 0x7000
#endif

static char stbsp__period = '.';
static char stbsp__comma = ',';
static char stbsp__digitpair[201] =
        "0001020304050607080910111213141516171819202122232425262728293031323"
        "3343536373839404142434445464748495051525354555657585960616263646566"
        "676869707172737475767778798081828384858687888990919293949596979899";

STBSP__PUBLICDEF void STB_SPRINTF_DECORATE(set_separators)(char pcomma, char pperiod) {
    stbsp__period = pperiod;
    stbsp__comma = pcomma;
}

#define STBSP__LEFTJUST 1
#define STBSP__LEADINGPLUS 2
#define STBSP__LEADINGSPACE 4
#define STBSP__LEADING_0X 8
#define STBSP__LEADINGZERO 16
#define STBSP__INTMAX 32
#define STBSP__TRIPLET_COMMA 64
#define STBSP__NEGATIVE 128
#define STBSP__METRIC_SUFFIX 256
#define STBSP__HALFWIDTH 512
#define STBSP__METRIC_NOSPACE 1024
#define STBSP__METRIC_1024 2048
#define STBSP__METRIC_JEDEC 4096

static void stbsp__lead_sign(stbsp__uint32 fl, char *sign) {
    sign[0] = 0;
    if (fl & STBSP__NEGATIVE) {
        sign[0] = 1;
        sign[1] = '-';
    } else if (fl & STBSP__LEADINGSPACE) {
        sign[0] = 1;
        sign[1] = ' ';
    } else if (fl & STBSP__LEADINGPLUS) {
        sign[0] = 1;
        sign[1] = '+';
    }
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintfcb)(STBSP_SPRINTFCB *callback, void *user, char *buf, char const *fmt, va_list va) {
    static char hex[] = "0123456789abcdefxp";
    static char hexu[] = "0123456789ABCDEFXP";
    char *bf;
    char const *f;
    int tlen = 0;

    bf = buf;
    f = fmt;
    for (;;) {
        stbsp__int32 fw, pr, tz;
        stbsp__uint32 fl;

        // macros for the callback buffer stuff
#define stbsp__chk_cb_bufL(bytes)                        \
         {                                                     \
            int len = (int)(bf - buf);                         \
            if ((len + (bytes)) >= STB_SPRINTF_MIN) {          \
               tlen += len;                                    \
               if (0 == (bf = buf = callback(buf, user, len))) \
                  goto done;                                   \
            }                                                  \
         }
#define stbsp__chk_cb_buf(bytes)    \
         {                                \
            if (callback) {               \
               stbsp__chk_cb_bufL(bytes); \
            }                             \
         }
#define stbsp__flush_cb()                      \
         {                                           \
            stbsp__chk_cb_bufL(STB_SPRINTF_MIN - 1); \
         } // flush if there is even one byte in the buffer
#define stbsp__cb_buf_clamp(cl, v)                \
         cl = v;                                        \
         if (callback) {                                \
            int lg = STB_SPRINTF_MIN - (int)(bf - buf); \
            if (cl > lg)                                \
               cl = lg;                                 \
         }

        // fast copy everything up to the next % (or end of string)
        for (;;) {
            while (((stbsp__uintptr) f) & 3) {
                schk1:
                if (f[0] == '%')
                    goto scandd;
                schk2:
                if (f[0] == 0)
                    goto endfmt;
                stbsp__chk_cb_buf(1);
                *bf++ = f[0];
                ++f;
            }
            for (;;) {
                // Check if the next 4 bytes contain %(0x25) or end of string.
                // Using the 'hasless' trick:
                // https://graphics.stanford.edu/~seander/bithacks.html#HasLessInWord
                stbsp__uint32 v, c;
                v = *(stbsp__uint32*) f;
                c = (~v) & 0x80808080;
                if (((v ^ 0x25252525) - 0x01010101) & c)
                    goto schk1;
                if ((v - 0x01010101) & c)
                    goto schk2;
                if (callback)
                    if ((STB_SPRINTF_MIN - (int) (bf - buf)) < 4)
                        goto schk1;
                *(stbsp__uint32*) bf = v;
                bf += 4;
                f += 4;
            }
        }
        scandd:

        ++f;

        // ok, we have a percent, read the modifiers first
        fw = 0;
        pr = -1;
        fl = 0;
        tz = 0;

        // flags
        for (;;) {
            switch (f[0]) {
                // if we have left justify
                case '-':
                    fl |= STBSP__LEFTJUST;
                    ++f;
                    continue;
                    // if we have leading plus
                case '+':
                    fl |= STBSP__LEADINGPLUS;
                    ++f;
                    continue;
                    // if we have leading space
                case ' ':
                    fl |= STBSP__LEADINGSPACE;
                    ++f;
                    continue;
                    // if we have leading 0x
                case '#':
                    fl |= STBSP__LEADING_0X;
                    ++f;
                    continue;
                    // if we have thousand commas
                case '\'':
                    fl |= STBSP__TRIPLET_COMMA;
                    ++f;
                    continue;
                    // if we have kilo marker (none->kilo->kibi->jedec)
                case '$':
                    if (fl & STBSP__METRIC_SUFFIX) {
                        if (fl & STBSP__METRIC_1024) {
                            fl |= STBSP__METRIC_JEDEC;
                        } else {
                            fl |= STBSP__METRIC_1024;
                        }
                    } else {
                        fl |= STBSP__METRIC_SUFFIX;
                    }
                    ++f;
                    continue;
                    // if we don't want space between metric suffix and number
                case '_':
                    fl |= STBSP__METRIC_NOSPACE;
                    ++f;
                    continue;
                    // if we have leading zero
                case '0':
                    fl |= STBSP__LEADINGZERO;
                    ++f;
                    goto flags_done;
                default:
                    goto flags_done;
            }
        }
        flags_done:

        // get the field width
        if (f[0] == '*') {
            fw = va_arg(va, stbsp__uint32);
            ++f;
        } else {
            while ((f[0] >= '0') && (f[0] <= '9')) {
                fw = fw * 10 + f[0] - '0';
                f++;
            }
        }
        // get the precision
        if (f[0] == '.') {
            ++f;
            if (f[0] == '*') {
                pr = va_arg(va, stbsp__uint32);
                ++f;
            } else {
                pr = 0;
                while ((f[0] >= '0') && (f[0] <= '9')) {
                    pr = pr * 10 + f[0] - '0';
                    f++;
                }
            }
        }

        // handle integer size overrides
        switch (f[0]) {
            // are we halfwidth?
            case 'h':
                fl |= STBSP__HALFWIDTH;
                ++f;
                break;
                // are we 64-bit (unix style)
            case 'l':
                ++f;
                if (f[0] == 'l') {
                    fl |= STBSP__INTMAX;
                    ++f;
                }
                break;
                // are we 64-bit on intmax? (c99)
            case 'j':
                fl |= STBSP__INTMAX;
                ++f;
                break;
                // are we 64-bit on size_t or ptrdiff_t? (c99)
            case 'z':
            case 't':
                fl |= ((sizeof(char*) == 8) ? STBSP__INTMAX : 0);
                ++f;
                break;
                // are we 64-bit (msft style)
            case 'I':
                if ((f[1] == '6') && (f[2] == '4')) {
                    fl |= STBSP__INTMAX;
                    f += 3;
                } else if ((f[1] == '3') && (f[2] == '2')) {
                    f += 3;
                } else {
                    fl |= ((sizeof(void*) == 8) ? STBSP__INTMAX : 0);
                    ++f;
                }
                break;
            default:
                break;
        }

        // handle each replacement
        switch (f[0]) {
#define STBSP__NUMSZ 512 // big enough for e308 (with commas) or e-307
            char num[STBSP__NUMSZ];
            char lead[8];
            char tail[8];
            char *s;
            char const *h;
            stbsp__uint32 l, n, cs;
            stbsp__uint64 n64;
#ifndef STB_SPRINTF_NOFLOAT
            double fv;
#endif
            stbsp__int32 dp;
            char const *sn;

        case 's':
            // get the string
            s = va_arg(va, char*);
            if (s == 0)
                s = (char*) "null";
            // get the length
            sn = s;
            for (;;) {
                if ((((stbsp__uintptr) sn) & 3) == 0)
                    break;
                lchk:
                if (sn[0] == 0)
                    goto ld;
                ++sn;
            }
            n = 0xffffffff;
            if (pr >= 0) {
                n = (stbsp__uint32) (sn - s);
                if (n >= (stbsp__uint32) pr)
                    goto ld;
                n = ((stbsp__uint32) (pr - n)) >> 2;
            }
            while (n) {
                stbsp__uint32 v = *(stbsp__uint32*) sn;
                if ((v - 0x01010101) & (~v) & 0x80808080UL)
                    goto lchk;
                sn += 4;
                --n;
            }
            goto lchk;
            ld:

            l = (stbsp__uint32) (sn - s);
            // clamp to precision
            if (l > (stbsp__uint32) pr)
                l = pr;
            lead[0] = 0;
            tail[0] = 0;
            pr = 0;
            dp = 0;
            cs = 0;
            // copy the string in
            goto scopy;

        case 'c': // char
            // get the character
            s = num + STBSP__NUMSZ - 1;
            *s = (char) va_arg(va, int);
            l = 1;
            lead[0] = 0;
            tail[0] = 0;
            pr = 0;
            dp = 0;
            cs = 0;
            goto scopy;

        case 'n': // weird write-bytes specifier
        {
            int *d = va_arg(va, int*);
            *d = tlen + (int) (bf - buf);
        }
            break;

#ifdef STB_SPRINTF_NOFLOAT
      case 'A':              // float
      case 'a':              // hex float
      case 'G':              // float
      case 'g':              // float
      case 'E':              // float
      case 'e':              // float
      case 'f':              // float
         va_arg(va, double); // eat it
         s = (char *)"No float";
         l = 8;
         lead[0] = 0;
         tail[0] = 0;
         pr = 0;
         dp = 0;
         cs = 0;
         goto scopy;
#else
        case 'A': // hex float
        case 'a': // hex float
            h = (f[0] == 'A') ? hexu : hex;
            fv = va_arg(va, double);
            if (pr == -1)
                pr = 6; // default is 6
            // read the double into a string
            if (stbsp__real_to_parts((stbsp__int64*) &n64, &dp, fv))
                fl |= STBSP__NEGATIVE;

            s = num + 64;

            stbsp__lead_sign(fl, lead);

            if (dp == -1023)
                dp = (n64) ? -1022 : 0;
            else
                n64 |= (((stbsp__uint64) 1) << 52);
            n64 <<= (64 - 56);
            if (pr < 15)
                n64 += ((((stbsp__uint64) 8) << 56) >> (pr * 4));
// add leading chars

#ifdef STB_SPRINTF_MSVC_MODE
         *s++ = '0';
         *s++ = 'x';
#else
            lead[1 + lead[0]] = '0';
            lead[2 + lead[0]] = 'x';
            lead[0] += 2;
#endif
            *s++ = h[(n64 >> 60) & 15];
            n64 <<= 4;
            if (pr)
                *s++ = stbsp__period;
            sn = s;

            // print the bits
            n = pr;
            if (n > 13)
                n = 13;
            if (pr > (stbsp__int32) n)
                tz = pr - n;
            pr = 0;
            while (n--) {
                *s++ = h[(n64 >> 60) & 15];
                n64 <<= 4;
            }

            // print the expo
            tail[1] = h[17];
            if (dp < 0) {
                tail[2] = '-';
                dp = -dp;
            } else
                tail[2] = '+';
            n = (dp >= 1000) ? 6 : ((dp >= 100) ? 5 : ((dp >= 10) ? 4 : 3));
            tail[0] = (char) n;
            for (;;) {
                tail[n] = '0' + dp % 10;
                if (n <= 3)
                    break;
                --n;
                dp /= 10;
            }

            dp = (int) (s - sn);
            l = (int) (s - (num + 64));
            s = num + 64;
            cs = 1 + (3 << 24);
            goto scopy;

        case 'G': // float
        case 'g': // float
            h = (f[0] == 'G') ? hexu : hex;
            fv = va_arg(va, double);
            if (pr == -1)
                pr = 6;
            else if (pr == 0)
                pr = 1; // default is 6
            // read the double into a string
            if (stbsp__real_to_str(&sn, &l, num, &dp, fv, (pr - 1) | 0x80000000))
                fl |= STBSP__NEGATIVE;

            // clamp the precision and delete extra zeros after clamp
            n = pr;
            if (l > (stbsp__uint32) pr)
                l = pr;
            while ((l > 1) && (pr) && (sn[l - 1] == '0')) {
                --pr;
                --l;
            }

            // should we use %e
            if ((dp <= -4) || (dp > (stbsp__int32) n)) {
                if (pr > (stbsp__int32) l)
                    pr = l - 1;
                else if (pr)
                    --pr; // when using %e, there is one digit before the decimal
                goto doexpfromg;
            }
            // this is the insane action to get the pr to match %g sematics for %f
            if (dp > 0) {
                pr = (dp < (stbsp__int32) l) ? l - dp : 0;
            } else {
                pr = -dp + ((pr > (stbsp__int32) l) ? l : pr);
            }
            goto dofloatfromg;

        case 'E': // float
        case 'e': // float
            h = (f[0] == 'E') ? hexu : hex;
            fv = va_arg(va, double);
            if (pr == -1)
                pr = 6; // default is 6
            // read the double into a string
            if (stbsp__real_to_str(&sn, &l, num, &dp, fv, pr | 0x80000000))
                fl |= STBSP__NEGATIVE;
            doexpfromg:
            tail[0] = 0;
            stbsp__lead_sign(fl, lead);
            if (dp == STBSP__SPECIAL) {
                s = (char*) sn;
                cs = 0;
                pr = 0;
                goto scopy;
            }
            s = num + 64;
            // handle leading chars
            *s++ = sn[0];

            if (pr)
                *s++ = stbsp__period;

            // handle after decimal
            if ((l - 1) > (stbsp__uint32) pr)
                l = pr + 1;
            for (n = 1; n < l; n++)
                *s++ = sn[n];
            // trailing zeros
            tz = pr - (l - 1);
            pr = 0;
            // dump expo
            tail[1] = h[0xe];
            dp -= 1;
            if (dp < 0) {
                tail[2] = '-';
                dp = -dp;
            } else
                tail[2] = '+';
#ifdef STB_SPRINTF_MSVC_MODE
         n = 5;
#else
            n = (dp >= 100) ? 5 : 4;
#endif
            tail[0] = (char) n;
            for (;;) {
                tail[n] = '0' + dp % 10;
                if (n <= 3)
                    break;
                --n;
                dp /= 10;
            }
            cs = 1 + (3 << 24); // how many tens
            goto flt_lead;

        case 'f': // float
            fv = va_arg(va, double);
            doafloat:
            // do kilos
            if (fl & STBSP__METRIC_SUFFIX) {
                double divisor;
                divisor = 1000.0f;
                if (fl & STBSP__METRIC_1024)
                    divisor = 1024.0;
                while (fl < 0x4000000) {
                    if ((fv < divisor) && (fv > -divisor))
                        break;
                    fv /= divisor;
                    fl += 0x1000000;
                }
            }
            if (pr == -1)
                pr = 6; // default is 6
            // read the double into a string
            if (stbsp__real_to_str(&sn, &l, num, &dp, fv, pr))
                fl |= STBSP__NEGATIVE;
            dofloatfromg:
            tail[0] = 0;
            stbsp__lead_sign(fl, lead);
            if (dp == STBSP__SPECIAL) {
                s = (char*) sn;
                cs = 0;
                pr = 0;
                goto scopy;
            }
            s = num + 64;

            // handle the three decimal varieties
            if (dp <= 0) {
                stbsp__int32 i;
                // handle 0.000*000xxxx
                *s++ = '0';
                if (pr)
                    *s++ = stbsp__period;
                n = -dp;
                if ((stbsp__int32) n > pr)
                    n = pr;
                i = n;
                while (i) {
                    if ((((stbsp__uintptr) s) & 3) == 0)
                        break;
                    *s++ = '0';
                    --i;
                }
                while (i >= 4) {
                    *(stbsp__uint32*) s = 0x30303030;
                    s += 4;
                    i -= 4;
                }
                while (i) {
                    *s++ = '0';
                    --i;
                }
                if ((stbsp__int32) (l + n) > pr)
                    l = pr - n;
                i = l;
                while (i) {
                    *s++ = *sn++;
                    --i;
                }
                tz = pr - (n + l);
                cs = 1 + (3 << 24); // how many tens did we write (for commas below)
            } else {
                cs = (fl & STBSP__TRIPLET_COMMA) ? ((600 - (stbsp__uint32) dp) % 3) : 0;
                if ((stbsp__uint32) dp >= l) {
                    // handle xxxx000*000.0
                    n = 0;
                    for (;;) {
                        if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                            cs = 0;
                            *s++ = stbsp__comma;
                        } else {
                            *s++ = sn[n];
                            ++n;
                            if (n >= l)
                                break;
                        }
                    }
                    if (n < (stbsp__uint32) dp) {
                        n = dp - n;
                        if ((fl & STBSP__TRIPLET_COMMA) == 0) {
                            while (n) {
                                if ((((stbsp__uintptr) s) & 3) == 0)
                                    break;
                                *s++ = '0';
                                --n;
                            }
                            while (n >= 4) {
                                *(stbsp__uint32*) s = 0x30303030;
                                s += 4;
                                n -= 4;
                            }
                        }
                        while (n) {
                            if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                                cs = 0;
                                *s++ = stbsp__comma;
                            } else {
                                *s++ = '0';
                                --n;
                            }
                        }
                    }
                    cs = (int) (s - (num + 64)) + (3 << 24); // cs is how many tens
                    if (pr) {
                        *s++ = stbsp__period;
                        tz = pr;
                    }
                } else {
                    // handle xxxxx.xxxx000*000
                    n = 0;
                    for (;;) {
                        if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                            cs = 0;
                            *s++ = stbsp__comma;
                        } else {
                            *s++ = sn[n];
                            ++n;
                            if (n >= (stbsp__uint32) dp)
                                break;
                        }
                    }
                    cs = (int) (s - (num + 64)) + (3 << 24); // cs is how many tens
                    if (pr)
                        *s++ = stbsp__period;
                    if ((l - dp) > (stbsp__uint32) pr)
                        l = pr + dp;
                    while (n < l) {
                        *s++ = sn[n];
                        ++n;
                    }
                    tz = pr - (l - dp);
                }
            }
            pr = 0;

            // handle k,m,g,t
            if (fl & STBSP__METRIC_SUFFIX) {
                char idx;
                idx = 1;
                if (fl & STBSP__METRIC_NOSPACE)
                    idx = 0;
                tail[0] = idx;
                tail[1] = ' ';
                {
                    if (fl >> 24) { // SI kilo is 'k', JEDEC and SI kibits are 'K'.
                        if (fl & STBSP__METRIC_1024)
                            tail[idx + 1] = "_KMGT"[fl >> 24];
                        else
                            tail[idx + 1] = "_kMGT"[fl >> 24];
                        idx++;
                        // If printing kibits and not in jedec, add the 'i'.
                        if ((fl & STBSP__METRIC_1024) && !(fl & STBSP__METRIC_JEDEC)) {
                            tail[idx + 1] = 'i';
                            idx++;
                        }
                        tail[0] = idx;
                    }
                }
            }
            ;

            flt_lead:
            // get the length that we copied
            l = (stbsp__uint32) (s - (num + 64));
            s = num + 64;
            goto scopy;
#endif

        case 'B': // upper binary
        case 'b': // lower binary
            h = (f[0] == 'B') ? hexu : hex;
            lead[0] = 0;
            if (fl & STBSP__LEADING_0X) {
                lead[0] = 2;
                lead[1] = '0';
                lead[2] = h[0xb];
            }
            l = (8 << 4) | (1 << 8);
            goto radixnum;

        case 'o': // octal
            h = hexu;
            lead[0] = 0;
            if (fl & STBSP__LEADING_0X) {
                lead[0] = 1;
                lead[1] = '0';
            }
            l = (3 << 4) | (3 << 8);
            goto radixnum;

        case 'p': // pointer
            fl |= (sizeof(void*) == 8) ? STBSP__INTMAX : 0;
            pr = sizeof(void*) * 2;
            fl &= ~STBSP__LEADINGZERO; // 'p' only prints the pointer with zeros
                                       // drop through to X

        case 'X': // upper hex
        case 'x': // lower hex
            h = (f[0] == 'X') ? hexu : hex;
            l = (4 << 4) | (4 << 8);
            lead[0] = 0;
            if (fl & STBSP__LEADING_0X) {
                lead[0] = 2;
                lead[1] = '0';
                lead[2] = h[16];
            }
            radixnum:
            // get the number
            if (fl & STBSP__INTMAX)
                n64 = va_arg(va, stbsp__uint64);
            else
                n64 = va_arg(va, stbsp__uint32);

            s = num + STBSP__NUMSZ;
            dp = 0;
            // clear tail, and clear leading if value is zero
            tail[0] = 0;
            if (n64 == 0) {
                lead[0] = 0;
                if (pr == 0) {
                    l = 0;
                    cs = (((l >> 4) & 15)) << 24;
                    goto scopy;
                }
            }
            // convert to string
            for (;;) {
                *--s = h[n64 & ((1 << (l >> 8)) - 1)];
                n64 >>= (l >> 8);
                if (!((n64) || ((stbsp__int32) ((num + STBSP__NUMSZ) - s) < pr)))
                    break;
                if (fl & STBSP__TRIPLET_COMMA) {
                    ++l;
                    if ((l & 15) == ((l >> 4) & 15)) {
                        l &= ~15;
                        *--s = stbsp__comma;
                    }
                }
            }
            ;
            // get the tens and the comma pos
            cs = (stbsp__uint32) ((num + STBSP__NUMSZ) - s) + ((((l >> 4) & 15)) << 24);
            // get the length that we copied
            l = (stbsp__uint32) ((num + STBSP__NUMSZ) - s);
            // copy it
            goto scopy;

        case 'u': // unsigned
        case 'i':
        case 'd': // integer
            // get the integer and abs it
            if (fl & STBSP__INTMAX) {
                stbsp__int64 i64 = va_arg(va, stbsp__int64);
                n64 = (stbsp__uint64) i64;
                if ((f[0] != 'u') && (i64 < 0)) {
                    n64 = (stbsp__uint64) -i64;
                    fl |= STBSP__NEGATIVE;
                }
            } else {
                stbsp__int32 i = va_arg(va, stbsp__int32);
                n64 = (stbsp__uint32) i;
                if ((f[0] != 'u') && (i < 0)) {
                    n64 = (stbsp__uint32) -i;
                    fl |= STBSP__NEGATIVE;
                }
            }

#ifndef STB_SPRINTF_NOFLOAT
            if (fl & STBSP__METRIC_SUFFIX) {
                if (n64 < 1024)
                    pr = 0;
                else if (pr == -1)
                    pr = 1;
                fv = (double) (stbsp__int64) n64;
                goto doafloat;
            }
#endif

            // convert to string
            s = num + STBSP__NUMSZ;
            l = 0;

            for (;;) {
                // do in 32-bit chunks (avoid lots of 64-bit divides even with constant denominators)
                char *o = s - 8;
                if (n64 >= 100000000) {
                    n = (stbsp__uint32) (n64 % 100000000);
                    n64 /= 100000000;
                } else {
                    n = (stbsp__uint32) n64;
                    n64 = 0;
                }
                if ((fl & STBSP__TRIPLET_COMMA) == 0) {
                    while (n) {
                        s -= 2;
                        *(stbsp__uint16*) s = *(stbsp__uint16*) &stbsp__digitpair[(n % 100) * 2];
                        n /= 100;
                    }
                }
                while (n) {
                    if ((fl & STBSP__TRIPLET_COMMA) && (l++ == 3)) {
                        l = 0;
                        *--s = stbsp__comma;
                        --o;
                    } else {
                        *--s = (char) (n % 10) + '0';
                        n /= 10;
                    }
                }
                if (n64 == 0) {
                    if ((s[0] == '0') && (s != (num + STBSP__NUMSZ)))
                        ++s;
                    break;
                }
                while (s != o)
                    if ((fl & STBSP__TRIPLET_COMMA) && (l++ == 3)) {
                        l = 0;
                        *--s = stbsp__comma;
                        --o;
                    } else {
                        *--s = '0';
                    }
            }

            tail[0] = 0;
            stbsp__lead_sign(fl, lead);

            // get the length that we copied
            l = (stbsp__uint32) ((num + STBSP__NUMSZ) - s);
            if (l == 0) {
                *--s = '0';
                l = 1;
            }
            cs = l + (3 << 24);
            if (pr < 0)
                pr = 0;

            scopy:
            // get fw=leading/trailing space, pr=leading zeros
            if (pr < (stbsp__int32) l)
                pr = l;
            n = pr + lead[0] + tail[0] + tz;
            if (fw < (stbsp__int32) n)
                fw = n;
            fw -= n;
            pr -= l;

            // handle right justify and leading zeros
            if ((fl & STBSP__LEFTJUST) == 0) {
                if (fl & STBSP__LEADINGZERO) // if leading zeros, everything is in pr
                {
                    pr = (fw > pr) ? fw : pr;
                    fw = 0;
                } else {
                    fl &= ~STBSP__TRIPLET_COMMA; // if no leading zeros, then no commas
                }
            }

            // copy the spaces and/or zeros
            if (fw + pr) {
                stbsp__int32 i;
                stbsp__uint32 c;

                // copy leading spaces (or when doing %8.4d stuff)
                if ((fl & STBSP__LEFTJUST) == 0)
                    while (fw > 0) {
                        stbsp__cb_buf_clamp(i, fw);
                        fw -= i;
                        while (i) {
                            if ((((stbsp__uintptr) bf) & 3) == 0)
                                break;
                            *bf++ = ' ';
                            --i;
                        }
                        while (i >= 4) {
                            *(stbsp__uint32*) bf = 0x20202020;
                            bf += 4;
                            i -= 4;
                        }
                        while (i) {
                            *bf++ = ' ';
                            --i;
                        }
                        stbsp__chk_cb_buf(1);
                    }

                // copy leader
                sn = lead + 1;
                while (lead[0]) {
                    stbsp__cb_buf_clamp(i, lead[0]);
                    lead[0] -= (char) i;
                    while (i) {
                        *bf++ = *sn++;
                        --i;
                    }
                    stbsp__chk_cb_buf(1);
                }

                // copy leading zeros
                c = cs >> 24;
                cs &= 0xffffff;
                cs = (fl & STBSP__TRIPLET_COMMA) ? ((stbsp__uint32) (c - ((pr + cs) % (c + 1)))) : 0;
                while (pr > 0) {
                    stbsp__cb_buf_clamp(i, pr);
                    pr -= i;
                    if ((fl & STBSP__TRIPLET_COMMA) == 0) {
                        while (i) {
                            if ((((stbsp__uintptr) bf) & 3) == 0)
                                break;
                            *bf++ = '0';
                            --i;
                        }
                        while (i >= 4) {
                            *(stbsp__uint32*) bf = 0x30303030;
                            bf += 4;
                            i -= 4;
                        }
                    }
                    while (i) {
                        if ((fl & STBSP__TRIPLET_COMMA) && (cs++ == c)) {
                            cs = 0;
                            *bf++ = stbsp__comma;
                        } else
                            *bf++ = '0';
                        --i;
                    }
                    stbsp__chk_cb_buf(1);
                }
            }

            // copy leader if there is still one
            sn = lead + 1;
            while (lead[0]) {
                stbsp__int32 i;
                stbsp__cb_buf_clamp(i, lead[0]);
                lead[0] -= (char) i;
                while (i) {
                    *bf++ = *sn++;
                    --i;
                }
                stbsp__chk_cb_buf(1);
            }

            // copy the string
            n = l;
            while (n) {
                stbsp__int32 i;
                stbsp__cb_buf_clamp(i, n);
                n -= i;
                STBSP__UNALIGNED(while (i >= 4) { *(stbsp__uint32 *)bf = *(stbsp__uint32 *)s; bf += 4; s += 4; i -= 4; })
                while (i) {
                    *bf++ = *s++;
                    --i;
                }
                stbsp__chk_cb_buf(1);
            }

            // copy trailing zeros
            while (tz) {
                stbsp__int32 i;
                stbsp__cb_buf_clamp(i, tz);
                tz -= i;
                while (i) {
                    if ((((stbsp__uintptr) bf) & 3) == 0)
                        break;
                    *bf++ = '0';
                    --i;
                }
                while (i >= 4) {
                    *(stbsp__uint32*) bf = 0x30303030;
                    bf += 4;
                    i -= 4;
                }
                while (i) {
                    *bf++ = '0';
                    --i;
                }
                stbsp__chk_cb_buf(1);
            }

            // copy tail if there is one
            sn = tail + 1;
            while (tail[0]) {
                stbsp__int32 i;
                stbsp__cb_buf_clamp(i, tail[0]);
                tail[0] -= (char) i;
                while (i) {
                    *bf++ = *sn++;
                    --i;
                }
                stbsp__chk_cb_buf(1);
            }

            // handle the left justify
            if (fl & STBSP__LEFTJUST)
                if (fw > 0) {
                    while (fw) {
                        stbsp__int32 i;
                        stbsp__cb_buf_clamp(i, fw);
                        fw -= i;
                        while (i) {
                            if ((((stbsp__uintptr) bf) & 3) == 0)
                                break;
                            *bf++ = ' ';
                            --i;
                        }
                        while (i >= 4) {
                            *(stbsp__uint32*) bf = 0x20202020;
                            bf += 4;
                            i -= 4;
                        }
                        while (i--)
                            *bf++ = ' ';
                        stbsp__chk_cb_buf(1);
                    }
                }
            break;

        default: // unknown, just copy code
            s = num + STBSP__NUMSZ - 1;
            *s = f[0];
            l = 1;
            fw = pr = fl = 0;
            lead[0] = 0;
            tail[0] = 0;
            pr = 0;
            dp = 0;
            cs = 0;
            goto scopy;
        }
        ++f;
    }
    endfmt:

    if (!callback)
        *bf = 0;
    else
        stbsp__flush_cb();

    done:
    return tlen + (int) (bf - buf);
}

// cleanup
#undef STBSP__LEFTJUST
#undef STBSP__LEADINGPLUS
#undef STBSP__LEADINGSPACE
#undef STBSP__LEADING_0X
#undef STBSP__LEADINGZERO
#undef STBSP__INTMAX
#undef STBSP__TRIPLET_COMMA
#undef STBSP__NEGATIVE
#undef STBSP__METRIC_SUFFIX
#undef STBSP__NUMSZ
#undef stbsp__chk_cb_bufL
#undef stbsp__chk_cb_buf
#undef stbsp__flush_cb
#undef stbsp__cb_buf_clamp

// ============================================================================
//   wrapper functions

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(sprintf)(char *buf, char const *fmt, ...) {
    int result;
    va_list va;
    va_start(va, fmt);
    result = STB_SPRINTF_DECORATE(vsprintfcb)(0, 0, buf, fmt, va);
    va_end(va);
    return result;
}

typedef struct stbsp__context {
    char *buf;
    int count;
    char tmp[STB_SPRINTF_MIN];
} stbsp__context;

static char* stbsp__clamp_callback(char *buf, void *user, int len) {
    stbsp__context *c = (stbsp__context*) user;

    if (len > c->count)
        len = c->count;

    if (len) {
        if (buf != c->buf) {
            char *s, *d, *se;
            d = c->buf;
            s = buf;
            se = buf + len;
            do {
                *d++ = *s++;
            } while (s < se);
        }
        c->buf += len;
        c->count -= len;
    }

    if (c->count <= 0)
        return 0;
    return (c->count >= STB_SPRINTF_MIN) ? c->buf : c->tmp; // go direct into buffer if you can
}

static char* stbsp__count_clamp_callback(char *buf, void *user, int len) {
    stbsp__context *c = (stbsp__context*) user;

    c->count += len;
    return c->tmp; // go direct into buffer if you can
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsnprintf)(char *buf, int count, char const *fmt, va_list va) {
    stbsp__context c;
    int l;

    if ((count == 0) && !buf) {
        c.count = 0;

        STB_SPRINTF_DECORATE( vsprintfcb )(stbsp__count_clamp_callback, &c, c.tmp, fmt, va);
        l = c.count;
    } else {
        if (count == 0)
            return 0;

        c.buf = buf;
        c.count = count;

        STB_SPRINTF_DECORATE( vsprintfcb )(stbsp__clamp_callback, &c, stbsp__clamp_callback(0, &c, 0), fmt, va);

        // zero-terminate
        l = (int) (c.buf - buf);
        if (l >= count) // should never be greater, only equal (or less) than count
            l = count - 1;
        buf[l] = 0;
    }

    return l;
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(snprintf)(char *buf, int count, char const *fmt, ...) {
    int result;
    va_list va;
    va_start(va, fmt);

    result = STB_SPRINTF_DECORATE(vsnprintf)(buf, count, fmt, va);
    va_end(va);

    return result;
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintf)(char *buf, char const *fmt, va_list va) {
    return STB_SPRINTF_DECORATE(vsprintfcb)(0, 0, buf, fmt, va);
}

// =======================================================================
//   low level float utility functions

#ifndef STB_SPRINTF_NOFLOAT

// copies d to bits w/ strict aliasing (this compiles to nothing on /Ox)
#define STBSP__COPYFP(dest, src)                   \
   {                                               \
      int cn;                                      \
      for (cn = 0; cn < 8; cn++)                   \
         ((char *)&dest)[cn] = ((char *)&src)[cn]; \
   }

// get float info
static stbsp__int32 stbsp__real_to_parts(stbsp__int64 *bits, stbsp__int32 *expo, double value) {
    double d;
    stbsp__int64 b = 0;

    // load value and round at the frac_digits
    d = value;

    STBSP__COPYFP(b, d);

    *bits = b & ((((stbsp__uint64) 1) << 52) - 1);
    *expo = (stbsp__int32) (((b >> 52) & 2047) - 1023);

    return (stbsp__int32) (b >> 63);
}

static double const stbsp__bot[23] = { 1e+000, 1e+001, 1e+002, 1e+003, 1e+004, 1e+005, 1e+006, 1e+007, 1e+008, 1e+009, 1e+010, 1e+011, 1e+012, 1e+013, 1e+014,
        1e+015, 1e+016, 1e+017, 1e+018, 1e+019, 1e+020, 1e+021, 1e+022 };
static double const stbsp__negbot[22] = { 1e-001, 1e-002, 1e-003, 1e-004, 1e-005, 1e-006, 1e-007, 1e-008, 1e-009, 1e-010, 1e-011, 1e-012, 1e-013, 1e-014,
        1e-015, 1e-016, 1e-017, 1e-018, 1e-019, 1e-020, 1e-021, 1e-022 };
static double const stbsp__negboterr[22] = { -5.551115123125783e-018, -2.0816681711721684e-019, -2.0816681711721686e-020, -4.7921736023859299e-021,
        -8.1803053914031305e-022, 4.5251888174113741e-023, 4.5251888174113739e-024, -2.0922560830128471e-025, -6.2281591457779853e-026,
        -3.6432197315497743e-027, 6.0503030718060191e-028, 2.0113352370744385e-029, -3.0373745563400371e-030, 1.1806906454401013e-032, -7.7705399876661076e-032,
        2.0902213275965398e-033, -7.1542424054621921e-034, -7.1542424054621926e-035, 2.4754073164739869e-036, 5.4846728545790429e-037, 9.2462547772103625e-038,
        -4.8596774326570872e-039 };
static double const stbsp__top[13] = { 1e+023, 1e+046, 1e+069, 1e+092, 1e+115, 1e+138, 1e+161, 1e+184, 1e+207, 1e+230, 1e+253, 1e+276, 1e+299 };
static double const stbsp__negtop[13] = { 1e-023, 1e-046, 1e-069, 1e-092, 1e-115, 1e-138, 1e-161, 1e-184, 1e-207, 1e-230, 1e-253, 1e-276, 1e-299 };
static double const stbsp__toperr[13] = { 8388608, 6.8601809640529717e+028, -7.253143638152921e+052, -4.3377296974619174e+075, -1.5559416129466825e+098,
        -3.2841562489204913e+121, -3.7745893248228135e+144, -1.7356668416969134e+167, -3.8893577551088374e+190, -9.9566444326005119e+213,
        6.3641293062232429e+236, -5.2069140800249813e+259, -5.2504760255204387e+282 };
static double const stbsp__negtoperr[13] = { 3.9565301985100693e-040, -2.299904345391321e-063, 3.6506201437945798e-086, 1.1875228833981544e-109,
        -5.0644902316928607e-132, -6.7156837247865426e-155, -2.812077463003139e-178, -5.7778912386589953e-201, 7.4997100559334532e-224,
        -4.6439668915134491e-247, -6.3691100762962136e-270, -9.436808465446358e-293, 8.0970921678014997e-317 };

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
static stbsp__uint64 const stbsp__powten[20] = {
   1,
   10,
   100,
   1000,
   10000,
   100000,
   1000000,
   10000000,
   100000000,
   1000000000,
   10000000000,
   100000000000,
   1000000000000,
   10000000000000,
   100000000000000,
   1000000000000000,
   10000000000000000,
   100000000000000000,
   1000000000000000000,
   10000000000000000000U
};
#define stbsp__tento19th ((stbsp__uint64)1000000000000000000)
#else
static stbsp__uint64 const stbsp__powten[20] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000ULL, 100000000000ULL,
        1000000000000ULL, 10000000000000ULL, 100000000000000ULL, 1000000000000000ULL, 10000000000000000ULL, 100000000000000000ULL, 1000000000000000000ULL,
        10000000000000000000ULL };
#define stbsp__tento19th (1000000000000000000ULL)
#endif

#define stbsp__ddmulthi(oh, ol, xh, yh)                            \
   {                                                               \
      double ahi = 0, alo, bhi = 0, blo;                           \
      stbsp__int64 bt;                                             \
      oh = xh * yh;                                                \
      STBSP__COPYFP(bt, xh);                                       \
      bt &= ((~(stbsp__uint64)0) << 27);                           \
      STBSP__COPYFP(ahi, bt);                                      \
      alo = xh - ahi;                                              \
      STBSP__COPYFP(bt, yh);                                       \
      bt &= ((~(stbsp__uint64)0) << 27);                           \
      STBSP__COPYFP(bhi, bt);                                      \
      blo = yh - bhi;                                              \
      ol = ((ahi * bhi - oh) + ahi * blo + alo * bhi) + alo * blo; \
   }

#define stbsp__ddtoS64(ob, xh, xl)          \
   {                                        \
      double ahi = 0, alo, vh, t;           \
      ob = (stbsp__int64)ph;                \
      vh = (double)ob;                      \
      ahi = (xh - vh);                      \
      t = (ahi - xh);                       \
      alo = (xh - (ahi - t)) - (vh + t);    \
      ob += (stbsp__int64)(ahi + alo + xl); \
   }

#define stbsp__ddrenorm(oh, ol) \
   {                            \
      double s;                 \
      s = oh + ol;              \
      ol = ol - (s - oh);       \
      oh = s;                   \
   }

#define stbsp__ddmultlo(oh, ol, xh, xl, yh, yl) ol = ol + (xh * yl + xl * yh);

#define stbsp__ddmultlos(oh, ol, xh, yl) ol = ol + (xh * yl);

static void stbsp__raise_to_power10(double *ohi, double *olo, double d, stbsp__int32 power) // power can be -323 to +350
{
    double ph, pl;
    if ((power >= 0) && (power <= 22)) {
        stbsp__ddmulthi(ph, pl, d, stbsp__bot[power]);
    } else {
        stbsp__int32 e, et, eb;
        double p2h, p2l;

        e = power;
        if (power < 0)
            e = -e;
        et = (e * 0x2c9) >> 14; /* %23 */
        if (et > 13)
            et = 13;
        eb = e - (et * 23);

        ph = d;
        pl = 0.0;
        if (power < 0) {
            if (eb) {
                --eb;
                stbsp__ddmulthi(ph, pl, d, stbsp__negbot[eb]);
                stbsp__ddmultlos(ph, pl, d, stbsp__negboterr[eb]);
            }
            if (et) {
                stbsp__ddrenorm(ph, pl);
                --et;
                stbsp__ddmulthi(p2h, p2l, ph, stbsp__negtop[et]);
                stbsp__ddmultlo(p2h, p2l, ph, pl, stbsp__negtop[et], stbsp__negtoperr[et]);
                ph = p2h;
                pl = p2l;
            }
        } else {
            if (eb) {
                e = eb;
                if (eb > 22)
                    eb = 22;
                e -= eb;
                stbsp__ddmulthi(ph, pl, d, stbsp__bot[eb]);
                if (e) {
                    stbsp__ddrenorm(ph, pl);
                    stbsp__ddmulthi(p2h, p2l, ph, stbsp__bot[e]);
                    stbsp__ddmultlos(p2h, p2l, stbsp__bot[e], pl);
                    ph = p2h;
                    pl = p2l;
                }
            }
            if (et) {
                stbsp__ddrenorm(ph, pl);
                --et;
                stbsp__ddmulthi(p2h, p2l, ph, stbsp__top[et]);
                stbsp__ddmultlo(p2h, p2l, ph, pl, stbsp__top[et], stbsp__toperr[et]);
                ph = p2h;
                pl = p2l;
            }
        }
    }
    stbsp__ddrenorm(ph, pl);
    *ohi = ph;
    *olo = pl;
}

// given a float value, returns the significant bits in bits, and the position of the
//   decimal point in decimal_pos.  +/-INF and NAN are specified by special values
//   returned in the decimal_pos parameter.
// frac_digits is absolute normally, but if you want from first significant digits (got %g and %e), or in 0x80000000
static stbsp__int32 stbsp__real_to_str(char const **start, stbsp__uint32 *len, char *out, stbsp__int32 *decimal_pos, double value, stbsp__uint32 frac_digits) {
    double d;
    stbsp__int64 bits = 0;
    stbsp__int32 expo, e, ng, tens;

    d = value;
    STBSP__COPYFP(bits, d);
    expo = (stbsp__int32) ((bits >> 52) & 2047);
    ng = (stbsp__int32) (bits >> 63);
    if (ng)
        d = -d;

    if (expo == 2047) // is nan or inf?
            {
        *start = (bits & ((((stbsp__uint64) 1) << 52) - 1)) ? "NaN" : "Inf";
        *decimal_pos = STBSP__SPECIAL;
        *len = 3;
        return ng;
    }

    if (expo == 0) // is zero or denormal
            {
        if ((bits << 1) == 0) // do zero
                {
            *decimal_pos = 1;
            *start = out;
            out[0] = '0';
            *len = 1;
            return ng;
        }
        // find the right expo for denormals
        {
            stbsp__int64 v = ((stbsp__uint64) 1) << 51;
            while ((bits & v) == 0) {
                --expo;
                v >>= 1;
            }
        }
    }

    // find the decimal exponent as well as the decimal bits of the value
    {
        double ph, pl;

        // log10 estimate - very specifically tweaked to hit or undershoot by no more than 1 of log10 of all expos 1..2046
        tens = expo - 1023;
        tens = (tens < 0) ? ((tens * 617) / 2048) : (((tens * 1233) / 4096) + 1);

        // move the significant bits into position and stick them into an int
        stbsp__raise_to_power10(&ph, &pl, d, 18 - tens);

        // get full as much precision from double-double as possible
        stbsp__ddtoS64(bits, ph, pl);

        // check if we undershot
        if (((stbsp__uint64) bits) >= stbsp__tento19th)
            ++tens;
    }

    // now do the rounding in integer land
    frac_digits = (frac_digits & 0x80000000) ? ((frac_digits & 0x7ffffff) + 1) : (tens + frac_digits);
    if ((frac_digits < 24)) {
        stbsp__uint32 dg = 1;
        if ((stbsp__uint64) bits >= stbsp__powten[9])
            dg = 10;
        while ((stbsp__uint64) bits >= stbsp__powten[dg]) {
            ++dg;
            if (dg == 20)
                goto noround;
        }
        if (frac_digits < dg) {
            stbsp__uint64 r;
            // add 0.5 at the right position and round
            e = dg - frac_digits;
            if ((stbsp__uint32) e >= 24)
                goto noround;
            r = stbsp__powten[e];
            bits = bits + (r / 2);
            if ((stbsp__uint64) bits >= stbsp__powten[dg])
                ++tens;
            bits /= r;
        }
        noround:
        ;
    }

    // kill long trailing runs of zeros
    if (bits) {
        stbsp__uint32 n;
        for (;;) {
            if (bits <= 0xffffffff)
                break;
            if (bits % 1000)
                goto donez;
            bits /= 1000;
        }
        n = (stbsp__uint32) bits;
        while ((n % 1000) == 0)
            n /= 1000;
        bits = n;
        donez:
        ;
    }

    // convert to string
    out += 64;
    e = 0;
    for (;;) {
        stbsp__uint32 n;
        char *o = out - 8;
        // do the conversion in chunks of U32s (avoid most 64-bit divides, worth it, constant denomiators be damned)
        if (bits >= 100000000) {
            n = (stbsp__uint32) (bits % 100000000);
            bits /= 100000000;
        } else {
            n = (stbsp__uint32) bits;
            bits = 0;
        }
        while (n) {
            out -= 2;
            *(stbsp__uint16*) out = *(stbsp__uint16*) &stbsp__digitpair[(n % 100) * 2];
            n /= 100;
            e += 2;
        }
        if (bits == 0) {
            if ((e) && (out[0] == '0')) {
                ++out;
                --e;
            }
            break;
        }
        while (out != o) {
            *--out = '0';
            ++e;
        }
    }

    *decimal_pos = tens;
    *start = out;
    *len = e;
    return ng;
}

#undef stbsp__ddmulthi
#undef stbsp__ddrenorm
#undef stbsp__ddmultlo
#undef stbsp__ddmultlos
#undef STBSP__SPECIAL
#undef STBSP__COPYFP

#endif // STB_SPRINTF_NOFLOAT

// clean up
#undef stbsp__uint16
#undef stbsp__uint32
#undef stbsp__int32
#undef stbsp__uint64
#undef stbsp__int64
#undef STBSP__UNALIGNED

#endif // STB_SPRINTF_IMPLEMENTATION

/*
 ------------------------------------------------------------------------------
 This software is available under 2 licenses -- choose whichever you prefer.
 ------------------------------------------------------------------------------
 ALTERNATIVE A - MIT License
 Copyright (c) 2017 Sean Barrett
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 ------------------------------------------------------------------------------
 ALTERNATIVE B - Public Domain (www.unlicense.org)
 This is free and unencumbered software released into the public domain.
 Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
 software, either in source code form or as a compiled binary, for any purpose,
 commercial or non-commercial, and by any means.
 In jurisdictions that recognize copyright laws, the author or authors of this
 software dedicate any and all copyright interest in the software to the public
 domain. We make this dedication for the benefit of the public at large and to
 the detriment of our heirs and successors. We intend this dedication to be an
 overt act of relinquishment in perpetuity of all present and future rights to
 this software under copyright law.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ------------------------------------------------------------------------------
 */

/* A mathematical expression evaluator.
 * It uses a recursive descent parser internally.
 * Author: Werner Stoop
 * This is free and unencumbered software released into the public domain.
 * http://unlicense.org/
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>  /* remember to compile with -lm */
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

/* Special tokens used by the lexer function lex()
 *  they've been chosen as non-printable characters
 *  so that printable characters can be used for other
 *  purposes
 */
#define TOK_END     0  /* end of text */
#define TOK_INI     1  /* Initial state */
#define TOK_ID      2  /* identifier */
#define TOK_NUM     3  /* number */

/* Types of errors */
// 0  /* "no error" */
#define ERR_MEMORY  1  /* "out of memory" */
#define ERR_LEXER   2  /* "unknown token" */
#define ERR_LONGID  3  /* "identifier too long" */
#define ERR_VALUE   4  /* "value expected" */
#define ERR_BRACKET 5  /* "missing ')'" */
#define ERR_FUNC    6  /* "unknown function" */
#define ERR_ARGS    7  /* "wrong number of arguments" */
#define ERR_CONST   8  /* "unknown constant" */

/* Other definitions */
#define MAX_ID_LEN  11      /* Max length of an identifier */
#define OPERATORS   "+-*/%(),^" /* Valid operators */

#define EVAL_PI         3.141592654
#define EVAL_E          2.718281828
#define EVAL_DEG        (EVAL_PI/180)

/* Internal structure for the parser/evaluator */
struct eval {

    jmp_buf j; /* For error handling */

    const char *p; /* Position in the text being parsed */

    double *st; /* Stack */
    int st_size; /* Stack size */
    int sp; /* Stack pointer */

    /* The current and next tokens identified by the lexer */
    struct {
        int type; /* Type of the token */
        double n_val; /* Numeric value of the previous lexed token */
        char s_val[MAX_ID_LEN]; /* String (identifier) value of the previous lexed token */
    } token[2];

    int cur_tok; /* Current token, either 0 or 1 (see the comments of lex()) */
};

/* Prototypes */
static double pop(struct eval *ev);
static void push(struct eval *ev, double d);
static int lex(struct eval *ev);

/* Prototypes for the recursive descent parser */
static void expr(struct eval *ev);
static void add_expr(struct eval *ev);
static void mul_expr(struct eval *ev);
static void pow_expr(struct eval *ev);
static void uni_expr(struct eval *ev);
static void bra_expr(struct eval *ev);
static void id_expr(struct eval *ev);
static void num_expr(struct eval *ev);

/*
 *  Evaluates a mathemeatical expression
 */
double streval(const char *exp/*, int *ep*/) {
    int _ep, *ep = &_ep;
    struct eval ev;
    double ans = 0.0;

    assert(ep != NULL);

    /* Allocate a stack */
    ev.st_size = 10;
    ev.st = CALLOC(ev.st_size, sizeof *ev.st);
    if (!ev.st) {
        *ep = ERR_MEMORY;
        return NAN; //0.0;
    }
    ev.sp = 0;

    /* Manage errors */
    *ep = setjmp(ev.j);
    if (*ep != 0) {
        FREE(ev.st);
        return NAN; //0.0;
    }

    /* Initialize the lexer */
    ev.token[0].type = TOK_INI;
    ev.token[0].s_val[0] = '\0';
    ev.token[1].type = TOK_INI;
    ev.token[1].s_val[0] = '\0';
    ev.cur_tok = 0;

    /* Initialize the parser */
    ev.p = exp;

    /* lex once to initialize the lexer */
    if (lex(&ev) != TOK_END) {
        expr(&ev);
        ans = pop(&ev);
    }

    FREE(ev.st);
    return ans;
}

/*
 * Pushes a value onto the stack, increases the stack size if necessary
 */
static void push(struct eval *ev, double d) {
    if (ev->sp == ev->st_size) {
        /* Resize the stack by 1.5 */
        double *old = ev->st;
        int new_size = ev->st_size + (ev->st_size >> 1);
        ev->st = REALLOC(ev->st, new_size);
        if (!ev->st) {
            ev->st = old;
            longjmp(ev->j, ERR_MEMORY);
        }

        ev->st_size = new_size;
    }

    ev->st[ev->sp++] = d;
}

//  Pops a value from the top of the stack
static double pop(struct eval *ev) {
    assert(ev->sp > 0);
    return ev->st[--ev->sp];
}

// stricmp() is common, but not standard, so I provide my own
static int istrcmp(const char *p, const char *q) {
    for (; tolower(p[0]) == tolower(q[0]) && p[0]; p++, q++)
        ;
    return tolower(p[0]) - tolower(q[0]);
}

/*
 *  Lexical analyzer function
 *
 *  In order to implement LL(1), struct eval has an array of two token structures,
 *  and its cur_tok member is used to point to the _current_ token, while the other
 *  element contains the _next_ token. This implements a 2 element ring buffer where
 *  the lexer always writes to the _next_ token so that the recursive descent parser can
 * _peek_ at the next token.
 */

static int lex(struct eval *ev) {
    int next_tok;

    start:
    /* Cycle the tokens */
    next_tok = ev->cur_tok;
    ev->cur_tok = ev->cur_tok ? 0 : 1;

    while (isspace(ev->p[0]))
        ev->p++;

    if (!ev->p[0]) {
        /* End of the expression */
        ev->token[next_tok].type = TOK_END;
        goto end;
    } else if (isdigit(ev->p[0]) || ev->p[0] == '.') {
        /* Number */
        char *endp;
        ev->token[next_tok].type = TOK_NUM;
        ev->token[next_tok].n_val = strtod(ev->p, &endp);
        ev->p = endp;
        goto end;
    } else if (isalpha(ev->p[0])) {
        /* Identifier */
        int i;
        for (i = 0; isalnum(ev->p[0]) && i < MAX_ID_LEN - 1; i++, ev->p++)
            ev->token[next_tok].s_val[i] = ev->p[0];

        if (isalpha(ev->p[0]))
            longjmp(ev->j, ERR_LONGID);

        ev->token[next_tok].s_val[i] = '\0';
        ev->token[next_tok].type = TOK_ID;
        goto end;
    } else if (strchr(OPERATORS, ev->p[0])) {
        /* Operator */
        ev->token[next_tok].type = ev->p[0];
        ev->p++;
        goto end;
    } else
        /* Unknown token */
        longjmp(ev->j, ERR_LEXER);

    end:

    /* If this was the first call, cycle the tokens again */
    if (ev->token[ev->cur_tok].type == TOK_INI)
        goto start;

    return ev->token[ev->cur_tok].type;
}

#define EVAL_TYPE(e)     (e->token[e->cur_tok].type)
#define EVAL_ERROR(c)    longjmp(ev->j, (c))

// num_expr ::= NUMBER
static void num_expr(struct eval *ev) {
    if (EVAL_TYPE(ev) != TOK_NUM)
        EVAL_ERROR(ERR_VALUE);
    push(ev, ev->token[ev->cur_tok].n_val);
    lex(ev);
}

// expr ::= add_expr
static void expr(struct eval *ev) {
    add_expr(ev);
}

// add_expr ::= mul_expr [('+'|'-') mul_expr]
static void add_expr(struct eval *ev) {
    int t;
    mul_expr(ev);
    while ((t = EVAL_TYPE(ev)) == '+' || t == '-') {
        double a, b;
        lex(ev);
        mul_expr(ev);
        b = pop(ev);
        a = pop(ev);

        if (t == '+')
            push(ev, a + b);
        else
            push(ev, a - b);
    }
}

// mul_expr ::= pow_expr [('*'|'/'|'%') pow_expr]
static void mul_expr(struct eval *ev) {
    int t;
    pow_expr(ev);
    while ((t = EVAL_TYPE(ev)) == '*' || t == '/' || t == '%') {
        double a, b;
        lex(ev);
        pow_expr(ev);
        b = pop(ev);
        a = pop(ev);

        if (t == '*')
            push(ev, a * b);
        else if (t == '/')
            push(ev, a / b);
        else
            push(ev, fmod(a, b));
    }
}

// pow_expr ::= uni_expr ['^' pow_expr]
static void pow_expr(struct eval *ev) {
    /* Note that exponentiation is right associative:
     2^3^4 is 2^(3^4), not (2^3)^4 */
    uni_expr(ev);
    if (EVAL_TYPE(ev) == '^') {
        double a, b;
        lex(ev);
        pow_expr(ev);
        b = pop(ev);
        a = pop(ev);
        push(ev, pow(a, b));
    }
}

// uni_expr ::= ['+'|'-'] bra_expr
static void uni_expr(struct eval *ev) {
    int t = '+';
    if (EVAL_TYPE(ev) == '-' || EVAL_TYPE(ev) == '+') {
        t = EVAL_TYPE(ev);
        lex(ev);
    }

    bra_expr(ev);

    if (t == '-') {
        double a = pop(ev);
        push(ev, -a);
    }
}

// bra_expr ::= '(' add_expr ')' | id_expr
static void bra_expr(struct eval *ev) {
    if (EVAL_TYPE(ev) == '(') {
        lex(ev);
        add_expr(ev);
        if (EVAL_TYPE(ev) != ')')
            EVAL_ERROR(ERR_BRACKET);
        lex(ev);
    } else
        id_expr(ev);
}

// id_expr ::= ID '(' add_expr [',' add_expr]* ')' | ID | num_expr
static void id_expr(struct eval *ev) {
    int nargs = 0;
    char id[MAX_ID_LEN];
    if (EVAL_TYPE(ev) != TOK_ID) {
        num_expr(ev);
    } else {
        strcpy(id, ev->token[ev->cur_tok].s_val);
        lex(ev);
        if (EVAL_TYPE(ev) != '(') {
            /**/if (!istrcmp(id, "true"))
                push(ev, 1.0);
            else if (!istrcmp(id, "false"))
                push(ev, 0.0);
            else if (!istrcmp(id, "on"))
                push(ev, 1.0);
            else if (!istrcmp(id, "off"))
                push(ev, 0.0);
            // pi - 3.141592654
            else if (!istrcmp(id, "pi"))
                push(ev, EVAL_PI);
            // e - base of natural logarithms, 2.718281828
            else if (!istrcmp(id, "e"))
                push(ev, EVAL_E);
            // deg - deg2rad, allows to degree conversion `sin(90*deg) = 1`
            else if (!istrcmp(id, "deg"))
                push(ev, EVAL_DEG);
            else
                EVAL_ERROR(ERR_CONST);
        } else {
            lex(ev);

            while (EVAL_TYPE(ev) != ')') {
                add_expr(ev);
                nargs++;
                if (EVAL_TYPE(ev) == ')')
                    break;

                if (EVAL_TYPE(ev) != ',')
                    EVAL_ERROR(ERR_BRACKET);
                lex(ev);
            }
            lex(ev);

            // abs(x) - absolute value of x
            if (!istrcmp(id, "abs")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, fabs(pop(ev)));
            }
            // ceil(x) - smallest integer greater than x
            else if (!istrcmp(id, "ceil")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, ceil(pop(ev)));
            }
            // floor(x) - largest integer smaller than x
            else if (!istrcmp(id, "floor")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, floor(pop(ev)));
            }
            // sin(x) - sine of x, in radians
            else if (!istrcmp(id, "sin")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, sin(pop(ev)));
            }
            // asin(x) - arcsine of x, in radians
            else if (!istrcmp(id, "asin")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, asin(pop(ev)));
            }
            // cos(x) - cosine of x, in radians
            else if (!istrcmp(id, "cos")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, cos(pop(ev)));
            }
            // acos(x) - arccosine of x, in radians
            else if (!istrcmp(id, "acos")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, acos(pop(ev)));
            }
            // tan(x) - tangent of x, in radians
            else if (!istrcmp(id, "tan")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, tan(pop(ev)));
            }
            // atan(x) - arctangent of x, in radians
            else if (!istrcmp(id, "atan")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, atan(pop(ev)));
            }
            // atan(y,x) - arctangent of y/x, in radians.
            else if (!istrcmp(id, "atan2")) {
                double a, b;
                if (nargs != 2)
                    EVAL_ERROR(ERR_ARGS);
                b = pop(ev);
                a = pop(ev);
                push(ev, atan2(a, b));
            }
            // sinh(x) - hyperbolic sine of x, in radians
            else if (!istrcmp(id, "sinh")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, sinh(pop(ev)));
            }
            // cosh(x) - hyperbolic cosine of x, in radians
            else if (!istrcmp(id, "cosh")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, cosh(pop(ev)));
            }
            // tanh(x) - hyperbolic tangent of x, in radians
            else if (!istrcmp(id, "tanh")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, tanh(pop(ev)));
            }
            // log(x) - natural logarithm of x
            else if (!istrcmp(id, "log")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, log(pop(ev)));
            }
            // log10(x) - logarithm of x, base-10
            else if (!istrcmp(id, "log10")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, log10(pop(ev)));
            }
            // exp(x) - computes e^x
            else if (!istrcmp(id, "exp")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, exp(pop(ev)));
            }
            // sqrt(x) - square root of x
            else if (!istrcmp(id, "sqrt")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, sqrt(pop(ev)));
            }
            // rad(x) - converts x from degrees to radians
            else if (!istrcmp(id, "rad")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, pop(ev) * EVAL_PI / 180);
            }
            // deg(x) - converts x from radians to degrees
            else if (!istrcmp(id, "deg")) {
                if (nargs != 1)
                    EVAL_ERROR(ERR_ARGS);
                push(ev, pop(ev) * 180 / EVAL_PI);
            }
            // pow(x,y) - computes x^y
            else if (!istrcmp(id, "pow")) {
                double a, b;
                if (nargs != 2)
                    EVAL_ERROR(ERR_ARGS);
                b = pop(ev);
                a = pop(ev);
                push(ev, pow(a, b));
            }
            // hypot(x,y) - computes sqrt(x*x + y*y)
            else if (!istrcmp(id, "hypot")) {
                double a, b;
                if (nargs != 2)
                    EVAL_ERROR(ERR_ARGS);
                b = pop(ev);
                a = pop(ev);
                push(ev, sqrt(a * a + b * b));
            } else
                EVAL_ERROR(ERR_FUNC);
        }
    }
}

//

#ifdef EVALDEMO
#include <stdio.h>
int main(int argc, char *argv[]) {
    int i;
    double e;

    for(i = 1; i < argc; i++) {
        e = streval(argv[i]);
        if(e != e)
            fprintf(stderr, "Error in expression %s\n", argv[i]);
        else
            printf("%s = %g\n", argv[i], e);
    }

    assert( streval("1+1") == 2 );
    assert( streval("1+") != streval("1+") );
    assert(~puts("Ok") );
}
#endif

// ## rob pike's regexp match (apparently public domain).
// [ref] https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
// @todo: evaluate @kokke/tiny-regex-c instead.

int regstar(const char *string, const char *re, int c);

int reghere(const char *string, const char *re) {
    if (re[0] == '\0')
        return 1;
    if (re[1] == '*')
        return regstar(string, re + 2, re[0]);
    if (re[0] == '$' && re[1] == '\0')
        return *string == '\0';
    if (*string != '\0' && (re[0] == '?' || re[0] == *string))
        return reghere(string + 1, re + 1);
    return 0;
}

int regstar(const char *string, const char *re, int c) {
    do { /* a * matches zero or more instances */
        if (reghere(string, re))
            return 1;
    } while (*string != '\0' && (*string++ == c || c == '?'));
    return 0;
}

int strregex(const char *string, const char *re) {
    if (re[0] == '^')
        return reghere(string, re + 1);
    do { /* must look even if string is empty */
        if (reghere(string, re))
            return 1;
    } while (*string++ != '\0');
    return 0;
}

bool strmatch(const char *text, const char *pattern) {
    $
    if (*pattern == '\0')
        return !*text;
    if (*pattern == '*')
        return strmatch(text, pattern + 1) || (*text && strmatch(text + 1, pattern));
    if (*pattern == '?')
        return *text && (*text != '.') && strmatch(text + 1, pattern + 1);
    return (*text == *pattern) && strmatch(text + 1, pattern + 1);
}

#ifdef REGEXDEMO
#include <assert.h>
#include <stdio.h>
int main() {
    assert( strregex("hello123", "^hel?*$") );
    assert( strmatch("hello", "h?ll*") );
    assert( ~puts("Ok.") );
}
#endif

// ## C-style formatting
// - rlyeh, public domain.

#include <stdarg.h>

// Wrap vsnprintf into a statically allocated buffer. A bunch of buffers are
// handled internally so that nested calls are safe within reasonable limits.

static builtin(thread) int vl_index = 0;
static builtin(thread) char *vl_buffer[16] = { 0 };
TEMP char* strfv(const char *fmt, va_list lst) { //$
    int idx = (++vl_index) % 16;
    int sz = 1 + strvsnprintf(0, 0, fmt, lst);
    vl_buffer[idx] = (char*) REALLOC(vl_buffer[idx], sz);
    strvsnprintf(vl_buffer[idx], sz, fmt, lst);
    return vl_buffer[idx];
}
TEMP char* strf(const char *fmt, ...) { //$
    va_list lst;
    va_start(lst, fmt);
    char *rc = strfv(fmt, lst);
    va_end(lst);
    return rc;
}
HEAP char* strcpyfv(char **str, const char *fmt, va_list lst) { //$
    TEMP char *buf = strfv(fmt, lst);
    if (str && *str) {
        int len = strlen(buf) + 1;
        (*str) = (char*) REALLOC(str && (*str) ? (*str) : 0, len);
        memcpy((*str), buf, len);
        return *str;
    } else {
        return str ? *str = STRDUP(buf) : STRDUP(buf);
    }
}
HEAP char* strcpyf(char **str, const char *fmt, ...) { //$
    va_list lst;
    va_start(lst, fmt);
    char *rc = strcpyfv(str, fmt, lst);
    va_end(lst);
    return rc;
}
HEAP char* strcatfv(char **str, const char *fmt, va_list lst) { //$
    TEMP char *buf = strfv(fmt, lst);
    if (str && *str) {
        int l1 = strlen(*str), l2 = strlen(buf);
        (*str) = (char*) REALLOC((*str), l1 + l2 + 1);
        memcpy((*str) + l1, buf, l2 + 1);
        return *str;
    } else {
        return str ? *str = STRDUP(buf) : STRDUP(buf);
    }
}
HEAP char* strcatf(char **str, const char *fmt, ...) { //$
    va_list lst;
    va_start(lst, fmt);
    HEAP char *rc = strcatfv(str, fmt, lst);
    va_end(lst);
    return rc;
}

// # string matching ##########################################################
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>
#include <assert.h>

const char* strsub(const char *str, int pos) {
    $
    int size = strlen(str);
    pos = pos && size ? (pos > 0 ? pos % size : size - 1 + ((pos + 1) % size)) : 0;
    return str + pos;
}

const char* strfindl(const char *text, const char *substring) {
    $
    const char *found = strstr(text, substring);
    return found ? found : text + strlen(text);
}
const char* strfindr(const char *text, const char *substring) {
    $
    char *found = 0;
    while (1) {
        char *found2 = strstr(text, substring);
        if (!found2)
            break;
        found = found2;
        text = found2 + 1;
    }
    return found ? found : text + strlen(text);
}

bool strbegin(const char *text, const char *substring) {
    $
    // also, return strncmp(string, substr, strlen(substr)) == 0;
    int s1 = strlen(text), s2 = strlen(substring);
    return s1 >= s2 ? 0 == memcmp(&text[0], substring, s2) : false;
}
bool strend(const char *text, const char *substring) {
    $
    int s1 = strlen(text), s2 = strlen(substring);
    return s1 >= s2 ? 0 == memcmp(&text[s1 - s2], substring, s2) : false;
}

bool streq(const char *string, const char *substr) {
    $
    return !strcmp(string, substr);
}
bool streqi(const char *string, const char *substr) {
    $
    while (*string && *substr) {
        int eqi = (*string++ | 32) == (*substr++ | 32);
        if (!eqi)
            return 0;
    }
    return *string == 0 && *substr == 0;
}

#ifdef MATCHDEMO
#include <stdio.h>
int main() {
    assert( streq("hello", "hello") );
    assert(!streq("HELLO", "hello") );

    assert( streqi("hello", "hello") );
    assert( streqi("HELLO", "hello") );

    assert( strbegin("hello", "hell") );
    assert(!strbegin("hell", "hello") );
    assert( strend("hello", "llo") );

    assert(~puts("Ok"));
}
#endif

// ## string conversion unit utils
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>

int64_t strint(const char *string) {
    $
    int64_t v = 0, n = 1;
    if (string) {
        while (*string == '-')
            n *= -1, string++;
        while (*string >= '0' && *string <= '9')
            v = (v * 10) + *string++ - '0';
    }
    return n * v;
}

static builtin(thread) char strhuman_buf[8] = { 0 };
TEMP char* strhuman(uint64_t number) {
    $
    int base = 1000; // ideally 1000 for units, 1024 for bits (conversion: 0.9765625)
    const char prefixes[] = " KMGTPEZY";
    const char *prefixp = prefixes;
    uint64_t i = number, d = 0;
    while ((i > base) && *prefixp++) {
        d = (i % base) / 10, i /= base;
    }
    if (d > 0)
        strsnprintf(strhuman_buf, sizeof(strhuman_buf), "%llu.%llu%c", i, d, *prefixp);
    else
        strsnprintf(strhuman_buf, sizeof(strhuman_buf), "%llu%c", i, *prefixp);
    return strhuman_buf;
}

uint64_t strrobot(const char *string) {
    $
    int base = 1000; // ideally 1000 for units, 1024 for bits (conversion: 0.9765625)
    size_t sz = 1, mul = 0;
    char *pend;
    double num = strtod(string, &pend);
    sz = pend - string;
    while (string[sz] && string[sz] == ' ')
        sz++;
    switch (string[sz]) {
        default:
            mul = 0;
            break;
        case 'K':
        case 'k':
            mul = 1;
            break;
        case 'M':
        case 'm':
            mul = 2;
            break;
        case 'G':
        case 'g':
            mul = 3;
            break;
        case 'T':
        case 't':
            mul = 4;
            break;
        case 'P':
        case 'p':
            mul = 5;
            break;
        case 'E':
        case 'e':
            mul = 6; // may overflow
            break;
        case 'Z':
        case 'z':
            mul = 7; // may overflow
            break;
        case 'Y':
        case 'y':
            mul = 8; // may overflow
    }
    while (mul--)
        if (num * base < num)
            return 0;
        else
            num *= base;
    return num;
}

#ifdef CONVERSIONDEMO
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main() {
    // string to integer (atoi)
    assert( strint( "-120" ) == -120 );
    // safe substring access (forward)
    assert(!strcmp(strsub( "Hello", 0), "Hello"));
    assert(!strcmp(strsub( "Hello", 1), "ello"));
    assert(!strcmp(strsub( "Hello", 2), "llo"));
    assert(!strcmp(strsub( "Hello", 3), "lo"));
    assert(!strcmp(strsub( "Hello", 4), "o"));
    assert(!strcmp(strsub( "Hello", 5), "Hello"));
    // safe substring access (backward)
    assert(!strcmp(strsub( "Hello", 0), "Hello"));
    assert(!strcmp(strsub( "Hello",-1), "o"));
    assert(!strcmp(strsub( "Hello",-2), "lo"));
    assert(!strcmp(strsub( "Hello",-3), "llo"));
    assert(!strcmp(strsub( "Hello",-4), "ello"));
    assert(!strcmp(strsub( "Hello",-5), "Hello"));
    // human<-->robot conversion
    assert(!strcmp(strhuman(120000),"120K"));
    assert( strrobot("1435.23Gb") == 1435230000000ULL );
    //
    assert(~puts("Ok"));
}
#endif

// ## string transform utils
// First four functions are based on code by Bob Stout (public domain).
// - rlyeh, public domain.

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* strlower(char *string) {
    if (string)
        for (char *s = string; *s; ++s)
            *s = tolower(*s);
    return string;
}
char* strupper(char *string) {
    if (string)
        for (char *s = string; *s; ++s)
            *s = toupper(*s);
    return string;
}
char* strrev(char *string) {
    if (string && *string)
        for (char *p1 = string, *p2 = p1 + strlen(p1) - 1; p2 > p1; ++p1, --p2) {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
        }
    return string;
}
char* strdel(char *string, const char *substring) {
    if (string) {
        char *p = strstr(string, substring);
        if (p) {
            for (int len = strlen(substring); p[len]; ++p) {
                p[0] = p[len];
            }
            *p = 0;
        }
    }
    return string;
}
char* strremap( INOUT char *string, const char srcs[], const char dsts[]) {
    $
    uint8_t map[256] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
            "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
            "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f"
            "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f"
            "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"
            "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
            "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"
            "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
            "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f"
            "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f"
            "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf"
            "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf"
            "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf"
            "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf"
            "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef"
            "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
    for (int i = 0; srcs[i]; ++i)
        map[(uint8_t) srcs[i]] = dsts[i];
    for (int i = 0; string[i]; ++i)
        string[i] = map[(uint8_t) string[i]];
    return string;
}

#ifdef TRANSFORMDEMO
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    char buf[] = "hello cruel world";
    assert( 0 == strcmp("hello world", strdel(buf, "cruel ")) );
    assert( 0 == strcmp("dlrow olleh", strrev(buf)) );

    char remap[] = "H3110 W0r1d";
    assert( 0 == strcmp("h3110 w0r1d", strlower(remap)));
    assert( 0 == strcmp("hello world", strremap(remap, "310", "elo")));
    assert(~puts("Ok"));
}
#endif

// ## string transform utils
// - rlyeh, public domain.

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* strtrimbff(char *string, const char *substring) {
    $
    char *found = strstr(string, substring);
    if (found) {
        int L = strlen(substring);
        memmove(string, found + L, strlen(string) - L);
    }
    return string;
}
char* strtrimffe(char *string, const char *substring) {
    $
    ((char*) strfindl(string, substring))[0] = 0;
    return string;
}
char* strtrimblf(char *string, const char *substring) {
    $
    const char *found = strfindr(string, substring);
    int L = strlen(substring);
    memmove(string, found + L, strlen(found) - L + 1);
    return string;
}
char* strtrimlfe(char *string, const char *substring) {
    $
    ((char*) strfindr(string, substring))[0] = 0;
    return string;
}
char* strtrimws(char *str) {
    char *ibuf, *obuf;
    if (str) {
        for (ibuf = obuf = str; *ibuf;) {
            while (*ibuf && isspace(*ibuf))
                (ibuf++);
            if (*ibuf && obuf != str)
                *(obuf++) = ' ';
            while (*ibuf && !isspace(*ibuf))
                *(obuf++) = *(ibuf++);
        }
        *obuf = 0;
    }
    return str;
}

#ifdef TRIMDEMO
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    {
        char bufws[] = "   Hello  world  ";
        assert( 0 == strcmp("Hello world", strtrimws(bufws)));

        char buf1[] = "hellohelloworldworld";
        char buf2[] = "hellohelloworldworld";
        char buf3[] = "hellohelloworldworld";
        char buf4[] = "hellohelloworldworld";
        strtrimbff(buf1, "ell"); puts(buf1); assert( 0 == strcmp( buf1, "ohelloworldworld") );
        strtrimffe(buf2, "ell"); puts(buf2); assert( 0 == strcmp( buf2, "h") );
        strtrimblf(buf3, "ell"); puts(buf3); assert( 0 == strcmp( buf3, "oworldworld") );
        strtrimlfe(buf4, "ell"); puts(buf4); assert( 0 == strcmp( buf4, "helloh") );
    }
    assert(~puts("Ok"));
}
#endif

// ## replace substring in a string
// - rlyeh, public domain.

#include <assert.h>

HEAP char* strrepl(char **string, const char *target, const char *replace) {
$
        assert(string);
    char HEAP *buf = 0, *aux = *string;
    for (int tgtlen = strlen(target); tgtlen && aux[0];) {
        char *found = strstr(aux, target);
        if (found) {
            strcatf(&buf, "%.*s%s", (int) (found - aux), aux, replace);
            aux += (found - aux) + tgtlen;
        } else {
            strcatf(&buf, "%s", aux);
            break;
        }
    }
    if (buf) {
        strcpyf(string, "%s", buf);
        FREE(buf);
    }
    return *string;
}

#ifdef REPLACEDEMO
#include <stdio.h>
int main() {
      #define test(a,b,eq) do { \
        char *buf = strcpyf(0, "%s", "mary has a little lamb little lamb"); \
        puts(strrepl(&buf, a, b)); \
        assert( 0 == strcmp(eq, buf) ); \
        free(buf); \
      } while(0)
      test("little" /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
      test("big"    /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
      test("little" /*->*/, "big",    /*==*/ "mary has a big lamb big lamb");
      test("little "/*->*/, "",       /*==*/ "mary has a lamb lamb");
      test(""       /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
}
#endif

// ## split strings into tokens
// - rlyeh, public domain.

#include <stdlib.h>
#include <string.h>
#include <assert.h>

int strchop(const char *string, const char *delimiters, int avail, const char *tokens[]) {
$
        assert(avail >= 4 && 0 == (avail % 2));
    for (avail /= 2; *string && avail-- > 0;) {
        int n = strcspn(string += strspn(string, delimiters), delimiters);
        *tokens++ = ((*tokens++ = (const char*) (uintptr_t) n)) ? string : "";
        string += n;
    }
    return *tokens++ = 0, *tokens = 0, avail > 0;
}

HEAP char** strsplit(const char *string, const char *delimiters) {
    $
    int L = strlen(string), len = sizeof(char*) * (L / 2 + 1 + 1), i = 0;
    char **res = (char**) CALLOC(1, len + L + 1);
    char *buf = strcpy((char*) res + len, string);
    for (char *token = strtok(buf, delimiters); token; token = strtok(NULL, delimiters)) {
        res[i++] = token;
    }
    return res;
}

HEAP char* strjoin(char **string, char *words[], const char *separator) {
    char* (*table[2])(char**, const char*, ...) = {strcpyf, strcatf };
    char *out = string ? *string : 0;
    for (int i = 0; words[i] /*i < nwords*/; ++i) {
        table[!!i](&out, "%s%s", i > 0 ? separator : "", words[i]);
    }
    return string ? *string = out : out;
}

#ifdef SPLITDEMO
#include <stdio.h>
int main() {
    // split input text into tokens. allocates once.
    HEAP char **tokens = strsplit("JAN,;,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC", ",;");
    HEAP char *joint = strjoin( 0, tokens, "/" );
    puts( joint );
    free( joint );
    free( tokens );

    // split input text into tokens. does not allocate.
    const char *words[32] = {0};
    if( strchop( "There is a lady who's sure, all that glitter is gold...", " ,.", 32, words ) ) { // "$"
        for( int i = 0; words[i]; i += 2 ) {
            printf("[%.*s],", (int)(uintptr_t)words[i+0], words[i+1]);
        }
    }
}
#endif

// # string options parsing ###################################################
// - rlyeh, public domain

#ifdef __GNUC__ // also, clang
int __argc;
char **__argv;
__attribute__((constructor)) void init_argcv(int argc, char **argv) {
    __argc = argc;
    __argv = argv;
}
#else
    // MINGW: _argc, _argv
    // HP-UX:  __argc_value, __argv_value 
    // libc:  __libc_argc, __libc_argv
#endif

const char* stropt(const char *defaults, const char *options_csv) {
    $
    const char *tokens[128];
    if (strchop(options_csv, ",", 128, tokens)) {
        for (int t = 0; tokens[t]; t += 2) {
            int size = (int) (uintptr_t) tokens[t];
            const char *token = tokens[t + 1];
            for (int i = 1; i < __argc; ++i) {
                const char *kv = __argv[i];
                if (strlen(kv) >= size && !memcmp(kv, token, size)) {
                    kv += kv[size] == '=';
                    defaults = kv[size] ? kv + size : defaults;
                }
            }
        }
    }
    return defaults;
}

double stroptf(double defaults, const char *options_csv) {
    $
    const char *s = stropt(0, options_csv);
    if (!s)
        return defaults;
    // evaluate expression, includes on/off and true/false tokens
    double v = streval(s);
    if (v != v)
        return defaults;
    // skip digits and symbols
    char charset[] = "0123456789+-/*^()";
    s += strspn(s, charset);
    // si units
    double unit = 1.0;
    /**/if (*s == 'n')
        unit = 1e-9;
    else if (*s == 'u')
        unit = 1e-6;
    else if (*s == 'm')
        unit = 1e-3;
    else if (*s == 'c')
        unit = 1e-2;
    else if (*s == 'd')
        unit = 1e-1;
    //   if( *s =='da' ) unit = 1e1;
    else if (*s == 'h')
        unit = 1e2;
    else if (*s == 'k')
        unit = 1e3;
    else if (*s == 'K')
        unit = 1e3; /*alias*/
    else if (*s == 'M')
        unit = 1e6;
    else if (*s == 'G')
        unit = 1e9;
    else if (*s == 'T')
        unit = 1e12;
    // digital information conversion to kibi, mebi, gibi, etc
    double conv = (*s && s[1] == 'i' ? 1.024 : 1.0);
    return v * unit * conv;
}

int64_t stropti(int64_t defaults, const char *options_csv) {
    $
    return (int64_t) stroptf((double) defaults, options_csv);
}

#ifdef OPTIONDEMO
#include <stdio.h>
int main() {
    // showcase:
    // demo.exe
    // demo.exe --client=off --server=true --user=another@mail.com
    // demo.exe --port=1111 --distance=120km --time=2ms --bits=4Kib --health=(10+12)*10
    printf("cfg.user: %s\n",     stropt("your@mail.com", "-u,--user"));
    printf("cfg.port: %f\n",     stroptf(8080, "-p,--port"));
    printf("cfg.client: %f\n",   stroptf(1, "-c,--client"));
    printf("cfg.server: %f\n",   stroptf(0, "-s,--server"));
    printf("cfg.distance: %f\n", stroptf(0, "-d,--distance"));
    printf("cfg.time: %f\n",     stroptf(0, "-t,--time"));
    printf("cfg.bits: %f\n",     stroptf(0, "-b,--bits"));
    printf("cfg.health: %f\n",   stroptf(50, "-h,--health"));
}
#endif

// Function to normalize resource identificators.
// - rlyeh, public domain.
//
// Basically `strnorm(string)` does a string transformation from given string
// to a deterministic pattern, which is guarnateed to remain inmutable (on a
// high degree) on code, even if name of physical source is altered externally.
// 
// This means different unified resource URIs will have same string hash if they
// point to the very same asset on disk. You usually want to normalize all your
// asset URIs before hashing the paths and storing them in a virtual filesystem.
//
// As a bonus point, transforming a normalized uri will return the very same value.
// 
// ## Features
// - Normalize folder/asset separators.
// - Normalize English singular/plurals.
// - Normalize AoS (OO) and SoA (ECS) disk layouts.
// - Normalize absolute, relative, virtual and remote paths.
// - Normalize uppercases, lowercases, whitespaces and hyphens.
// - Normalize extensions, double extensions and double punctuations.
// - Normalize SOV, SVO, VSO, VOS, OVS, OSV subject/verb/object language topologies.
// - Normalize folder/file tagging (useful when globbing and deploying files and/or directories).
// - Normalize previously unified ids (lossless process).
//
// ## Todo
// - Normalize typos on unicode diacritics.
//

static
int strnorm_strcmp(const void *a, const void *b) {
    return strcmp(*(char* const*) a, *(char* const*) b);
}

static builtin(thread) char *strnorm_buf[16] = { 0 };
static builtin(thread) int strnorm_buflevel = 0;

TEMP char* strnorm(const char *uri) {

#   define with (strnorm_buflevel[strnorm_buf])
    strnorm_buflevel = (strnorm_buflevel + 1) % 16;

    // 0. @todo: unescape url here
    // 1. @todo: convert diacritics into latin characters here (romanization)
    // 2. camelCase to lisp-case

    int i = 0;
    char lbuf[511 + 1] = { 0 };
    for (char *p = lbuf; *uri && i < 511; ++uri) {
        if (islower(*uri)) {
            p[i++] = *uri;
        } else {
            p[i++] = '-';
            p[i++] = tolower(*uri);
        }
    }
    char *lisp = (lbuf[i] = 0, &lbuf[lbuf[0] == '-']);

    // 3. lowercase
    TEMP char *buf = strlower(strcpyf(&with, "%s", lisp));

    // 4. remove url options at eos (if any)
    strtrimffe(buf, "?");

    // 5. split path "\\/" up to 2nd level only
    HEAP char **tokens = strsplit(buf, "\\/");
    int n = 0;
    while (tokens[n])
        n++;
    char *file = tokens[n - 1];
    char *path = n >= 2 ? tokens[n - 2] : "";

    // 6. strip all #tags and trim extensions
    strtrimffe(file, ".");
    strtrimffe(file, "#");
    strtrimffe(path, ".");
    strtrimffe(path, "#");
    strcpyf(&with, "%s_%s", path, file);
    FREE(tokens);

    // 7. convert separators to underscores
    strremap( with, " -,|;:()[]", "__________");

    // 8. split stems
    HEAP char **words = strsplit(with, "_");

    // 9. trim aos/soa plurals
    int w = 0;
    while (words[w]) {
        int L = strlen(words[w]);
        if (words[w][L - 1] == 's')
            words[w][L - 1] = 0;
        ++w;
    }

    // 10. sort and join stems
    qsort(words, w, sizeof(char*), strnorm_strcmp);
    strjoin(&with, words, "_");
    FREE(words);

    return &with[0];
#   undef with
}

#ifdef NORMDEMO
#include <assert.h>
#include <stdio.h>
int main() {
    const char *should_be;
    #define test(expr) printf( "[%s] %s\n", !strcmp(strnorm(expr),should_be) ? " OK ":"FAIL", strnorm(expr) )
    if( "test absolute, relative, virtual and remote paths" ) {
        should_be = "folder_logo_main";
        test( "~home/game/folder/main logo.jpg" );
        test( "~user/game1/folder/main logo.jpg" );
        test( "~mark/game2/folder/main logo.jpg" );
        test( "~john/game3/data/folder/main logo.jpg" );
        test( "../folder/main logo.jpg" );
        test( "C:\\data\\folder\\main logo.jpg" );
        test( "C:/game/data/folder/main logo.jpg" );
        test( "data.zip/data/folder/main logo.jpg" );
        test( "virtual.rar/folder/main logo.jpg" );
        test( "http://web.domain.com%20/folder/main logo.jpg?blabla=123&abc=123#qwe" );
    }
    if( "test uppercases, lowercases, whitespaces and hyphens" ) {
        should_be = "folder_logo_main";
        test( "folder/main-logo" );
        test( "folder/main_logo" );
        test( "folder/Main logo" );
        test( "folder / Main  logo " );
    }
    if( "test camelCase" ) {
        should_be = "folder_logo_main";
        test( "folderMainLogo" );
        test( "FolderMainLogo" );
        test( "folder/MainLogo" );
        test( "folder/MainLogo" );
    }
    if( "test folder/asset separators" ) {
        should_be = "folder_logo_main";
        test( "folder/main-logo" );
        test( "folder\\main-logo" );
        test( "folder-main-logo" );
        test( "folder_main-logo" );
        test( "folder|main-logo" );
        test( "folder:main-logo" );
        test( "folder;main-logo" );
        test( "folder,main-logo" );
        test( "[folder]main-logo" );
        test( "main-logo(folder)" );
    }
    if( "test extensions" ) {
        should_be = "folder_logo_main";
        test( "folder/main_logo.jpg" );
        test( "folder/main_logo.png" );
        test( "folder/main_logo.webp" );
    }
    if( "test double extensions and double punctuations" ) {
        should_be = "folder_logo_main";
        test( "folder/main logo.bmp.png" );
        test( "folder/main  logo..png" );
    }
    if( "test diacritics" ) {
        // @todo: diacritrics need additional utf8 pass. might be much slower though.
        // should_be = "animation_walk";
        // test( "âñimátïón/wàlk" );
    }
    if( "test AoS (OO) and SoA (ECS) disk layouts" ) {
        should_be = "logo_purple";
        test( "logos/purple" );
        test( "purple/logo" );
        should_be = "kid_sprite";
        test( "sprites/kid" );
        test( "kid/sprite" );
    }
    if( "test SOV, SVO, VSO, VOS, OVS, OSV subject/verb/object language topologies"
        "test English plurals as well" ) {
        should_be = "join_player_scene";
        test( "player-joins-scene.intro" );
        test( "player-scene-join.intro" );
        test( "join-player-scene.intro" );
        test( "join-scene-player.intro" );
        test( "scene-join-player.intro" );
        test( "scene-player-join.intro" );
    }
    if( "test folder/file tagging" ) {
        should_be = "logo_splash";
        test( "splash/logo" );
        test( "/splash #win32/logo" );
        test( "splash #mobile/logo #win32=always.png" );
    }
    if( "test re-normalization consistency" ) {
        should_be = "folder_logo_main";
        test( strnorm("main/folder-logo") );
        test( strnorm(strnorm("main/folder-logo")) );
    }
    assert(~puts("Ok"));
}
#endif

// ## string interning (quarks)
// - rlyeh, public domain.

#include <stdint.h>
#include <assert.h>

static builtin(thread) int quarklen = 0, quarkcap = 0;
static builtin(thread) char *quarks = 0;

int strput(const char *string) {
    $
    if (!quarks) {
        // init buffer on first time
        quarks = (char*) REALLOC(quarks, (1 + 1));
        quarkcap += 1;
        // copy null string
        quarks[0] = 0;
        quarklen += 1;
        quarkcap -= 1;
    }
    if (string && string[0]) {
        int len = strlen(string) + 1;
        if (quarkcap < len) {
            int extend = (int) (len * 1.5f); // 2.33f
            // printf("alloc += %d\n", extend);
            quarks = (char*) REALLOC(quarks, quarklen + extend);
            quarkcap += extend;
        }
        memcpy(quarks + quarklen, string, len);
        quarklen += len;
        quarkcap -= len;
        // printf("%d/%d\n", quarklen, quarklen+quarkcap);
        return quarklen - len;
    }
    return 0;
}
const char* strget(int key) {
    assert(quarks);
    return quarks + key;
}

#ifdef INTERNDEMO
#include <stdio.h>
#include <assert.h>
int main() {
    assert( !strput(NULL) ); // quark #0, couldnt intern null string
    assert( !strput("") );   // quark #0, can intern empty string
    assert( !strget(0)[0] ); // empty string for quark #0

    int q1 = strput("Hello");  // -> quark #1
    int q2 = strput("cruel");  // -> quark #2
    int q3 = strput("world."); // -> quark #3
    //printf("%d/%d\n", quarklen, quarklen+quarkcap);

    char buf[256];
    sprintf(buf, "%s %s %s", strget(q1), strget(q2), strget(q3));
    assert( !strcmp("Hello cruel world.", buf) );

    assert(~puts("Ok"));
}
#endif

// ## Fuzzy string matching
// Ideas from https://blog.forrestthewoods.com/reverse-engineering-sublime-text-s-fuzzy-match-4cffeed33fdb
// - rlyeh, public domain.

#include <string.h>

int strscore(const char *str1, const char *str2) {
    int score = 0, consecutive = 0, maxerrors = 0;
    while (*str1 && *str2) {
        int is_leading = (*str1 & 64) && !(str1[1] & 64);
        if ((*str1 & ~32) == (*str2 & ~32)) {
            int had_separator = (str1[-1] <= 32);
            int x = had_separator || is_leading ? 10 : consecutive * 5;
            consecutive = 1;
            score += x;
            ++str2;
        } else {
            int x = -1, y = is_leading * -3;
            consecutive = 0;
            score += x;
            maxerrors += y;
        }
        ++str1;
    }
    return score + (maxerrors < -9 ? -9 : maxerrors);
}

const char* strfuzzy(const char *str, int num, const char *words[]) {
    int scoremax = 0;
    const char *best = 0;
    for (int i = 0; i < num; ++i) {
        int score = strscore(words[i], str);
        int record = (score >= scoremax);
        int draw = (score == scoremax);
        if (record) {
            scoremax = score;
            if (!draw)
                best = words[i];
            else
                best = best && strlen(best) < strlen(words[i]) ? best : words[i];
        }
    }
    return best ? best : "";
}

#ifdef FUZZYDEMO
#include <stdio.h>

int main( int argc, char **argv ) {
    if( argc <= 1 ) printf("%s command\n", argv[0]), exit(0);
    const char *texts[] = {
        "The Black Knight",
        "SVisualLoggerLogsList.h",
        "AnimGraphNode_CopyBone",
        "client_unit.cpp",
        "Miskatonic university",
        "MockAI.h",
        "MacroCallback.cpp",
        "MockGameplayTasks.h",
        "MovieSceneColorTrack.cpp",
        "ce skipsplash",
        "ce skipsplashscreen",
        "ce skipscreen",
        "ce skipaa",
        "r.maxfps",
        "r.maxsteadyfps",
        "slomo 10",
        "retrograd",
        "retrocomputer",
        "return",
        "level",
        "leveler",
        "letrograd",
        "restart",
        "resource",
        "reset",
        "reboot",
        "rescale",
    };
    const char *partial_word = argv[1]; // try 'tk', 'reset', 'rest', etc...
    /* printf("Scoring '%s'\n", partial_word);
    for( int i = 0; i < sizeof(texts) / sizeof(texts[0]); ++i ) {
        printf("Score %d: (%s vs %s\n", strscore(texts[i], partial_word), texts[i], partial_word );
    } */
    const char *fuzzy_search = strfuzzy( partial_word, sizeof(texts)/sizeof(texts[0]), texts );
    printf(">> Did you mean '%s' instead of '%s'?\n", fuzzy_search, partial_word );
}
#endif

// ## utf8 and unicode
// Based on code by @ddiakopoulos (unlicensed).
// Based on code by @nothings (public domain).
// - rlyeh, public domain.

uint32_t strutf32(INOUT const char **p) {
    $
    if ((**p & 0x80) == 0x00) {
        int a = *((*p)++);
        return a;
    }
    if ((**p & 0xe0) == 0xc0) {
        int a = *((*p)++) & 0x1f;
        int b = *((*p)++) & 0x3f;
        return (a << 6) | b;
    }
    if ((**p & 0xf0) == 0xe0) {
        int a = *((*p)++) & 0x0f;
        int b = *((*p)++) & 0x3f;
        int c = *((*p)++) & 0x3f;
        return (a << 12) | (b << 6) | c;
    }
    if ((**p & 0xf8) == 0xf0) {
        int a = *((*p)++) & 0x07;
        int b = *((*p)++) & 0x3f;
        int c = *((*p)++) & 0x3f;
        int d = *((*p)++) & 0x3f;
        return (a << 18) | (b << 12) | (c << 8) | d;
    }
    return 0;
}
static builtin(thread) uint8_t utf[8] = { 0 };
TEMP char* strutf8(uint32_t cp) {
    $
    int n = 0;
    /**/if (cp < 0x80)
        n = 1;
    else if (cp < 0x800)
        n = 2;
    else if (cp < 0x10000)
        n = 3;
    else if (cp < 0x200000)
        n = 4;
    else if (cp < 0x4000000)
        n = 5;
    else if (cp <= 0x7fffffff)
        n = 6;
    switch (n) {
        case 6:
            utf[5] = 0x80 | (cp & 0x3f);
            cp = (cp >> 6) | 0x4000000;
        case 5:
            utf[4] = 0x80 | (cp & 0x3f);
            cp = (cp >> 6) | 0x200000;
        case 4:
            utf[3] = 0x80 | (cp & 0x3f);
            cp = (cp >> 6) | 0x10000;
        case 3:
            utf[2] = 0x80 | (cp & 0x3f);
            cp = (cp >> 6) | 0x800;
        case 2:
            utf[1] = 0x80 | (cp & 0x3f);
            cp = (cp >> 6) | 0xc0;
        case 1:
            utf[0] = cp;
        default:
            ;
    }
    return utf[n] = '\0', (char*) utf;
}

wchar_t* strwiden_(wchar_t *buffer, const char *ostr, int n) {
    $
    const uint8_t *str = (const uint8_t*) ostr;
    uint32_t c;
    int i = 0;
    --n;
    while (*str) {
        if (i >= n)
            return NULL;
        if (!(*str & 0x80))
            buffer[i++] = *str++;
        else if ((*str & 0xe0) == 0xc0) {
            if (*str < 0xc2)
                return NULL;
            c = (*str++ & 0x1f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            buffer[i++] = c + (*str++ & 0x3f);
        } else if ((*str & 0xf0) == 0xe0) {
            if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf))
                return NULL;
            if (*str == 0xed && str[1] > 0x9f)
                return NULL; // str[1] < 0x80 is checked below
            c = (*str++ & 0x0f) << 12;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            buffer[i++] = c + (*str++ & 0x3f);
        } else if ((*str & 0xf8) == 0xf0) {
            if (*str > 0xf4)
                return NULL;
            if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf))
                return NULL;
            if (*str == 0xf4 && str[1] > 0x8f)
                return NULL; // str[1] < 0x80 is checked below
            c = (*str++ & 0x07) << 18;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 12;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f);
            // utf-8 encodings of values used in surrogate pairs are invalid
            if ((c & 0xFFFFF800) == 0xD800)
                return NULL;
            if (c >= 0x10000) {
                c -= 0x10000;
                if (i + 2 > n)
                    return NULL;
                buffer[i++] = 0xD800 | (0x3ff & (c >> 10));
                buffer[i++] = 0xDC00 | (0x3ff & (c));
            }
        } else
            return NULL;
    }
    buffer[i] = 0;
    return buffer;
}

char* strshorten_(char *buffer, const wchar_t *str, int n) {
    $
    int i = 0;
    --n;
    while (*str) {
        if (*str < 0x80) {
            if (i + 1 > n)
                return NULL;
            buffer[i++] = (char) *str++;
        } else if (*str < 0x800) {
            if (i + 2 > n)
                return NULL;
            buffer[i++] = 0xc0 + (*str >> 6);
            buffer[i++] = 0x80 + (*str & 0x3f);
            str += 1;
        } else if (*str >= 0xd800 && *str < 0xdc00) {
            uint32_t c;
            if (i + 4 > n)
                return NULL;
            c = ((str[0] - 0xd800) << 10) + ((str[1]) - 0xdc00) + 0x10000;
            buffer[i++] = 0xf0 + (c >> 18);
            buffer[i++] = 0x80 + ((c >> 12) & 0x3f);
            buffer[i++] = 0x80 + ((c >> 6) & 0x3f);
            buffer[i++] = 0x80 + ((c) & 0x3f);
            str += 2;
        } else if (*str >= 0xdc00 && *str < 0xe000) {
            return NULL;
        } else {
            if (i + 3 > n)
                return NULL;
            buffer[i++] = 0xe0 + (*str >> 12);
            buffer[i++] = 0x80 + ((*str >> 6) & 0x3f);
            buffer[i++] = 0x80 + ((*str) & 0x3f);
            str += 1;
        }
    }
    buffer[i] = 0;
    return buffer;
}

TEMP wchar_t* strwiden(const char *str) {
    int len = strlen(str) * 6;
    wchar_t *buffer = (wchar_t*) MALLOC(len);
    return strwiden_(buffer, str, len);
}

TEMP char* strshorten(const wchar_t *str) {
    int len = wcslen(str) * 6;
    char *buffer = (char*) MALLOC(len);
    return strshorten_(buffer, str, len);
}

#ifdef UTFDEMO
#include <assert.h>
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"user32.lib")
#endif
int main() {
    const char *text = "私 は ガ";
    const char *copy = text;
    assert( strutf32(&copy) == 31169 );
    assert( strutf32(&copy) == 32 );
    assert( strutf32(&copy) == 12399 );
    assert( strutf32(&copy) == 32 );
    assert( strutf32(&copy) == 12460 );
    assert( strutf32(&copy) == 0 );
#ifdef _WIN32
    MessageBoxW(0, strwiden(text), L"Unicode", 0);
#endif
    assert(~puts("Ok"));
}
#endif

// ## Compile time string hash (pure C)
// Based on code by http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash
// This macro is not always inlined. Depends on compilers and optimization flags.
// For example g++ requires -O3 and msvc requires /O2 (verify output assembly with /Fa).
// About the hash function, it is using my own and free hashing algorithm.
// - rlyeh, public domain.

/*
 [macro already defined in header]
 #define STRHASHLEN(str)               (sizeof(str)-1)
 #define STRHASHCHR(str,idx)           ((unsigned)str[(idx)<STRHASHLEN(str)?STRHASHLEN(str)-1-(idx):STRHASHLEN(str)])
 #define STRHASH01(hsh,mul,str,idx)    ((STRHASHCHR(str,idx) ^ hsh) * mul)
 #define STRHASH04(hsh,mul,str,idx)    STRHASH01(STRHASH01(STRHASH01(STRHASH01(hsh,mul,str,idx+ 3),mul,str,idx+ 2),mul,str,idx+ 1),mul,str,idx)
 #define STRHASH16(hsh,mul,str,idx)    STRHASH04(STRHASH04(STRHASH04(STRHASH04(hsh,mul,str,idx+12),mul,str,idx+ 8),mul,str,idx+ 4),mul,str,idx)
 #define STRHASH64(hsh,mul,str,idx)    STRHASH16(STRHASH16(STRHASH16(STRHASH16(hsh,mul,str,idx+48),mul,str,idx+32),mul,str,idx+16),mul,str,idx)
 #define STRHASH(str)                  STRHASH64(0,131ull,str,0)
 */

#include <stdint.h>

uint64_t strhash(const char *str) {
    uint64_t hash = 0;
    while (*str++) {
        hash = (str[-1] ^ hash) * 131ull;
    }
    return hash;
}

#ifdef HASHDEMO
#include <stdio.h>
int main() {
    uint64_t literal = (uint64_t)0xf0e28e9bdecd6646ull;
    printf("%016llx\n", literal);

    uint64_t precomp = (uint64_t)STRHASH("/hello/world.txt");
    printf("%016llx\n", precomp);

    uint64_t runtime = (uint64_t)strhash("/hello/world.txt");
    printf("%016llx\n", runtime);
}
#endif

#endif // STDSTRING_IMPLEMENTATION
#endif // STDSTRING_H
