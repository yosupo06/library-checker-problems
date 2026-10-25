/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "appconst.h"
#include "stack.h"
#include <stdlib.h>

stackP sp_New(int capacity)
{
    stackP theStack;

    theStack = (stackP)malloc(sizeof(stackStruct));

    if (theStack != NULL)
    {
        theStack->S = (int *)malloc(capacity * sizeof(int));
        if (theStack->S == NULL)
        {
            free(theStack);
            theStack = NULL;
        }
    }

    if (theStack != NULL)
    {
        theStack->capacity = capacity;
        sp_ClearStack(theStack);
    }

    return theStack;
}

void sp_Free(stackP *pStack)
{
    if (pStack == NULL || *pStack == NULL)
        return;

    (*pStack)->capacity = (*pStack)->size = 0;

    if ((*pStack)->S != NULL)
        free((*pStack)->S);
    (*pStack)->S = NULL;
    free(*pStack);

    *pStack = NULL;
}

int sp_CopyContent(stackP stackDst, stackP stackSrc)
{
    if (stackDst->capacity < stackSrc->size)
        return NOTOK;

    if (stackSrc->size > 0)
        memcpy(stackDst->S, stackSrc->S, stackSrc->size * sizeof(int));

    stackDst->size = stackSrc->size;
    return OK;
}

stackP sp_Duplicate(stackP theStack)
{
    stackP newStack = sp_New(theStack->capacity);

    if (newStack == NULL)
        return NULL;

    if (theStack->size > 0)
    {
        memcpy(newStack->S, theStack->S, theStack->size * sizeof(int));
        newStack->size = theStack->size;
    }

    return newStack;
}

int sp_Copy(stackP stackDst, stackP stackSrc)
{
    if (sp_CopyContent(stackDst, stackSrc) != OK)
    {
        stackP newStack = sp_Duplicate(stackSrc);
        int *p;

        if (newStack == NULL)
            return NOTOK;

        p = stackDst->S;
        stackDst->S = newStack->S;
        newStack->S = p;
        newStack->capacity = stackDst->capacity;
        sp_Free(&newStack);

        stackDst->size = stackSrc->size;
        stackDst->capacity = stackSrc->capacity;
    }

    return OK;
}

#ifndef SPEED_MACROS

int sp_ClearStack(stackP theStack)
{
    theStack->size = 0;
    return OK;
}

int sp_GetCurrentSize(stackP theStack)
{
    return theStack->size;
}

int sp_SetCurrentSize(stackP theStack, int size)
{
    return size > theStack->capacity ? NOTOK : (theStack->size = size, OK);
}

int sp_IsEmpty(stackP theStack)
{
    return !theStack->size;
}

int sp_NonEmpty(stackP theStack)
{
    return theStack->size;
}

int sp__Push(stackP theStack, int a)
{
    if (theStack->size >= theStack->capacity)
        return NOTOK;

    theStack->S[theStack->size++] = a;
    return OK;
}

int sp__Push2(stackP theStack, int a, int b)
{
    if (theStack->size + 1 >= theStack->capacity)
        return NOTOK;

    theStack->S[theStack->size++] = a;
    theStack->S[theStack->size++] = b;
    return OK;
}

int sp__Pop(stackP theStack, int *pA)
{
    if (theStack->size <= 0)
        return NOTOK;

    *pA = theStack->S[--theStack->size];
    return OK;
}

int sp__Pop_Discard(stackP theStack)
{
    if (theStack->size <= 0)
        return NOTOK;

    --theStack->size;
    return OK;
}

int sp__Pop2(stackP theStack, int *pA, int *pB)
{
    if (theStack->size <= 1)
        return NOTOK;

    *pB = theStack->S[--theStack->size];
    *pA = theStack->S[--theStack->size];

    return OK;
}

int sp__Pop2_Discard1(stackP theStack, int *pA)
{
    if (theStack->size <= 1)
        return NOTOK;

    // When a pair of the form (main, secondary) are pushed in order,
    // it is sometimes necessary to pop the secondary and discard,
    // then pop and store the main datum.
    --theStack->size;
    *pA = theStack->S[--theStack->size];

    return OK;
}

int sp__Pop2_Discard(stackP theStack)
{
    if (theStack->size <= 1)
        return NOTOK;

    --theStack->size;
    --theStack->size;

    return OK;
}

int sp_Top(stackP theStack)
{
    return theStack->size ? theStack->S[theStack->size - 1] : NIL;
}

int sp_Get(stackP theStack, int pos)
{
    if (theStack == NULL || pos < 0 || pos >= theStack->size)
        return NOTOK;

    return (theStack->S[pos]);
}

int sp_Set(stackP theStack, int pos, int val)
{
    if (theStack == NULL || pos < 0 || pos >= theStack->size)
        return NOTOK;

    return (theStack->S[pos] = val);
}

#endif // not defined SPEED_MACROS
