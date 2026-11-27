/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/
#ifndef APIUTILS_PRIVATE_H
#define APIUTILS_PRIVATE_H

#ifdef __cplusplus
extern "C"
{
#endif

    /* PRIVATE FUNCTIONS FOR ADDITIONAL INFORMATIONAL LOGGING.

       If LOGGING is defined by uncommenting it below, then log-related lines
       write to the log, and otherwise they no-op.

       By default, neither release nor DEBUG builds including LOGGING.
       Logging is used to see more details of how various algorithms
       handle a particular graph. */

// #define LOGGING
#ifdef LOGGING

#define _gp_LogLine _LogLine
#define _gp_Log _Log

    void _LogLine(const char *Line);
    void _Log(const char *Line);

#define _gp_MakeLogStr1 _MakeLogStr1
#define _gp_MakeLogStr2 _MakeLogStr2
#define _gp_MakeLogStr3 _MakeLogStr3
#define _gp_MakeLogStr4 _MakeLogStr4
#define _gp_MakeLogStr5 _MakeLogStr5

    char *_MakeLogStr1(const char *format, int one);
    char *_MakeLogStr2(const char *format, int one, int two);
    char *_MakeLogStr3(const char *format, int one, int two, int three);
    char *_MakeLogStr4(const char *format, int one, int two, int three, int four);
    char *_MakeLogStr5(const char *format, int one, int two, int three, int four, int five);

#else
#define _gp_LogLine(Line)
#define _gp_Log(Line)
#define _gp_MakeLogStr1(format, one)
#define _gp_MakeLogStr2(format, one, two)
#define _gp_MakeLogStr3(format, one, two, three)
#define _gp_MakeLogStr4(format, one, two, three, four)
#define _gp_MakeLogStr5(format, one, two, three, four, five)
#endif

#ifdef __cplusplus
}
#endif

#endif
