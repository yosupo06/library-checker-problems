/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifndef STRBUF_H
#define STRBUF_H

#ifdef __cplusplus
extern "C"
{
#endif

// includes mem functions like memcpy
#include <string.h>

        typedef struct
        {
                char *buf;
                int size, capacity, readPos;
        } strBuf;

        typedef strBuf *strBufP;

        strBufP sb_New(int capacity);
        void sb_Free(strBufP *pStrBuf);

        void sb_ClearBuf(strBufP theStrBuf);
        int sb_Copy(strBufP strBufDst, strBufP strBufSrc);
        strBufP sb_Duplicate(strBufP theStrBuf);

#define sb_GetFullString(theStrBuf) (theStrBuf->buf)
#define sb_GetSize(theStrBuf) (theStrBuf->size)
#define sb_GetCapacity(theStrBuf) (theStrBuf->capacity)
#define sb_GetUnreadCharCount(theStrBuf) (theStrBuf->size - theStrBuf->readPos)
#define sb_GetReadString(theStrBuf) ((theStrBuf != NULL && theStrBuf->buf != NULL) ? (theStrBuf->buf + theStrBuf->readPos) : NULL)

#define sb_GetReadPos(theStrBuf) (theStrBuf->readPos)
#define sb_SetReadPos(theStrBuf, theReadPos)     \
        {                                        \
                theStrBuf->readPos = theReadPos; \
        }

        void sb_ReadSkipWhitespace(strBufP theStrBuf);
        void sb_ReadSkipInteger(strBufP theStrBuf);
#define sb_ReadSkipChar(theStrBuf)    \
        {                             \
                theStrBuf->readPos++; \
        }

        int sb_ConcatString(strBufP theStrBuf, char const *s);
        int sb_ConcatChar(strBufP theStrBuf, char ch);
        int sb_ConcatInt(strBufP theStrBuf, int value);

        char *sb_TakeString(strBufP theStrBuf);

#ifndef SPEED_MACROS
// Optimized SPEED_MACROS versions of larger methods are not used in this module
#else
// Optimized SPEED_MACROS versions of larger methods are not used in this module
#endif

#ifdef __cplusplus
}
#endif

#endif /* STRBUF_H */
