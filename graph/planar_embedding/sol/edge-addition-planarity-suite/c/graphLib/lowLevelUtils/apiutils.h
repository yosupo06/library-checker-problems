/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/
#ifndef APIUTILS_H
#define APIUTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <limits.h>

#define MAXLINE 1024

// The string representation for an integer must account for: an optional '-',
// then 10 digits (max signed 32-bit int), and a null-terminator
#define MAXCHARSFOR32BITINT 11

#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#define APPLY_FORMAT_ATTRIBUTE 0
#elif defined(__has_attribute)
#define APPLY_FORMAT_ATTRIBUTE __has_attribute(format)
#elif defined(__GNUC__) || defined(__clang__)
#define APPLY_FORMAT_ATTRIBUTE 1
#else
#define APPLY_FORMAT_ATTRIBUTE 0
#endif

#if APPLY_FORMAT_ATTRIBUTE
#if defined(__GNUC__) && !defined(__clang__)
#define FORMAT_PRINTF(formatIndex, firstArg) __attribute__((format(gnu_printf, formatIndex, firstArg)))
#else
#define FORMAT_PRINTF(formatIndex, firstArg) __attribute__((format(printf, formatIndex, firstArg)))
#endif
#else
#define FORMAT_PRINTF(formatIndex, firstArg)
#endif

    // These methods control whether gp_ErrorMessage() and gp_Message() calls
    // emit output or skip producing output (the default)
    unsigned gp_GetQuietMode(void);
    void gp_SetQuietMode(unsigned newQuietMode);

#define QUIETMODE_NONE 0
#define QUIETMODE_ERRORS 1
#define QUIETMODE_MESSAGES 2
#define QUIETMODE_ALL 0XFFFFFFFF

    void gp_Message(const char *message, ...) FORMAT_PRINTF(1, 2);
    void gp_MessagePrompt(const char *message, ...) FORMAT_PRINTF(1, 2);

#define gp_ErrorMessage(...) (gp_LogErrorMessage(__LINE__, __FILE__, __VA_ARGS__))
    void gp_LogErrorMessage(int lineNum, const char *srcFileName, const char *message, ...) FORMAT_PRINTF(3, 4);

    int gp_GetRandomNumber(int NMin, int NMax);

#ifdef __cplusplus
}
#endif

#endif
