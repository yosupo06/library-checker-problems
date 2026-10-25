#ifndef GRAPH_EXTENSIONS_PRIVATE_H
#define GRAPH_EXTENSIONS_PRIVATE_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graphFunctionTable.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct graphExtensionStruct
    {
        int moduleID;
        void *context;
        void *(*dupContext)(void *pContext, void *theGraph);
        int  (*copyData)(void *dstContext, void *srcContext);
        void (*freeContext)(void *pContext);

        graphFunctionTableP functions;

        struct graphExtensionStruct *next;
    };

    typedef struct graphExtensionStruct graphExtensionStruct;
    typedef graphExtensionStruct *graphExtensionP;

#ifdef __cplusplus
}
#endif

#endif
