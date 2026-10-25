#ifndef GRAPH_K23SEARCH_PRIVATE_H
#define GRAPH_K23SEARCH_PRIVATE_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../planarityRelated/graphOuterplanarity.private.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        // Overloaded function pointers
        graphFunctionTableStruct functions;

    } K23SearchContext;

    extern int K23SEARCH_ID;

#ifdef __cplusplus
}
#endif

#endif
