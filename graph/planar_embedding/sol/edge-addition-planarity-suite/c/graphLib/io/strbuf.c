/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../lowLevelUtils/appconst.h"
#include "../lowLevelUtils/apiutils.h"
#include "strbuf.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/********************************************************************
 sb_New()
 Allocates a string buffer with space for capacity characters, plus one
 for a null terminator

 Returns the allocated string buffer, or NULL on error.
 ********************************************************************/
strBufP sb_New(int capacity)
{
    strBufP theStrBuf;

    if (capacity < 0 || capacity == INT_MAX)
        return NULL;

    theStrBuf = (strBufP)malloc(sizeof(strBuf));

    if (theStrBuf != NULL)
    {
        theStrBuf->buf = (char *)malloc((capacity + 1) * sizeof(char));
        if (theStrBuf->buf == NULL)
        {
            free(theStrBuf);
            theStrBuf = NULL;
        }
    }

    if (theStrBuf != NULL)
    {
        theStrBuf->capacity = capacity;
        sb_ClearBuf(theStrBuf);
    }

    return theStrBuf;
}

/********************************************************************
 sb_Free()
 Receives a pointer-pointer to a string buffer.
 Frees the memory of the string buffer structure and the string buffer
 it contains. Using the pointer-pointer, sets the pointer to NULL.
 ********************************************************************/
void sb_Free(strBufP *pStrBuf)
{
    if (pStrBuf != NULL && *pStrBuf != NULL)
    {
        (*pStrBuf)->capacity = (*pStrBuf)->size = (*pStrBuf)->readPos = 0;

        if ((*pStrBuf)->buf != NULL)
            free((*pStrBuf)->buf);
        (*pStrBuf)->buf = NULL;

        free(*pStrBuf);
        *pStrBuf = NULL;
    }
}

/********************************************************************
 sb_CleareBuf()
 The string buffer is changed, if not NULL, to hold an empty string,
 including setting the size and position to 0. The capacity is not
 changed.
 ********************************************************************/
void sb_ClearBuf(strBufP theStrBuf)
{
    if (theStrBuf != NULL)
    {
        if (theStrBuf->buf != NULL)
            theStrBuf->buf[0] = '\0';
        theStrBuf->size = theStrBuf->readPos = 0;
    }
}

/********************************************************************
 sb_Copy()
 Receives strBuf pointers for a destination and source.
 Ensures that the destination has the capacity of the source.
 Copies the source string content into the destination, and sets the
 size correctly.
 Returns OK for success, NOTOK on param or memory allocation error.
 ********************************************************************/
int sb_Copy(strBufP strBufDst, strBufP strBufSrc)
{
    char *tempBuf;
    strBufP newStrBuf = sb_Duplicate(strBufSrc);

    if (strBufDst == NULL || strBufSrc == NULL || newStrBuf == NULL)
    {
        sb_Free(&newStrBuf);
        return NOTOK;
    }

    tempBuf = strBufDst->buf;
    strBufDst->buf = newStrBuf->buf;
    newStrBuf->buf = tempBuf;

    sb_Free(&newStrBuf);

    strBufDst->size = strBufSrc->size;
    strBufDst->capacity = strBufSrc->capacity;

    return OK;
}

/********************************************************************
 sb_Duplicate()
 Receives a strBuf pointer. Allocates a new strBuf structure with the
 same capacity, and initially clears it. If the received strBuf has
 a non-empty string, then it is copied into the duplicate, and
 the duplicates size is set correctly.
 Returns the duplicate, or NULL on memory allocation error.
 ********************************************************************/
strBufP sb_Duplicate(strBufP theStrBuf)
{
    strBufP newStrBuf = sb_New(theStrBuf->capacity);

    if (newStrBuf == NULL)
        return NULL;

    if (theStrBuf->size > 0)
    {
        strcpy(newStrBuf->buf, theStrBuf->buf);
        newStrBuf->size = theStrBuf->size;
    }

    return newStrBuf;
}

/********************************************************************
 sb_ReadSkipWhitespace()
 Advances the read position managed by the string buffer by skipping
 any number of whitespace characters, if present.
 ********************************************************************/

