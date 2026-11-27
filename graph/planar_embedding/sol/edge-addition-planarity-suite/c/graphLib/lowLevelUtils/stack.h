/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C"
{
#endif

// includes mem functions like memcpy
#include <string.h>

        struct stackStruct
        {
                int *S;
                int size, capacity;
        };

        typedef struct stackStruct stackStruct;
        typedef stackStruct *stackP;

        stackP sp_New(int capacity);
        void sp_Free(stackP *pStack);

        int sp_Copy(stackP stackDst, stackP stackSrc);

        int sp_CopyContent(stackP stackDst, stackP stackSrc);
        stackP sp_Duplicate(stackP theStack);

#define sp_GetCapacity(theStack) (theStack->capacity)

#ifndef SPEED_MACROS

        int sp_ClearStack(stackP theStack);
        int sp_GetCurrentSize(stackP theStack);
        int sp_SetCurrentSize(stackP theStack, int top);

        int sp_IsEmpty(stackP theStack);
        int sp_NonEmpty(stackP theStack);

#define sp_Push(theStack, a)                       \
        {                                          \
                if (sp__Push(theStack, (a)) != OK) \
                        return NOTOK;              \
        }
#define sp_Push2(theStack, a, b)                         \
        {                                                \
                if (sp__Push2(theStack, (a), (b)) != OK) \
                        return NOTOK;                    \
        }

        int sp__Push(stackP theStack, int a);
        int sp__Push2(stackP theStack, int a, int b);

#define sp_Pop(theStack, a)                        \
        {                                          \
                if (sp__Pop(theStack, &(a)) != OK) \
                        return NOTOK;              \
        }
#define sp_Pop_Discard(theStack)                     \
        {                                            \
                if (sp__Pop_Discard(theStack) != OK) \
                        return NOTOK;                \
        }

#define sp_Pop2(theStack, a, b)                           \
        {                                                 \
                if (sp__Pop2(theStack, &(a), &(b)) != OK) \
                        return NOTOK;                     \
        }
#define sp_Pop2_Discard1(theStack, a)                        \
        {                                                    \
                if (sp__Pop2_Discard1(theStack, &(a)) != OK) \
                        return NOTOK;                        \
        }
#define sp_Pop2_Discard(theStack)                     \
        {                                             \
                if (sp__Pop2_Discard(theStack) != OK) \
                        return NOTOK;                 \
        }

        int sp__Pop(stackP theStack, int *pA);
        int sp__Pop_Discard(stackP theStack);

        int sp__Pop2(stackP theStack, int *pA, int *pB);
        int sp__Pop2_Discard1(stackP theStack, int *pA);
        int sp__Pop2_Discard(stackP theStack);

        int sp_Top(stackP theStack);
        int sp_Get(stackP theStack, int pos);
        int sp_Set(stackP theStack, int pos, int val);

#else

#define sp_ClearStack(theStack) theStack->size = 0
#define sp_GetCurrentSize(theStack) (theStack->size)
#define sp_SetCurrentSize(theStack, Size) ((Size) > theStack->capacity ? NOTOK : (theStack->size = (Size), OK))

#define sp_IsEmpty(theStack) !theStack->size
#define sp_NonEmpty(theStack) theStack->size

#define sp_Push(theStack, a) theStack->S[theStack->size++] = a
#define sp_Push2(theStack, a, b)      \
        {                             \
                sp_Push(theStack, a); \
                sp_Push(theStack, b); \
        }

#define sp_Pop(theStack, a) a = theStack->S[--theStack->size]
#define sp_Pop_Discard(theStack) --theStack->size

#define sp_Pop2(theStack, a, b)      \
        {                            \
                sp_Pop(theStack, b); \
                sp_Pop(theStack, a); \
        }
#define sp_Pop2_Discard1(theStack, a)     \
        {                                 \
                sp_Pop_Discard(theStack); \
                sp_Pop(theStack, a);      \
        }
#define sp_Pop2_Discard(theStack)         \
        {                                 \
                sp_Pop_Discard(theStack); \
                sp_Pop_Discard(theStack); \
        }

#define sp_Top(theStack) (theStack->size ? theStack->S[theStack->size - 1] : NIL)
#define sp_Get(theStack, pos) (theStack->S[pos])
#define sp_Set(theStack, pos, val) (theStack->S[pos] = val)

#endif

#ifdef __cplusplus
}
#endif

#endif
