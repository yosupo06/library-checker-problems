#ifndef GRAPH_EXTENSIONS_H
#define GRAPH_EXTENSIONS_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "../graph.h"

    int gp_AddExtension(graphP theGraph,
                        int *pModuleID,
                        void *context,
                        void *(*dupContext)(void *pContext, void *theGraph),
                        int  (*copyData)(void *dstContext, void *srcContext),
                        void (*freeContext)(void *pContext),
                        graphFunctionTableP overloadTable);

    int gp_FindExtension(graphP theGraph, int moduleID, void **pContext);
    void *gp_GetExtension(graphP theGraph, int moduleID);

    int gp_DupExtensions(graphP dstGraph, graphP srcGraph);
    int gp_CopyExtensions(graphP dstGraph, graphP srcGraph);
    void gp_FreeExtensions(graphP theGraph);

    int gp_RemoveExtension(graphP theGraph, int moduleID);

#ifdef __cplusplus
}
#endif

#endif
