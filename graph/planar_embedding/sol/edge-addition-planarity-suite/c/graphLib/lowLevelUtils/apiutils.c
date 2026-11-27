/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

#include "appconst.h"

#include "apiutils.h"
#include "apiutils.private.h"

// The graphLib gp_ErrorMessage() and gp_Message() calls are suppressed by
// default, but an application can turn them on if desired.
unsigned quietMode = QUIETMODE_ALL;

unsigned gp_GetQuietMode(void)
{
    return quietMode;
}

void gp_SetQuietMode(unsigned newQuietMode)
{
    quietMode = newQuietMode;
}

void gp_Message(const char *message, ...)
{
    if (!(gp_GetQuietMode() & QUIETMODE_MESSAGES))
    {
        va_list args;

        va_start(args, message);
        vfprintf(stdout, message, args);
        va_end(args);

        fprintf(stdout, "\n");

        fflush(stdout);
    }
}

void gp_MessagePrompt(const char *message, ...)
{
    if (!(gp_GetQuietMode() & QUIETMODE_MESSAGES))
    {
        va_list args;

        va_start(args, message);
        vfprintf(stdout, message, args);
        va_end(args);

        fprintf(stdout, " ");

        fflush(stdout);
    }
}

void gp_LogErrorMessage(int lineNum, const char *srcFileName, const char *message, ...)
{
    if (!(gp_GetQuietMode() & QUIETMODE_ERRORS))
    {
        va_list args;

        fprintf(stderr, "[ERROR] ");

        va_start(args, message);
        vfprintf(stderr, message, args);
        va_end(args);

        if (lineNum > 0 && srcFileName != NULL)
            fprintf(stderr, "\n\ton line %d of '%s'", lineNum, srcFileName);

        fprintf(stderr, "\n");

        fflush(stderr);
    }
}

/********************************************************************
 gp_GetRandomNumber()
 This function generates a random number between NMin and NMax
 inclusive.  It assumes that the caller has called srand().
 It calls rand(), but before truncating to the proper range,
 it adds the high bits of the rand() result into the low bits.
 The result of this is that the randomness appearing in the
 truncated bits also has an affect on the non-truncated bits.
 ********************************************************************/

int gp_GetRandomNumber(int NMin, int NMax)
{
    unsigned int N = (unsigned int)rand();

    if (NMax < NMin)
        return NMin;

    /* Folded in unsigned arithmetic because the additions below overflow a
       signed int for rand() results just below INT_MAX. */

    N += ((N & 0xFFFF0000) >> 16);
    N += ((N & 0x0000FF00) >> 8);
    N %= (unsigned int)(NMax - NMin + 1);
    return (int)(N & 0x7FFFFFFF) + NMin;
}


/********************************************************************
 debugNOTOK()

 This function returns the literal value of NOTOK. In debug mode,
 NOTOK is redefined to first use printf() to emit information about
 where in the code a NOTOK has occurred. Then, this method is invoked
 so that the debug version of NOTOK still returns the NOTOK value.

 Rather than just returning 0 in the debug-mode NOTOK macro, we
 invoke this method because it gives the option (with recompilation)
 of having the program exit on the first NOTOK occurrence. That
 option is off by default, so we normally get a stack trace of the
 NOTOK occcurences, but on an exhaustive, long-run test, it can be
 handy to stop on the first error since otherwise the error message
 might not be seen.
 ********************************************************************/

#ifdef DEBUG
int debugNOTOK(void)
{
    // exit(-1);
    return 0; // NOTOK is normally defined to be zero
}
#endif

// LOGGING is not defined in the standard compile configuration.
// A graphLib developer can uncomment LOGGING in apiutils.private.h
#ifdef LOGGING

/********************************************************************
 _Log()

 When the project is compiled with LOGGING enabled, this method writes
 a string to the file Edge_Addition_Planarity_Suite.LOG in the current
 working directory.

 On first write, the file is created or cleared.
 Call this method with NULL to close the log file.
 ********************************************************************/

void closeLogFileAtExit(void);

void _Log(char const *Str)
{
    static FILE *logfile = NULL;
    static int triedlogfile = FALSE;

    if (logfile == NULL && !triedlogfile)
    {
        triedlogfile = TRUE;
        if (atexit(closeLogFileAtExit) != 0)
            gp_ErrorMessage("Unable to set up atexit() to close Edge_Addition_Planarity_Suite log file on exit");
        else
        {
            if ((logfile = fopen("Edge_Addition_Planarity_Suite.LOG", WRITETEXT)) == NULL)
                gp_ErrorMessage("Unable to open the Edge_Addition_Planarity_Suite log file");
        }
    }

    if (logfile != NULL)
    {
        if (Str != NULL)
        {
            fprintf(logfile, "%s", Str);
            fflush(logfile);
        }
        else
        {
            fclose(logfile);
            logfile = NULL;
        }
    }
}

void _LogLine(char const *Str)
{
    _Log(Str);
    _Log("\n");
}

void closeLogFileAtExit(void)
{
    _gp_Log(NULL);
}

static char LogStr[MAXLINE + 1];

char *_MakeLogStr1(const char *format, int one)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    sprintf(LogStr, format, one);
#pragma GCC diagnostic pop
    return LogStr;
}

char *_MakeLogStr2(const char *format, int one, int two)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    sprintf(LogStr, format, one, two);
#pragma GCC diagnostic pop
    return LogStr;
}

char *_MakeLogStr3(const char *format, int one, int two, int three)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    sprintf(LogStr, format, one, two, three);
#pragma GCC diagnostic pop
    return LogStr;
}

char *_MakeLogStr4(const char *format, int one, int two, int three, int four)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    sprintf(LogStr, format, one, two, three, four);
#pragma GCC diagnostic pop
    return LogStr;
}

char *_MakeLogStr5(const char *format, int one, int two, int three, int four, int five)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    sprintf(LogStr, format, one, two, three, four, five);
#pragma GCC diagnostic pop
    return LogStr;
}

#endif // LOGGING
