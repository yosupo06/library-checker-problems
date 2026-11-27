#ifndef APPCONST_H
#define APPCONST_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "apiutils.h"

// NOTE: This is defined on 32- and 64-bit Windows systems; see
// https://sourceforge.net/p/predef/wiki/OperatingSystems
#if defined(WIN32) || defined(_WIN32)
#define WINDOWS
#endif

/* Defines fopen strings for reading and writing text files on PC and UNIX */

#ifdef WINDOWS
#define READTEXT "rt"
#define WRITETEXT "wt"
#define FILE_DELIMITER '\\'
#else
#define READTEXT "r"
#define WRITETEXT "w"
#define FILE_DELIMITER '/'
#endif

/* Define DEBUG to get additional debugging. The default is to define it when MSC does */

#ifdef _DEBUG
#define DEBUG
#endif

/* Some low-level functions are replaced by faster macros, except when debugging */

#define SPEED_MACROS
#ifdef DEBUG
#undef SPEED_MACROS
#endif

/* Return status values; OK/NOTOK behave like Boolean true/false,
   not like program exit codes. */

#define OK 1
#define NOTOK 0

#ifdef DEBUG
#undef NOTOK
extern int debugNOTOK(void);
#include <stdio.h>
#define NOTOK (gp_ErrorMessage("NOTOK occurred"), debugNOTOK())
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

// Define one of these to use 1-based arrays or the original 0-based arrays
// It used to be true that the 1-based arrays were faster, but compiler
// optimizations have come a long way in two decades.
//
// The main advantages of 1-based arrays are readability of the data,
// that NIL is still an index within array bounds, that 1-based supports
// 0-based files but not the reverse, and continuing the long-time default.
#define USE_1BASEDARRAYS
// #define USE_0BASEDARRAYS

#ifdef USE_0BASEDARRAYS
#undef USE_1BASEDARRAYS
#endif

/* Array indexes are used as pointers, and NIL means bad pointer */
#ifdef USE_1BASEDARRAYS
// This definition is used with 1-based array indexing
#define NIL 0
#define NIL_CHAR 0x00
#else
// This definition is used with 0-based array indexing
#define NIL -1
#define NIL_CHAR 0xFF
#endif

#endif
