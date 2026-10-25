#ifndef GRAPHFUNCTIONTABLE_H
#define GRAPHFUNCTIONTABLE_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     NOTE: If you add any FUNCTION POINTERS to this function table, then you must
           also initialize them in _InitFunctionTable() in graph.c.
    */
    typedef struct graphStruct graphStruct;
    typedef graphStruct *graphP;

    struct graphFunctionTableStruct
    {
        // These function pointers allow extension modules to overload some of
        // the behaviors of protected functions.  Only advanced applications
        // will overload these functions
        int (*fpEmbeddingInitialize)(graphP theGraph);
        void (*fpEmbedBackEdgeToDescendant)(graphP theGraph, int RootSide, int RootVertex, int W, int WPrevLink);
        void (*fpWalkUp)(graphP theGraph, int v, int e);
        int (*fpWalkDown)(graphP theGraph, int v, int RootVertex);
        int (*fpMergeBicomps)(graphP theGraph, int v, int RootVertex, int W, int WPrevLink);
        void (*fpMergeVertex)(graphP theGraph, int W, int WPrevLink, int R);
        int (*fpHandleInactiveVertex)(graphP theGraph, int BicompRoot, int *pW, int *pWPrevLink);
        int (*fpHandleBlockedBicomp)(graphP theGraph, int v, int RootVertex, int R);
        int (*fpEmbedPostprocess)(graphP theGraph, int v, int edgeEmbeddingResult);
        int (*fpMarkDFSPath)(graphP theGraph, int ancestor, int descendant);

        int (*fpCheckEmbeddingIntegrity)(graphP theGraph, graphP origGraph);
        int (*fpCheckObstructionIntegrity)(graphP theGraph, graphP origGraph);

        // These function pointers allow extension modules to overload some
        // of the behaviors of gp_* function in the public API
        int (*fpEnsureVertexCapacity)(graphP theGraph, int N);
        void (*fpResetGraphStorage)(graphP theGraph);
        int (*fpEnsureEdgeCapacity)(graphP theGraph, int requiredEdgeCapacity);
        int (*fpSortVertices)(graphP theGraph);

        int (*fpReadPostprocess)(graphP theGraph, char *extraData);
        int (*fpWritePostprocess)(graphP theGraph, char **pExtraData);

        int (*fpDeleteEdge)(graphP theGraph, int e);
        void (*fpHideEdge)(graphP theGraph, int e);
        void (*fpRestoreEdge)(graphP theGraph, int e);
        int (*fpHideVertex)(graphP theGraph, int vertex);
        int (*fpRestoreVertex)(graphP theGraph);
        int (*fpContractEdge)(graphP theGraph, int e);
        int (*fpIdentifyVertices)(graphP theGraph, int u, int v, int eBefore);
    };

    typedef struct graphFunctionTableStruct graphFunctionTableStruct;
    typedef graphFunctionTableStruct *graphFunctionTableP;

#ifdef __cplusplus
}
#endif

#endif