void sb_ReadSkipWhitespace(strBufP theStrBuf)
{
    if (theStrBuf != NULL && theStrBuf->buf != NULL)
    {
        while (isspace(theStrBuf->buf[theStrBuf->readPos]))
            theStrBuf->readPos++;
    }
}

/********************************************************************
 sb_ReadSkipInteger()
 Advances the read position managed by the string buffer by skipping
 an initial negative sign, if present, then skipping any number of
 numeric digits, if present.
 ********************************************************************/
void sb_ReadSkipInteger(strBufP theStrBuf)
{
    if (theStrBuf != NULL && theStrBuf->buf != NULL)
    {
        if (theStrBuf->buf[theStrBuf->readPos] == '-')
            theStrBuf->readPos++;

        while (isdigit(theStrBuf->buf[theStrBuf->readPos]))
            theStrBuf->readPos++;
    }
}

/********************************************************************
 sb_ConcatString()
 Appends the content of string s to the end of the content already
 in the string buffer. If the append would exceed the capacity of
 the buffer, then the buffer capacity is first increased. It is
 increased to one greater than the sum of the current capacity and the
 new string size or double the capacity (to ensure the memory space is
 big enough for both strings and linear time performance over many
 small concatenations).
 Returns OK on success, NOTOK on error
 ********************************************************************/
int sb_ConcatString(strBufP theStrBuf, char const *s)
{
    // Switched to size_t to fix int overflow and also warnings on 64-bit builds
    size_t strLen = s == NULL ? 0 : strlen(s);

    if (strLen == 0)
        return OK;

    if (theStrBuf == NULL || theStrBuf->buf == NULL)
        return NOTOK;

    if (theStrBuf->size + strLen > INT_MAX)
        return NOTOK;

    if ((size_t)theStrBuf->size + strLen > (size_t)theStrBuf->capacity)
    {
        size_t newLen = 0, doubleCapacity = 0;
        char *newBuf = NULL;

        doubleCapacity = ((size_t)theStrBuf->capacity) << 1;
        newLen = theStrBuf->size + strLen;
        if (newLen < doubleCapacity && (doubleCapacity + 1) <= INT_MAX)
            newLen = doubleCapacity;

        if ((newLen + 1) > INT_MAX)
            return NOTOK;

        newBuf = (char *)malloc((newLen + 1) * sizeof(char));
        if (newBuf == NULL)
            return NOTOK;

        strcpy(newBuf, theStrBuf->buf);
        free(theStrBuf->buf);
        theStrBuf->buf = newBuf;
        theStrBuf->capacity = (int)newLen;
    }

    strcpy(theStrBuf->buf + theStrBuf->size, s);
    theStrBuf->size += (int)strLen;

    return OK;
}

/********************************************************************
 sb_ConcatChar()
 Converts ch into a one-character string containing ch, then invokes
 sb_ConcatStr().
 Returns Same as sb_ConcatStr()
 ********************************************************************/
int sb_ConcatChar(strBufP theStrBuf, char ch)
{
    char s[2];
    s[0] = ch;
    s[1] = '\0';
    return sb_ConcatString(theStrBuf, s);
}

/********************************************************************
 sb_ConcatInt()
 Converts theInt into a string, then invokes sb_ConcatString().
 Returns Same as sb_ConcatString()
 ********************************************************************/
int sb_ConcatInt(strBufP theStrBuf, int theInt)
{
    char numberStr[MAXCHARSFOR32BITINT + 1];

    if (sprintf(numberStr, "%d", theInt) < 1)
        return NOTOK;

    return sb_ConcatString(theStrBuf, numberStr);
}

/********************************************************************
 sb_TakeString()
 Extracts the buffer string from the received string buffer and
 returns it. The string buffer is changed to contain a zero length
 string, so that the buffer can be reused or freed with sb_Free().
 Returns NULL on error or a string to be freed by the caller on success.
 ********************************************************************/
char *sb_TakeString(strBufP theStrBuf)
{
    char *theBuf = NULL;

    if (theStrBuf == NULL)
        return NULL;

    theBuf = theStrBuf->buf;
    theStrBuf->buf = (char *)malloc(sizeof(char));
    theStrBuf->buf[0] = '\0';
    theStrBuf->size = theStrBuf->capacity = 0;

    return theBuf;
}
