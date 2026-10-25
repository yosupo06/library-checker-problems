/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graph.h"
#include "graph.private.h"

// To enable performing of certain initialization calls for the
// DFSUtils, Planarity, and Outerplanarity pseudo-extensions.
#include "planarityRelated/graphPlanarity.h"
#include "planarityRelated/graphPlanarity.private.h"
#include "planarityRelated/graphOuterplanarity.h"

#include <stdlib.h>

/* Imported functions for FUNCTION POINTERS */

extern int _EmbeddingInitialize(graphP theGraph);
extern int _SortVertices(graphP theGraph);
extern void _EmbedBackEdgeToDescendant(graphP theGraph, int RootSide, int RootVertex, int W, int WPrevLink);
extern void _WalkUp(graphP theGraph, int v, int e);
extern int _WalkDown(graphP theGraph, int v, int RootVertex);
extern int _MergeBicomps(graphP theGraph, int v, int RootVertex, int W, int WPrevLink);
extern void _MergeVertex(graphP theGraph, int W, int WPrevLink, int R);
extern int _HandleBlockedBicomp(graphP theGraph, int v, int RootVertex, int R);
extern int _HandleInactiveVertex(graphP theGraph, int BicompRoot, int *pW, int *pWPrevLink);
extern int _MarkDFSPath(graphP theGraph, int ancestor, int descendant);
extern int _EmbedPostprocess(graphP theGraph, int v, int edgeEmbeddingResult);
extern int _CheckEmbeddingIntegrity(graphP theGraph, graphP origGraph);
extern int _CheckObstructionIntegrity(graphP theGraph, graphP origGraph);
extern int _ReadPostprocess(graphP theGraph, char *extraData);
extern int _WritePostprocess(graphP theGraph, char **pExtraData);

/* Internal util functions for FUNCTION POINTERS */

int _HideVertex(graphP theGraph, int vertex);
void _HideEdge(graphP theGraph, int e);
void _RestoreEdge(graphP theGraph, int e);
int _ContractEdge(graphP theGraph, int e);
int _IdentifyVertices(graphP theGraph, int u, int v, int eBefore);
int _RestoreVertex(graphP theGraph);

/********************************************************************
 Private functions, except exported within library
 ********************************************************************/

void _InitIsolatorContext(graphP theGraph);
void _ClearAllVisitedFlagsInGraph(graphP theGraph);
void _ClearVertexVisitedFlags(graphP theGraph, int includeVirtualVertices);
void _ClearEdgeVisitedFlags(graphP theGraph);
int _ClearAllVisitedFlagsInBicomp(graphP theGraph, int BicompRoot);
int _ClearAllVisitedFlagsInOtherBicomps(graphP theGraph, int BicompRoot);
void _ClearEdgeVisitedFlagsInUnembeddedEdges(graphP theGraph);
int _FillVertexVisitedIndexes(graphP theGraph, int FillValue);
int _FillVertexVisitedIndexesInBicomp(graphP theGraph, int BicompRoot, int FillValue);
int _ClearObstructionMarksInBicomp(graphP theGraph, int BicompRoot);

int _gp_FindEdge(graphP theGraph, int u, int v);

int _ClearAllVisitedFlagsOnPath(graphP theGraph, int u, int v, int w, int x);
int _SetAllVisitedFlagsOnPath(graphP theGraph, int u, int v, int w, int x);

int _ComputeEdgeRecordType(graphP theGraph, int a, int b, int edgeType);
int _RestoreEdgeType(graphP theGraph, int u, int v);

int _HideInternalEdges(graphP theGraph, int vertex);
int _RestoreInternalEdges(graphP theGraph, int stackBottom);
int _RestoreHiddenEdges(graphP theGraph, int stackBottom);

int _GetBicompSize(graphP theGraph, int BicompRoot);
int _DeleteUnmarkedEdgesInBicomp(graphP theGraph, int BicompRoot);
int _ClearInvertedFlagsInBicomp(graphP theGraph, int BicompRoot);

void _InitFunctionTable(graphP theGraph);

/********************************************************************
 Private functions.
 ********************************************************************/

void _InitVertices(graphP theGraph);
void _InitEdges(graphP theGraph);

void _ClearGraph(graphP theGraph);

typedef struct
{
    int u;
    int v;
} randomGraphEdgeRec;

typedef struct
{
    int a;
    int b;
    int c;
} randomGraphFaceRec;

int _AddRandomGraphEdgeCandidate(randomGraphEdgeRec *edgeList, int edgeListCapacity, int *pEdgeListCount, int u, int v);
int _ProcessRandomGraphOptionalEdge(graphP theGraph, randomGraphEdgeRec *edgeList, int edgeListCapacity,
                                    int *pEdgeListCount, int addImmediately, int u, int v);
void _ShuffleRandomGraphEdgeCandidates(randomGraphEdgeRec *edgeList, int edgeCount);

void _AttachEdgeRecord(graphP theGraph, int v, int e, int link, int newEdge);
void _DetachEdgeRecord(graphP theGraph, int e);
void _RestoreEdgeRecord(graphP theGraph, int e);
int _DeleteEdge(graphP theGraph, int e);

/* Private functions for which there are FUNCTION POINTERS */

void _InitVertexRec(graphP theGraph, int v);
void _InitVertexInfo(graphP theGraph, int v);
void _InitEdgeRec(graphP theGraph, int e);

int _EnsureVertexCapacity(graphP theGraph, int N);
void _ResetGraphStorage(graphP theGraph);
int _EnsureEdgeCapacity(graphP theGraph, int requiredEdgeCapacity);

/********************************************************************
 gp_New()
 Constructor for graph object.
 Can create two graphs if restricted to no dynamic memory.
 ********************************************************************/

graphP gp_New(void)
{
    graphP theGraph = (graphP)calloc(1, sizeof(graphStruct));
    graphFunctionTableP functionTable = (graphFunctionTableP)calloc(1, sizeof(graphFunctionTableStruct));
    graphPrivateDataP theGraphPrivateData = (graphPrivateDataP)calloc(1, sizeof(graphPrivateDataStruct));
    graphExtensionP *extensionLookupTable = (graphExtensionP *)calloc(MAXNUMSUPPORTEDEXTENSIONS + 1, sizeof(graphExtensionP));

    if (theGraph != NULL && functionTable != NULL &&
        theGraphPrivateData != NULL && extensionLookupTable != NULL)
    {
        theGraph->privateData = (void *)theGraphPrivateData;
        theGraph->extensionLookupTable = extensionLookupTable;

        theGraph->functions = functionTable;
        _InitFunctionTable(theGraph);

        _ClearGraph(theGraph);
    }
    else
    {
        if (theGraph != NULL)
        {
            free(theGraph);
            theGraph = NULL;
        }
        if (functionTable != NULL)
        {
            free(functionTable);
            functionTable = NULL;
        }
        if (theGraphPrivateData != NULL)
        {
            free(theGraphPrivateData);
            theGraphPrivateData = NULL;
        }
        if (extensionLookupTable != NULL)
        {
            free(extensionLookupTable);
            extensionLookupTable = NULL;
        }
    }

    return theGraph;
}

/********************************************************************
 _InitFunctionTable()

 If you add functions to the function table, then they must be
 initialized here, but you must also add the new function pointer
 to the definition of the graphFunctionTableStruct in graphFunctionTable.h

 Function headers for the functions used to initialize the table are
 classified at the top of this file as either imported from other
 compilation units (extern) or private to this compilation unit.
 Search for FUNCTION POINTERS in this file to see where to add the
 function header.
 ********************************************************************/

void _InitFunctionTable(graphP theGraph)
{
    if (theGraph != NULL && theGraph->functions != NULL)
    {
        theGraph->functions->fpEmbeddingInitialize = _EmbeddingInitialize;
        theGraph->functions->fpEmbedBackEdgeToDescendant = _EmbedBackEdgeToDescendant;
        theGraph->functions->fpWalkUp = _WalkUp;
        theGraph->functions->fpWalkDown = _WalkDown;
        theGraph->functions->fpMergeBicomps = _MergeBicomps;
        theGraph->functions->fpMergeVertex = _MergeVertex;
        theGraph->functions->fpHandleBlockedBicomp = _HandleBlockedBicomp;
        theGraph->functions->fpHandleInactiveVertex = _HandleInactiveVertex;
        theGraph->functions->fpEmbedPostprocess = _EmbedPostprocess;
        theGraph->functions->fpMarkDFSPath = _MarkDFSPath;
        theGraph->functions->fpCheckEmbeddingIntegrity = _CheckEmbeddingIntegrity;
        theGraph->functions->fpCheckObstructionIntegrity = _CheckObstructionIntegrity;

        theGraph->functions->fpEnsureVertexCapacity = _EnsureVertexCapacity;
        theGraph->functions->fpResetGraphStorage = _ResetGraphStorage;
        theGraph->functions->fpEnsureEdgeCapacity = _EnsureEdgeCapacity;
        theGraph->functions->fpSortVertices = _SortVertices;

        theGraph->functions->fpReadPostprocess = _ReadPostprocess;
        theGraph->functions->fpWritePostprocess = _WritePostprocess;

        theGraph->functions->fpDeleteEdge = _DeleteEdge;
        theGraph->functions->fpHideEdge = _HideEdge;
        theGraph->functions->fpRestoreEdge = _RestoreEdge;
        theGraph->functions->fpHideVertex = _HideVertex;
        theGraph->functions->fpRestoreVertex = _RestoreVertex;
        theGraph->functions->fpContractEdge = _ContractEdge;
        theGraph->functions->fpIdentifyVertices = _IdentifyVertices;
    }
}

/********************************************************************
 gp_EnsureVertexCapacity()

 Allocates memory for N vertices and N virtual vertices. Once N > 0
 vertices have been allocated, this method currently does not support
 being called a second time to add more vertices.

 This method will also ensure that the edge capacity is allocated or
 reallocated to be at least (DEFAULT_EDGE_CAPACITY_FACTOR * N), i.e.,
 a capacity for twice that many edge records, two per edge (plus 2
 for the default of using one-based arrays). The edge capacity can
 be set before this function using gp_EnsureEdgeCapacity().

 The edgeHoles stack, initially empty, is set to the edgeCapacity,
     which is big enough to push every edge (to indicate an edge,
     only one of its two edge records need be pushed).

 The numEdgeHoles is set to 0; it tracks the edgeHoles stack size,
    so the number of edge records in use can be efficiently computed.

 The stack, initially empty, is made big enough for a pair of integers
     per edge (2 * edgeCapacity), or 6N integers if the edgeCapacity
     was set below the default. Space for 2 extra integers is added so
     depth-first search can push (NIL, NIL) to start at a DFS tree root.

 The BicompRootLists and sortedDFSChildLists are set to a size of N,
     and they start out empty.

 DVI and PVI are set to store N of their respective vertex info records.

 An instance of the isolator context is created.

 Returns OK on success, NOTOK on any failure.
          On NOTOK, graph extensions are freed so that the graph is
          returned to the post-condition of gp_New().
 ********************************************************************/

int gp_EnsureVertexCapacity(graphP theGraph, int N)
{
    long long effectiveEdgeCapacity = 0;

    // valid params check
    if (theGraph == NULL || N <= 0)
        return NOTOK;

    // Should not call init a second time; use reinit
    if (gp_GetN(theGraph) > 0)
        return NOTOK;

    // Reject a vertex count whose capacity arithmetic cannot be represented
    // in int (issue #325). The effective edge capacity is the greater of a
    // pre-set edgeCapacity and DEFAULT_EDGE_CAPACITY_FACTOR * N, because
    // gp_EnsureEdgeCapacity() may legitimately have stored a lower value
    // before this call. The stack holds (edgeCapacity << 2) + 2 entries,
    // which strictly exceeds every other derived quantity (vertex storage,
    // edge storage and the 2 * 2 * DEFAULT_EDGE_CAPACITY_FACTOR * N + 2
    // fallback), so one test on it shields them all, including the
    // gp_UpperBoundEdgeStorage() uses in the algorithm extensions.
    effectiveEdgeCapacity = (long long)DEFAULT_EDGE_CAPACITY_FACTOR * N;
    if (effectiveEdgeCapacity < theGraph->edgeCapacity)
        effectiveEdgeCapacity = theGraph->edgeCapacity;
    if ((effectiveEdgeCapacity << 2) + 2 > INT_MAX)
        return NOTOK;

    return theGraph->functions->fpEnsureVertexCapacity(theGraph, N);
}

int _EnsureVertexCapacity(graphP theGraph, int N)
{
    int Vsize, VIsize, Esize, stackSize;

    // Compute the vertex and edge capacities of the graph
    theGraph->N = N;
    theGraph->NV = N;
    theGraph->edgeCapacity = theGraph->edgeCapacity > 0 ? theGraph->edgeCapacity : DEFAULT_EDGE_CAPACITY_FACTOR * N;
    theGraph->numEdgeHoles = 0;

    VIsize = gp_UpperBoundVertices(theGraph);
    Vsize = gp_UpperBoundVertexStorage(theGraph);
    Esize = gp_UpperBoundEdgeStorage(theGraph);

    // Stack size is 2 integers per edge record plus 2 to start depth-first search at a tree root
    stackSize = (theGraph->edgeCapacity << 2) + 2;
    // In case of small edgeCapacity, ensure minimum based on number of vertices
    stackSize = stackSize <= 2 * 2 * DEFAULT_EDGE_CAPACITY_FACTOR * N ? 2 * 2 * DEFAULT_EDGE_CAPACITY_FACTOR * N + 2 : stackSize;

    // Allocate memory as described above
    if ((theGraph->V = (vertexRecP)calloc(Vsize, sizeof(vertexRec))) == NULL ||
        (theGraph->E = (edgeRecP)calloc(Esize, sizeof(edgeRec))) == NULL ||
        (theGraph->edgeHoles = sp_New(theGraph->edgeCapacity)) == NULL ||

        (theGraph->theStack = sp_New(stackSize)) == NULL ||
        (theGraphBicompRootLists(theGraph) = LCNew(VIsize)) == NULL ||
        (theGraphDVI(theGraph) = (DFSUtils_VertexInfoP)calloc(VIsize, sizeof(DFSUtils_VertexInfo))) == NULL ||

        (theGraphPVI(theGraph) = (Planarity_VertexInfoP)calloc(VIsize, sizeof(Planarity_VertexInfo))) == NULL ||
        (theGraphSortedDFSChildLists(theGraph) = LCNew(VIsize)) == NULL ||
        (theGraphExtFace(theGraph) = (extFaceLinkRecP)calloc(Vsize, sizeof(extFaceLinkRec))) == NULL ||
        (theGraphIC(theGraph) = (isolatorContextP)calloc(1, sizeof(isolatorContextStruct))) == NULL ||
        0)
    {
        _ClearGraph(theGraph);
        return NOTOK;
    }

    // Initialize memory
    _InitVertices(theGraph);
    _InitEdges(theGraph);
    _InitIsolatorContext(theGraph);

    return OK;
}

/********************************************************************
 _InitVertices()
 ********************************************************************/
void _InitVertices(graphP theGraph)
{
    memset(theGraph->V, NIL_CHAR, gp_UpperBoundVertexStorage(theGraph) * sizeof(vertexRec));

    memset(theGraphDVI(theGraph), NIL_CHAR, gp_UpperBoundVertices(theGraph) * sizeof(DFSUtils_VertexInfo));

    memset(theGraphPVI(theGraph), NIL_CHAR, gp_UpperBoundVertices(theGraph) * sizeof(Planarity_VertexInfo));
    memset(theGraphExtFace(theGraph), NIL_CHAR, gp_UpperBoundVertexStorage(theGraph) * sizeof(extFaceLinkRec));

#ifdef USE_1BASEDARRAYS
// For 1-based arrays, the memset() initializes the flags correctly
#else
    for (int v = gp_LowerBoundVertexStorage(theGraph); v < gp_UpperBoundVertexStorage(theGraph); ++v)
        gp_InitFlags(theGraph, v);
#endif
}

/********************************************************************
 _InitEdges()
 ********************************************************************/
void _InitEdges(graphP theGraph)
{
    memset(theGraph->E, NIL_CHAR, gp_UpperBoundEdgeStorage(theGraph) * sizeof(edgeRec));

#ifdef USE_1BASEDARRAYS
#else
    for (int e = gp_LowerBoundEdgeStorage(theGraph); e < gp_UpperBoundEdgeStorage(theGraph); ++e)
        gp_InitEdgeFlags(theGraph, e);
#endif
}

/********************************************************************
 gp_ResetGraphStorage()
 Resets the graph to the state immediately after processing by
 gp_EnsureVertexCapacity().
 ********************************************************************/

void gp_ResetGraphStorage(graphP theGraph)
{
    if (theGraph == NULL || gp_GetN(theGraph) <= 0)
        return;

    theGraph->functions->fpResetGraphStorage(theGraph);
}

void _ResetGraphStorage(graphP theGraph)
{
    theGraph->M = 0;
    theGraph->embedFlags = 0;

    theGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED;
    theGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED_DIRECTED;
    theGraph->graphFlags &= ~GRAPHFLAGS_SORTEDBYDFI;
    theGraph->graphFlags &= ~GRAPHFLAGS_LOWPOINTSCOMPUTED;
    theGraph->graphFlags &= ~GRAPHFLAGS_DIRECTEDEDGEDETECTED;
    _InitVertices(theGraph);
    _InitEdges(theGraph);
    _InitIsolatorContext(theGraph);

    LCReset(theGraphBicompRootLists(theGraph));
    LCReset(theGraphSortedDFSChildLists(theGraph));
    sp_ClearStack(theGraph->theStack);
    sp_ClearStack(theGraph->edgeHoles);
    theGraph->numEdgeHoles = 0;
}

/********************************************************************
 gp_EnsureEdgeCapacity()

 This method ensures that theGraph is or will be capable of storing
 at least requiredEdgeCapacity edge records.  Two edge records are
 needed per edge.

 This method is most performant when invoked immediately after
 gp_New(), since it must only set the edgeCapacity and then let
 normal processing by gp_EnsureVertexCapacity() occur.

 This method is also a constant time operation if the graph already
 has at least the requiredEdgeCapacity, since it will return OK
 without making any structural changes.

 This method is generally more performant if it is invoked before
 attaching extensions to the graph.  Some extensions associate
 parallel data with edge records, which is a faster operation if
 the associated data storage is created and initialized only after
 the proper edgeCapacity is specified.

 The array of edge records is allocated or reallocated to
 satisfy the requiredEdgeCapacity.  The new array contains the
 old edges and edge holes, if any, at the same locations. All
 newly created edge records are initialized.

 Also, if the edge capacity was lower than required, then the
 edgeCapacity member of theGraph is increased and both
 theStack and the edgeHoles are expanded (since the sizes of both
 are based on the edge capacity).

 Extensions that add to data associated with edges must overload
 this method to ensure the reqquired capacity in the parallel
 extension data structures.

 Returns NOTOK on failure to reallocate the edge record array to
         satisfy the requiredEdgeCapacity
         OK if reallocation succeeds or is not required
 ********************************************************************/
int gp_EnsureEdgeCapacity(graphP theGraph, int requiredEdgeCapacity)
{
    if (theGraph == NULL || requiredEdgeCapacity <= 0)
        return NOTOK;

    // Reject a capacity whose stack arithmetic cannot be represented in int
    // (issue #325). Together with the guard in gp_EnsureVertexCapacity(),
    // this keeps every stored capacity able to support its stack and edge
    // storage arithmetic: the vertex-side guard covers the derived
    // quantities computed from N, and this test covers the ones computed
    // from a stored or requested capacity
    if ((((long long)requiredEdgeCapacity) << 2) + 2 > INT_MAX)
        return NOTOK;

    if (theGraph->edgeCapacity >= requiredEdgeCapacity)
        return OK;

    // In the special case where gp_EnsureVertexCapacity() has not yet
    // been called, we can simply set the higher edgeCapacity since normal
    // behavior of gp_EnsureVertexCapacity() will then allocate the
    // correct number of edge records.
    if (gp_GetN(theGraph) == 0)
    {
        theGraph->edgeCapacity = requiredEdgeCapacity;
        return OK;
    }

    // Try to expand the edge capacity
    return theGraph->functions->fpEnsureEdgeCapacity(theGraph, requiredEdgeCapacity);
}

int _EnsureEdgeCapacity(graphP theGraph, int requiredEdgeCapacity)
{
    stackP newStack = NULL;
    int newEsize = gp_LowerBoundEdgeStorage(theGraph) + (requiredEdgeCapacity << 1);

    // If the new size is less than or equal to the current edge storage size,
    // then the graph already has the required edge capacity
    if (newEsize <= gp_UpperBoundEdgeStorage(theGraph))
        return OK;

    // Expand theStack. Depth-first search needs 2 integers per edge record
    // (2 edge records per edge), plus 2 to start the DFS on a tree root
    //
    if (sp_GetCapacity(theGraph->theStack) < 2 * (2 * requiredEdgeCapacity) + 2)
    {
        int newStackSize = 2 * (2 * requiredEdgeCapacity) + 2;

        if (newStackSize < 2 * (2 * DEFAULT_EDGE_CAPACITY_FACTOR * gp_GetN(theGraph)) + 2)
        {
            // NOTE: We enforce a minimum stack based on number of vertices
            //       if edgeCapacity is small. Currently, this will not
            //       happen because we only 'ensure' edge capacity, i.e.,
            //       the capacity can only ever get bigger. However, this
            //       rule is enforced in case future methods are added
            //       that reduce edge capacity
            newStackSize = 2 * (2 * DEFAULT_EDGE_CAPACITY_FACTOR * gp_GetN(theGraph)) + 2;
        }

        if ((newStack = sp_New(newStackSize)) == NULL)
            return NOTOK;

        sp_CopyContent(newStack, theGraph->theStack);
        sp_Free(&theGraph->theStack);
        theGraph->theStack = newStack;
    }

    // Expand edgeHoles (at most, every edge is a hole if all edges deleted)
    if ((newStack = sp_New(requiredEdgeCapacity)) == NULL)
    {
        return NOTOK;
    }

    sp_CopyContent(newStack, theGraph->edgeHoles);
    sp_Free(&theGraph->edgeHoles);
    theGraph->edgeHoles = newStack;
    theGraph->numEdgeHoles = sp_GetCurrentSize(theGraph->edgeHoles);

    // Reallocate the edgeRec array to the new size,
    theGraph->E = (edgeRecP)realloc(theGraph->E, newEsize * sizeof(edgeRec));
    if (theGraph->E == NULL)
        return NOTOK;

    // Initialize the new edge records
    for (int e = gp_UpperBoundEdgeStorage(theGraph); e < newEsize; ++e)
        _InitEdgeRec(theGraph, e);

    // The new edgeCapacity has been successfully allocated
    theGraph->edgeCapacity = requiredEdgeCapacity;
    return OK;
}

/********************************************************************
 _InitVertexRec()
 Sets the fields in a single vertex record to initial values
 ********************************************************************/

void _InitVertexRec(graphP theGraph, int v)
{
    gp_SetFirstEdge(theGraph, v, NIL);
    gp_SetLastEdge(theGraph, v, NIL);
    gp_SetIndex(theGraph, v, NIL);
    gp_InitFlags(theGraph, v);
}

/********************************************************************
 _InitVertexInfo()
 Sets the fields in a single vertex record to initial values
 ********************************************************************/

void _InitVertexInfo(graphP theGraph, int v)
{
    gp_SetVertexParent(theGraph, v, NIL);
    gp_SetVertexLeastAncestor(theGraph, v, NIL);
    gp_SetVertexLowpoint(theGraph, v, NIL);

    gp_SetVertexVisitedIndex(theGraph, v, NIL);
    gp_SetVertexPertinentEdge(theGraph, v, NIL);
    gp_SetVertexPertinentRootsList(theGraph, v, NIL);
    gp_SetVertexFuturePertinentChild(theGraph, v, NIL);
    gp_SetVertexSortedDFSChildList(theGraph, v, NIL);
    gp_SetVertexFwdEdgeList(theGraph, v, NIL);
}

/********************************************************************
 _InitEdgeRec()
 Sets the fields in a single edge record structure to initial values
 ********************************************************************/

void _InitEdgeRec(graphP theGraph, int e)
{
    gp_SetNeighbor(theGraph, e, NIL);
    gp_SetPrevEdge(theGraph, e, NIL);
    gp_SetNextEdge(theGraph, e, NIL);
    gp_InitEdgeFlags(theGraph, e);
}

/********************************************************************
 _InitIsolatorContext()
 ********************************************************************/

void _InitIsolatorContext(graphP theGraph)
{
    isolatorContextP IC = theGraphIC(theGraph);

    if (IC != NULL)
    {
        IC->minorType = MINORTYPE_NONE;
        IC->v = IC->r = IC->x = IC->y = IC->w = IC->px = IC->py = IC->z =
            IC->ux = IC->dx = IC->uy = IC->dy = IC->dw = IC->uz = IC->dz = NIL;
    }
}

/********************************************************************
 _ClearAllVisitedFlagsInGraph()
 ********************************************************************/

void _ClearAllVisitedFlagsInGraph(graphP theGraph)
{
    _ClearVertexVisitedFlags(theGraph, TRUE);
    _ClearEdgeVisitedFlags(theGraph);
}

/********************************************************************
 _ClearVertexVisitedFlags()
 Clears the visited flags of vertices, and if the second parameter
 is truthy, also clears the visited flags of virtual vertices.
 ********************************************************************/

void _ClearVertexVisitedFlags(graphP theGraph, int includeVirtualVertices)
{
    for (int v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
        gp_ClearVisited(theGraph, v);

    if (includeVirtualVertices)
        for (int vv = gp_LowerBoundVirtualVertices(theGraph); vv < gp_UpperBoundVirtualVertices(theGraph); ++vv)
            gp_ClearVisited(theGraph, vv);
}

/********************************************************************
 _ClearEdgeVisitedFlags()
 ********************************************************************/

void _ClearEdgeVisitedFlags(graphP theGraph)
{
    for (int e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); ++e)
        gp_ClearEdgeVisited(theGraph, e);
}

/********************************************************************
 _ClearAllVisitedFlagsInBicomp()

 Clears the visited flag of the vertices and edge records in the
 bicomp rooted by BicompRoot.

 This method uses the stack but preserves whatever may have been
 on it.  In debug mode, it will return NOTOK if the stack overflows.
 This method pushes at most one integer per vertex in the bicomp.

 Returns OK on success, NOTOK on implementation failure.
 ********************************************************************/

int _ClearAllVisitedFlagsInBicomp(graphP theGraph, int BicompRoot)
{
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);
    int v, e;

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, v);
        gp_ClearVisited(theGraph, v);

        e = gp_GetFirstEdge(theGraph, v);
        while (gp_IsEdge(theGraph, e))
        {
            gp_ClearEdgeVisited(theGraph, e);

            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));

            e = gp_GetNextEdge(theGraph, e);
        }
    }
    return OK;
}

/********************************************************************
 _ClearAllVisitedFlagsInOtherBicomps()
 Typically, we want to clear all visited flags in the graph
 (see _ClearVisitedFlags).  However, in some algorithms this would be
 too costly, so it is necessary to clear the visited flags only
 in one bicomp (see _ClearAllVisitedFlagsInBicomp), then do some processing
 that sets some of the flags then performs some tests.  If the tests
 are positive, then we can clear all the visited flags in the
 other bicomps (the processing may have set the visited flags in the
 one bicomp in a particular way that we want to retain, so we skip
 the given bicomp).
 ********************************************************************/

int _ClearAllVisitedFlagsInOtherBicomps(graphP theGraph, int BicompRoot)
{
    int R;

    for (R = gp_LowerBoundVirtualVertices(theGraph); R < gp_UpperBoundVirtualVertices(theGraph); ++R)
    {
        if (R != BicompRoot && gp_VirtualVertexInUse(theGraph, R))
        {
            if (_ClearAllVisitedFlagsInBicomp(theGraph, R) != OK)
                return NOTOK;
        }
    }
    return OK;
}

/********************************************************************
 _ClearEdgeVisitedFlagsInUnembeddedEdges()
 Unembedded edges aren't part of any bicomp yet, but it may be
 necessary to clear their visited flags.
 ********************************************************************/

void _ClearEdgeVisitedFlagsInUnembeddedEdges(graphP theGraph)
{
    int v, e;

    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        e = gp_GetVertexFwdEdgeList(theGraph, v);
        while (gp_IsEdge(theGraph, e))
        {
            gp_ClearEdgeVisited(theGraph, e);
            gp_ClearEdgeVisited(theGraph, gp_GetTwin(theGraph, e));

            e = gp_GetNextEdge(theGraph, e);
            if (e == gp_GetVertexFwdEdgeList(theGraph, v))
                e = NIL;
        }
    }
}

/****************************************************************************
 _ClearAllVisitedFlagsOnPath()
 This method clears the visited flags on the vertices and edges on the path
 (u, v, ..., w, x) in which all vertices except the endpoints u and x
 are degree 2.  This method avoids performing more than constant work at the
 path endpoints u and x, so the total work is on the order of the path length.

 Returns OK on success, NOTOK on internal failure
 ****************************************************************************/

int _ClearAllVisitedFlagsOnPath(graphP theGraph, int u, int v, int w, int x)
{
    int e, eTwin;

    // Suppresses an unused-parameter warning for a parameter we intend to keep
    (void)w;

    // We want to exit u from e, but we get eTwin first here in order to avoid
    // work, in case the degree of u is greater than 2.
    eTwin = _gp_FindEdge(theGraph, v, u);
    if (gp_IsNotEdge(theGraph, eTwin))
        return NOTOK;
    e = gp_GetTwin(theGraph, eTwin);

    v = u;

    do
    {
        // Mark the vertex and the exiting edge
        gp_ClearVisited(theGraph, v);
        gp_ClearEdgeVisited(theGraph, e);
        gp_ClearEdgeVisited(theGraph, eTwin);

        // Get the next vertex
        v = gp_GetNeighbor(theGraph, e);
        e = gp_GetNextEdgeCircular(theGraph, eTwin);
        eTwin = gp_GetTwin(theGraph, e);
    } while (v != x);

    // Mark the last vertex with 'visited'
    gp_ClearVisited(theGraph, x);

    return OK;
}

/****************************************************************************
 _SetAllVisitedFlagsOnPath()
 This method sets the visited flags on the vertices and edges on the path
 (u, v, ..., w, x) in which all vertices except the endpoints u and x
 are degree 2.  This method avoids performing more than constant work at the
 path endpoints u and x, so the total work is on the order of the path length.

 Returns OK on success, NOTOK on internal failure
 ****************************************************************************/

int _SetAllVisitedFlagsOnPath(graphP theGraph, int u, int v, int w, int x)
{
    int e, eTwin;

    // Suppresses an unused-parameter warning for a parameter we intend to keep
    (void)w;

    // We want to exit u from e, but we get eTwin first here in order to avoid
    // work, in case the degree of u is greater than 2.
    eTwin = _gp_FindEdge(theGraph, v, u);
    if (gp_IsNotEdge(theGraph, eTwin))
        return NOTOK;
    e = gp_GetTwin(theGraph, eTwin);

    v = u;

    do
    {
        // Mark the vertex and the exiting edge
        gp_SetVisited(theGraph, v);
        gp_SetEdgeVisited(theGraph, e);
        gp_SetEdgeVisited(theGraph, eTwin);

        // Get the next vertex
        v = gp_GetNeighbor(theGraph, e);
        e = gp_GetNextEdgeCircular(theGraph, eTwin);
        eTwin = gp_GetTwin(theGraph, e);
    } while (v != x);

    // Mark the last vertex with 'visited'
    gp_SetVisited(theGraph, x);

    return OK;
}

/********************************************************************
 _FillVertexVisitedIndexes()

 Places the FillValue into the visitedIndex of all non-virtual vertices
 in the graph.

 Returns OK on success, NOTOK on failure.
 ********************************************************************/

int _FillVertexVisitedIndexes(graphP theGraph, int FillValue)
{
    if (theGraph == NULL)
        return NOTOK;

    for (int v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
        gp_SetVertexVisitedIndex(theGraph, v, FillValue);

    return OK;
}

/********************************************************************
 _FillVertexVisitedIndexesInBicomp()

 Places the FillValue into the visitedIndex of the non-virtual vertices
 in the bicomp rooted by BicompRoot.

 This method uses the stack but preserves whatever may have been
 on it.  In debug mode, it will return NOTOK if the stack overflows.
 This method pushes at most one integer per vertex in the bicomp.

 Returns OK on success, NOTOK on implementation failure.
 ********************************************************************/

int _FillVertexVisitedIndexesInBicomp(graphP theGraph, int BicompRoot, int FillValue)
{
    int v, e;
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, v);

        if (gp_IsNotVirtualVertex(theGraph, v))
            gp_SetVertexVisitedIndex(theGraph, v, FillValue);

        e = gp_GetFirstEdge(theGraph, v);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));

            e = gp_GetNextEdge(theGraph, e);
        }
    }
    return OK;
}

/********************************************************************
 _ClearObstructionMarksInBicomp()

 Clears the 'obstruction type' bits for each vertex in the bicomp
 rooted by BicompRoot.

 This method uses the stack but preserves whatever may have been
 on it.  In debug mode, it will return NOTOK if the stack overflows.
 This method pushes at most one integer per vertex in the bicomp.

 Returns OK on success, NOTOK on implementation failure.
 ********************************************************************/

int _ClearObstructionMarksInBicomp(graphP theGraph, int BicompRoot)
{
    int V, e;
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, V);
        gp_ClearObstructionMark(theGraph, V);

        e = gp_GetFirstEdge(theGraph, V);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));

            e = gp_GetNextEdge(theGraph, e);
        }
    }
    return OK;
}

/********************************************************************
 _ClearGraph()
 Clears all memory used by the graph, restoring it to the state it
 was in immediately after gp_New() created it.
 ********************************************************************/

void _ClearGraph(graphP theGraph)
{
    if (theGraph->V != NULL)
    {
        free(theGraph->V);
        theGraph->V = NULL;
    }
    if (theGraph->E != NULL)
    {
        free(theGraph->E);
        theGraph->E = NULL;
    }

    theGraph->N = 0;
    theGraph->NV = 0;
    theGraph->M = 0;
    theGraph->edgeCapacity = 0;
    theGraph->embedFlags = 0;

    sp_Free(&theGraph->edgeHoles);
    theGraph->numEdgeHoles = 0;

    sp_Free(&theGraph->theStack);
    LCFree(&theGraphBicompRootLists(theGraph));
    if (theGraphDVI(theGraph) != NULL)
    {
        free(theGraphDVI(theGraph));
        theGraphDVI(theGraph) = NULL;
    }

    if (theGraphPVI(theGraph) != NULL)
    {
        free(theGraphPVI(theGraph));
        theGraphPVI(theGraph) = NULL;
    }
    LCFree(&theGraphSortedDFSChildLists(theGraph));
    if (theGraphExtFace(theGraph) != NULL)
    {
        free(theGraphExtFace(theGraph));
        theGraphExtFace(theGraph) = NULL;
    }
    if (theGraphIC(theGraph) != NULL)
    {
        free(theGraphIC(theGraph));
        theGraphIC(theGraph) = NULL;
    }

    gp_FreeExtensions(theGraph);

    // Free the pseudo-extensions
    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY)
        gp_Detach_Outerplanarity(theGraph);

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_PLANARITY)
        gp_Detach_Planarity(theGraph);

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_DFSUTILS)
        gp_Detach_DFSUtils(theGraph);

    theGraph->graphFlags = 0;
}

/********************************************************************
 gp_Free()
 Frees G and V, then the graph record. Then sets the caller's graph
 pointer to NULL (caller must pass the address of a graphP variable).
 ********************************************************************/

void gp_Free(graphP *pGraph)
{
    if (pGraph == NULL)
        return;
    if (*pGraph == NULL)
        return;

    _ClearGraph(*pGraph);

    if ((*pGraph)->functions != NULL)
    {
        free((*pGraph)->functions);
        (*pGraph)->functions = NULL;
    }

    if ((*pGraph)->privateData != NULL)
    {
        free((*pGraph)->privateData);
        (*pGraph)->privateData = NULL;
    }
    if ((*pGraph)->extensionLookupTable != NULL)
    {
        free((*pGraph)->extensionLookupTable);
        (*pGraph)->extensionLookupTable = NULL;
    }

    free(*pGraph);
    *pGraph = NULL;
}

/********************************************************************
 gp_CopyAdjacencyLists()
 Copies the adjacency lists from the srcGraph to the dstGraph.
 This method intentionally copies only the adjacency lists of the
 first N vertices, so the adjacency lists of virtual vertices are
 excluded (unless the caller temporarily resets the value of N to
 include NV).

 Returns OK on success, NOTOK on failures, e.g. if the two graphs
 have different orders N or if the edgeCapacity of dstGraph cannot
 be made to be at least that of srcGraph.
 ********************************************************************/
int gp_CopyAdjacencyLists(graphP dstGraph, graphP srcGraph)
{
    int v, e;

    if (dstGraph == NULL || srcGraph == NULL)
        return NOTOK;

    if (gp_GetN(dstGraph) != gp_GetN(srcGraph) || gp_GetN(dstGraph) == 0)
        return NOTOK;

    if (gp_EnsureEdgeCapacity(dstGraph, srcGraph->edgeCapacity) != OK)
        return NOTOK;

    // Copy the links that hook each owning vertex to its adjacency list
    for (v = gp_LowerBoundVertices(srcGraph); v < gp_UpperBoundVertices(srcGraph); ++v)
    {
        gp_SetFirstEdge(dstGraph, v, gp_GetFirstEdge(srcGraph, v));
        gp_SetLastEdge(dstGraph, v, gp_GetLastEdge(srcGraph, v));
    }

    // Copy the adjacency links and neighbor pointers for each edge record
    for (e = gp_LowerBoundEdges(srcGraph); e < gp_UpperBoundEdges(srcGraph); ++e)
    {
        gp_SetNeighbor(dstGraph, e, gp_GetNeighbor(srcGraph, e));
        gp_SetNextEdge(dstGraph, e, gp_GetNextEdge(srcGraph, e));
        gp_SetPrevEdge(dstGraph, e, gp_GetPrevEdge(srcGraph, e));
    }

    // Tell the dstGraph how many edges it now has and where the edge holes are
    dstGraph->M = gp_GetM(srcGraph);
    sp_Copy(dstGraph->edgeHoles, srcGraph->edgeHoles);
    dstGraph->numEdgeHoles = sp_GetCurrentSize(dstGraph->edgeHoles);

    dstGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED;
    dstGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED_DIRECTED;
    dstGraph->graphFlags &= ~GRAPHFLAGS_SORTEDBYDFI;
    dstGraph->graphFlags &= ~GRAPHFLAGS_LOWPOINTSCOMPUTED;
    dstGraph->graphFlags &= ~GRAPHFLAGS_DIRECTEDEDGEDETECTED;
    if (gp_GetGraphFlags(srcGraph) & GRAPHFLAGS_DIRECTEDEDGEDETECTED)
        dstGraph->graphFlags |= GRAPHFLAGS_DIRECTEDEDGEDETECTED;

    return OK;
}

/********************************************************************
 gp_CopyGraph()

 Copies the content of the srcGraph into the dstGraph.

 The dstGraph must have been previously initialized with the same
 number of vertices as the srcGraph.

 NOTE: If the dstGraph has a higher edge capacity than the srcGraph,
 then this call will fail unless the caller first ensures that the
 edge capacity of the srcGraph is increased to match the dstGraph.

 Returns OK for success, NOTOK for failure.
 ********************************************************************/

// Give macro names to three copy operations
#define _gp_CopyVertexRec(dstGraph, vdst, srcGraph, vsrc) (dstGraph->V[vdst] = srcGraph->V[vsrc])
#define _gp_CopyDFSUtilsVertexInfo(dstGraph, dstI, srcGraph, srcI) (theGraphDVI(dstGraph)[dstI] = theGraphDVI(srcGraph)[srcI])
#define _gp_CopyPlanarityVertexInfo(dstGraph, dstI, srcGraph, srcI) (theGraphPVI(dstGraph)[dstI] = theGraphPVI(srcGraph)[srcI])
#define _gp_CopyEdgeRec(dstGraph, edst, srcGraph, esrc) (dstGraph->E[edst] = srcGraph->E[esrc])

int gp_CopyGraph(graphP dstGraph, graphP srcGraph)
{
    int v, e;

    // Parameter checks
    if (dstGraph == NULL || srcGraph == NULL)
    {
        return NOTOK;
    }

    // The graphs need to be the same order and initialized
    if (gp_GetN(dstGraph) != gp_GetN(srcGraph) || gp_GetN(dstGraph) == 0)
    {
        return NOTOK;
    }

    // Ensure dstGraph has the required edge capacity; this expands
    // dstGraph if needed, but does not contract.  An error is only
    // returned if the expansion fails.
    if (gp_EnsureEdgeCapacity(dstGraph, srcGraph->edgeCapacity) != OK)
    {
        return NOTOK;
    }

    // Copy the vertices (non-virtual only).  Augmentations to vertices created
    // by extensions are copied below by gp_CopyExtensions()
    for (v = gp_LowerBoundVertices(srcGraph); v < gp_UpperBoundVertices(srcGraph); ++v)
    {
        _gp_CopyVertexRec(dstGraph, v, srcGraph, v);
        if (theGraphDVI(dstGraph) != NULL && theGraphDVI(srcGraph) != NULL)
            _gp_CopyDFSUtilsVertexInfo(dstGraph, v, srcGraph, v);
        if (theGraphPVI(dstGraph) != NULL && theGraphPVI(srcGraph) != NULL)
            _gp_CopyPlanarityVertexInfo(dstGraph, v, srcGraph, v);
        gp_SetExtFaceVertex(dstGraph, v, 0, gp_GetExtFaceVertex(srcGraph, v, 0));
        gp_SetExtFaceVertex(dstGraph, v, 1, gp_GetExtFaceVertex(srcGraph, v, 1));
    }

    // Copy the virtual vertices.  Augmentations to virtual vertices created
    // by extensions are copied below by gp_CopyExtensions()
    for (v = gp_LowerBoundVirtualVertices(srcGraph); v < gp_UpperBoundVirtualVertices(srcGraph); ++v)
    {
        _gp_CopyVertexRec(dstGraph, v, srcGraph, v);
        gp_SetExtFaceVertex(dstGraph, v, 0, gp_GetExtFaceVertex(srcGraph, v, 0));
        gp_SetExtFaceVertex(dstGraph, v, 1, gp_GetExtFaceVertex(srcGraph, v, 1));
    }

    // Copy the basic EdgeRec structures.  Augmentations to the edgeRec structure
    // created by extensions are copied below by gp_CopyExtensions()
    for (e = gp_LowerBoundEdgeStorage(srcGraph); e < gp_UpperBoundEdgeStorage(srcGraph); e++)
        _gp_CopyEdgeRec(dstGraph, e, srcGraph, e);

    // If the dstGraph has more edge storage than the srcGraph, then we clear the extra
    // base edgeRec structures. In gp_CopyExtensions(), the various extensions' copyData()
    // functions are expected to clear out any extension-specific extra edgeRec structures
    if (gp_UpperBoundEdgeStorage(dstGraph) > gp_UpperBoundEdgeStorage(srcGraph))
    {
        for (e = gp_UpperBoundEdgeStorage(srcGraph); e < gp_UpperBoundEdgeStorage(dstGraph); e++)
            _InitEdgeRec(dstGraph, e);
    }

    // Give the dstGraph the same size and intrinsic properties
    dstGraph->N = gp_GetN(srcGraph);
    dstGraph->NV = gp_GetNV(srcGraph);
    dstGraph->M = gp_GetM(srcGraph);
    dstGraph->embedFlags = gp_GetEmbedFlags(srcGraph);

    dstGraph->graphFlags = gp_GetGraphFlags(srcGraph);

    LCCopy(theGraphBicompRootLists(dstGraph), theGraphBicompRootLists(srcGraph));
    LCCopy(theGraphSortedDFSChildLists(dstGraph), theGraphSortedDFSChildLists(srcGraph));
    sp_Copy(dstGraph->theStack, srcGraph->theStack);
    sp_Copy(dstGraph->edgeHoles, srcGraph->edgeHoles);
    dstGraph->numEdgeHoles = sp_GetCurrentSize((dstGraph)->edgeHoles);

    // Copy the set of extensions, which includes copying the
    // extension data as well as the function overload tables
    if (gp_CopyExtensions(dstGraph, srcGraph) != OK)
        return NOTOK;

    // We do not copy the function table of srcGraph to the dstGraph
    // because copy extensions now copies all possible data from
    // srcGraph to dstGraph, but it does not extend dstGraph with
    // any extensions it doesn't already have, so the dstGraph
    // function table is already correct for its type.

    return OK;
}

/********************************************************************
 gp_DupGraph()
 ********************************************************************/

graphP gp_DupGraph(graphP theGraph)
{
    graphP result = NULL;

    if ((result = gp_New()) == NULL)
    {
        gp_ErrorMessage("Failed to create a new graph.");
        return NULL;
    }

    if (gp_EnsureVertexCapacity(result, gp_GetN(theGraph)) != OK)
    {
        gp_ErrorMessage("Failed to increase the vertex capacity of the new "
                        "graph.");
        gp_Free(&result);
        return NULL;
    }

    if (gp_CopyGraph(result, theGraph) != OK)
    {
        gp_ErrorMessage("Failed to copy the source graph to the new graph.");
        gp_Free(&result);
        return NULL;
    }

    if (gp_DupExtensions(result, theGraph) != OK)
    {
        gp_ErrorMessage("Failed to duplicate the extensions of the source graph into the new graph.");
        gp_Free(&result);
        return NULL;
    }

    return result;
}

/********************************************************************
 gp_CreateRandomGraph()

 Creates a randomly generated graph.  First a tree is created by
 connecting each vertex to some successor.  Then a random number of
 additional random edges are added.  If an edge already exists, then
 we retry until a non-existent edge is picked.

 This function assumes the caller has already called srand().

 Returns OK on success, NOTOK on failure
 ********************************************************************/

int gp_CreateRandomGraph(graphP theGraph)
{
    int N, M, u, v, m;
    long long maxSimpleEdges;

    if (theGraph == NULL)
    {
        return NOTOK;
    }

    N = gp_GetN(theGraph);

    /* Generate a random tree; note that this method virtually guarantees
            that the graph will be renumbered, but it is linear time.
            Also, we are not generating the DFS tree but rather a tree
            that simply ensures the resulting random graph is connected. */

    for (v = gp_LowerBoundVertices(theGraph) + 1; v < gp_UpperBoundVertices(theGraph); ++v)
    {
        u = gp_GetRandomNumber(gp_LowerBoundVertices(theGraph), v - 1);
        if (gp_AddEdge(theGraph, u, 0, v, 0) != OK)
            return NOTOK;
    }

    /* Generate a random number of additional edges
            (actually, leave open a small chance that no
            additional edges will be added). */

    M = gp_GetRandomNumber(7 * N / 8, theGraph->edgeCapacity);

    /* N * (N - 1) overflows a 32-bit int at N == 46342, before the halved
            result would, so the simple undirected edge bound is formed in a
            wider type. */

    maxSimpleEdges = ((long long)N * (N - 1)) / 2;

    if (M > maxSimpleEdges)
        M = (int)maxSimpleEdges;

    for (m = N - 1; m < M; m++)
    {
        u = gp_GetRandomNumber(gp_LowerBoundVertices(theGraph), gp_UpperBoundVertices(theGraph) - 2);
        v = gp_GetRandomNumber(u + 1, gp_UpperBoundVertices(theGraph) - 1);

        // If the edge (u,v) exists, decrement eIndex to try again
        if (gp_IsNeighbor(theGraph, u, v))
            m--;

        // If the edge (u,v) doesn't exist, add it
        else
        {
            if (gp_AddEdge(theGraph, u, 0, v, 0) != OK)
                return NOTOK;
        }
    }

    return OK;
}

int _AddRandomGraphEdgeCandidate(randomGraphEdgeRec *edgeList, int edgeListCapacity, int *pEdgeListCount, int u, int v)
{
    if (edgeList == NULL || pEdgeListCount == NULL || *pEdgeListCount >= edgeListCapacity)
        return NOTOK;

    edgeList[*pEdgeListCount].u = u;
    edgeList[*pEdgeListCount].v = v;
    (*pEdgeListCount)++;

    return OK;
}

int _ProcessRandomGraphOptionalEdge(graphP theGraph, randomGraphEdgeRec *edgeList, int edgeListCapacity,
                                    int *pEdgeListCount, int addImmediately, int u, int v)
{
    if (addImmediately)
        return gp_AddEdge(theGraph, u, 0, v, 0) == OK ? OK : NOTOK;

    if (edgeList != NULL)
        return _AddRandomGraphEdgeCandidate(edgeList, edgeListCapacity, pEdgeListCount, u, v);

    return OK;
}

void _ShuffleRandomGraphEdgeCandidates(randomGraphEdgeRec *edgeList, int edgeCount)
{
    int e;

    if (edgeList == NULL)
        return;

    for (e = edgeCount - 1; e > 0; --e)
    {
        int e2 = gp_GetRandomNumber(0, e);
        randomGraphEdgeRec temp = edgeList[e];

        edgeList[e] = edgeList[e2];
        edgeList[e2] = temp;
    }
}

/********************************************************************
 gp_CreateRandomGraphEx()

 Given a graph structure with a pre-specified number of vertices N,
 this function creates a graph with the specified number of edges.

 The primary use case for this method is to generate either a
 maximal planar graph, or a maximal planar graph plus a number
 of random additional edges. These cases correspond to the
 numEdges being equal to 3N-6 or greater than 3N-6, respectively.

 If numEdges < 3N-6, then the graph generated is a connected planar
 subgraph of a random maximal planar graph. The output graph will
 have exactly numEdges edges.

 NOTE: This function assumes the caller has already called srand().

 NOTE: If numEdges is larger than the edge capacity of theGraph, then
       then its value is reduced internally. The caller can invoke
       gp_EnsureEdgeCapacity() beforehand, if desired.
 ********************************************************************/

int gp_CreateRandomGraphEx(graphP theGraph, int numEdges)
{
    randomGraphEdgeRec *optionalEdges = NULL;
    randomGraphFaceRec *faces = NULL;
    int N, maxPlanarEdges, numPlanarCoreEdges;
    long long maxNumEdges;
    int lowerVertex, upperVertex, faceCapacity, optionalEdgeCapacity;
    int optionalEdgeCount = 0, faceCount = 0, addAllPlanarEdges;
    int Result = OK;
    int v, u, e;

    // Parameter checks: Must have a graph of at least three vertices, and the
    // number of edges must be at least enough to support making a random tree.
    if (theGraph == NULL || gp_GetN(theGraph) < 3 || numEdges < (gp_GetN(theGraph) - 1))
        return NOTOK;

    N = gp_GetN(theGraph);
    lowerVertex = gp_LowerBoundVertices(theGraph);
    upperVertex = gp_UpperBoundVertices(theGraph);
    // Formed in a wider type because N * (N - 1) overflows a 32-bit int at
    // N == 46342, before the halved result would.
    maxNumEdges = ((long long)N * (N - 1)) >> 1;
    maxPlanarEdges = 3 * N - 6;

    if (numEdges > theGraph->edgeCapacity)
        numEdges = theGraph->edgeCapacity;

    if (numEdges > maxNumEdges)
        numEdges = (int)maxNumEdges;

    if (numEdges < N - 1)
        return NOTOK;

    numPlanarCoreEdges = numEdges <= maxPlanarEdges ? numEdges : maxPlanarEdges;
    addAllPlanarEdges = numPlanarCoreEdges == maxPlanarEdges;
    faceCapacity = 2 * N - 4;
    optionalEdgeCapacity = maxPlanarEdges - (N - 1);

    faces = (randomGraphFaceRec *)calloc((size_t)faceCapacity, sizeof(randomGraphFaceRec));

    if (!addAllPlanarEdges && numPlanarCoreEdges > N - 1)
        optionalEdges = (randomGraphEdgeRec *)calloc((size_t)optionalEdgeCapacity, sizeof(randomGraphEdgeRec));

    if (faces == NULL || (!addAllPlanarEdges && numPlanarCoreEdges > N - 1 && optionalEdges == NULL))
    {
        Result = NOTOK;
        goto gp_CreateRandomGraphEx_Cleanup;
    }

    faces[faceCount].a = lowerVertex;
    faces[faceCount].b = lowerVertex + 1;
    faces[faceCount].c = lowerVertex + 2;
    faceCount++;

    faces[faceCount].a = lowerVertex;
    faces[faceCount].b = lowerVertex + 2;
    faces[faceCount].c = lowerVertex + 1;
    faceCount++;

    if (gp_AddEdge(theGraph, lowerVertex, 0, lowerVertex + 1, 0) != OK ||
        gp_AddEdge(theGraph, lowerVertex + 1, 0, lowerVertex + 2, 0) != OK)
    {
        Result = NOTOK;
        goto gp_CreateRandomGraphEx_Cleanup;
    }

    if (_ProcessRandomGraphOptionalEdge(theGraph, optionalEdges, optionalEdgeCapacity, &optionalEdgeCount,
                                        addAllPlanarEdges, lowerVertex + 2, lowerVertex) != OK)
    {
        Result = NOTOK;
        goto gp_CreateRandomGraphEx_Cleanup;
    }

    for (v = lowerVertex + 3; v < upperVertex; ++v)
    {
        int faceIndex = gp_GetRandomNumber(0, faceCount - 1);
        int a = faces[faceIndex].a;
        int b = faces[faceIndex].b;
        int c = faces[faceIndex].c;
        int faceVertices[3] = {a, b, c};
        int treeEdgeIndex = gp_GetRandomNumber(0, 2);
        int i;

        if (gp_AddEdge(theGraph, v, 0, faceVertices[treeEdgeIndex], 0) != OK)
        {
            Result = NOTOK;
            goto gp_CreateRandomGraphEx_Cleanup;
        }

        for (i = 0; i < 3; ++i)
        {
            if (i != treeEdgeIndex &&
                _ProcessRandomGraphOptionalEdge(theGraph, optionalEdges, optionalEdgeCapacity,
                                                &optionalEdgeCount, addAllPlanarEdges, v, faceVertices[i]) != OK)
            {
                Result = NOTOK;
                goto gp_CreateRandomGraphEx_Cleanup;
            }
        }

        faces[faceIndex].a = a;
        faces[faceIndex].b = b;
        faces[faceIndex].c = v;

        if (faceCount + 2 > faceCapacity)
        {
            Result = NOTOK;
            goto gp_CreateRandomGraphEx_Cleanup;
        }

        faces[faceCount].a = b;
        faces[faceCount].b = c;
        faces[faceCount].c = v;
        faceCount++;

        faces[faceCount].a = c;
        faces[faceCount].b = a;
        faces[faceCount].c = v;
        faceCount++;
    }

    if (optionalEdges != NULL)
    {
        _ShuffleRandomGraphEdgeCandidates(optionalEdges, optionalEdgeCount);

        for (e = 0; e < optionalEdgeCount && gp_GetM(theGraph) < numPlanarCoreEdges; ++e)
        {
            if (gp_AddEdge(theGraph, optionalEdges[e].u, 0, optionalEdges[e].v, 0) != OK)
            {
                Result = NOTOK;
                goto gp_CreateRandomGraphEx_Cleanup;
            }
        }
    }

    if (gp_GetM(theGraph) < numPlanarCoreEdges)
    {
        Result = NOTOK;
        goto gp_CreateRandomGraphEx_Cleanup;
    }

    /* Add additional random edges if the limit has not yet been reached. */

    while (gp_GetM(theGraph) < numEdges)
    {
        u = gp_GetRandomNumber(lowerVertex, upperVertex - 1);
        v = gp_GetRandomNumber(lowerVertex, upperVertex - 1);

        if (u != v && !gp_IsNeighbor(theGraph, u, v))
        {
            if (gp_AddEdge(theGraph, u, 0, v, 0) != OK)
            {
                Result = NOTOK;
                goto gp_CreateRandomGraphEx_Cleanup;
            }
        }
    }

gp_CreateRandomGraphEx_Cleanup:

    if (optionalEdges != NULL)
    {
        free(optionalEdges);
        optionalEdges = NULL;
    }
    if (faces != NULL)
    {
        free(faces);
        faces = NULL;
    }

    return Result;
}

/********************************************************************
 gp_IsNeighbor()

 Checks whether the adjacency list of an any-type vertex u contains an
 edge record with a neighbor field indicating v.

 Returns TRUE or FALSE.

 NOTE: The edge may be undirected, INONLY or OUTONLY. To test if
       v is an in-neighbor or out-neighbor of u, use the directed
       method gp_IsNeighborDirected() instead.
 ********************************************************************/

int gp_IsNeighbor(graphP theGraph, int u, int v)
{
    int e = NIL;

    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
    {
#ifdef DEBUG
        NOTOK;
#endif
        return FALSE;
    }

    e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetNeighbor(theGraph, e) == v)
            return TRUE;

        e = gp_GetNextEdge(theGraph, e);
    }
    return FALSE;
}

/********************************************************************
 gp_IsNeighborDirected()

 Checks whether the adjacency list of an any-type vertex u contains an
 edge record with a neighbor field indicating v and a direction flag
 matching the direction parameter.

 Returns TRUE or FALSE.

 NOTE: The valid direction flag values are 0 to match any edge record,
       or EDGEFLAG_DIRECTION_INONLY to test if v is an in-neighbor of u,
       or EDGEFLAG_DIRECTION_OUTONLY to test if v is an out-neighbor of u.
 ********************************************************************/
int gp_IsNeighborDirected(graphP theGraph, int u, int v, unsigned direction)
{
    int e = NIL;

    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph) ||
        (direction != 0 && direction != EDGEFLAG_DIRECTION_INONLY && direction != EDGEFLAG_DIRECTION_OUTONLY))
    {
#ifdef DEBUG
        NOTOK;
#endif
        return FALSE;
    }

    e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetNeighbor(theGraph, e) == v)
        {
            if (direction == 0 || direction == gp_GetDirection(theGraph, e))
                return TRUE;
        }
        e = gp_GetNextEdge(theGraph, e);
    }
    return FALSE;
}

/********************************************************************
 gp_FindEdge()

 Searches the adjacency list of an any-type of vertex u to obtain an
 edge record with v in the neighbor field.

 Returns the edge record's location, or NIL if there is no such edge.

 NOTE: The returned edge may be undirected, INONLY or OUTONLY.
       This method is intended for when a graph is undirected or
       when an application must treat a directed graph as if it
       is undirected. To obtain a result for INONLY or OUTONLY
       edges, use gp_FindDirectedEdge() instead.
 ********************************************************************/

int gp_FindEdge(graphP theGraph, int u, int v)
{
    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
    {
#ifdef DEBUG
        NOTOK;
#endif

        return NIL;
    }

    return _gp_FindEdge(theGraph, u, v);
}

/*****************************************************************
 * _gp_FindEdge()
 *
 * Private version of the public method that performs the search
 * without preceding parameter validation checks. This is called
 * from other private methods of the graph library, to avoid
 * duplication of the effort of the checks performed by invoking
 * public methods.
 */
int _gp_FindEdge(graphP theGraph, int u, int v)
{
    int e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetNeighbor(theGraph, e) == v)
            return e;

        e = gp_GetNextEdge(theGraph, e);
    }
    return NIL;
}

/********************************************************************
 gp_FindDirectedEdge()

 Searches the adjacency list of an any-type of vertex u to obtain an
 edge record that matches the direction flag and that has v in the
 neighbor field.

 Returns the edge record's location, or NIL if there is no such edge.

 NOTE: The valid direction flag value are 0 for any direction,
       EDGEFLAG_DIRECTION_INONLY, or EDGEFLAG_DIRECTION_OUTONLY.
 ********************************************************************/
int gp_FindDirectedEdge(graphP theGraph, int u, int v, unsigned direction)
{
    int e = NIL;

    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph) ||
        (direction != 0 && direction != EDGEFLAG_DIRECTION_INONLY && direction != EDGEFLAG_DIRECTION_OUTONLY))
    {
#ifdef DEBUG
        NOTOK;
#endif

        return NIL;
    }

    // If undirected, call the undirected version
    if (direction == 0)
        return _gp_FindEdge(theGraph, u, v);

    // If a direction was given, then use it
    e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetNeighbor(theGraph, e) == v &&
            gp_GetDirection(theGraph, e) == direction)
            return e;

        e = gp_GetNextEdge(theGraph, e);
    }
    return NIL;
}

/********************************************************************
 gp_GetVertexDegree()

Counts the number of edge records in the adjacency list of a given
vertex V.

NOTE: For digraphs, this method returns the total degree of the
    vertex, including undirected, OUTONLY and INONLY edge records.
    Other functions are defined to get the in-degree or out-degree
    of a vertex.

NOTE: This function determines the degree by counting. An extension
    could cache the degree value of each vertex and update the
    cached value as edges are added and deleted.
********************************************************************/

int gp_GetVertexDegree(graphP theGraph, int v)
{
    int e, degree;

    if (theGraph == NULL ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
    {
#ifdef DEBUG
        NOTOK;
        ;
#endif

        return 0;
    }

    degree = 0;

    e = gp_GetFirstEdge(theGraph, v);
    while (gp_IsEdge(theGraph, e))
    {
        degree++;
        e = gp_GetNextEdge(theGraph, e);
    }

    return degree;
}

/********************************************************************
 gp_GetVertexInDegree()

 Counts the number of edge records in the adjacency list of a given
 vertex v that represent edge records from another vertex into v.
 This includes undirected edges and INONLY edge records, so it only
 excludes edges records that are marked as OUTONLY.

 NOTE: This function determines the in-degree by counting. An extension
       could cache the in-degree value of each vertex and update the
       cached value as edges are added and deleted.
 ********************************************************************/

int gp_GetVertexInDegree(graphP theGraph, int v)
{
    int e, degree;

    if (theGraph == NULL ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
    {
#ifdef DEBUG
        NOTOK;
#endif

        return 0;
    }

    degree = 0;

    e = gp_GetFirstEdge(theGraph, v);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetDirection(theGraph, e) != EDGEFLAG_DIRECTION_OUTONLY)
            degree++;
        e = gp_GetNextEdge(theGraph, e);
    }

    return degree;
}

/********************************************************************
 gp_GetVertexOutDegree()

 Counts the number of edge records in the adjacency list of a given
 vertex V that represent edges from V to another vertex.
 This includes undirected edges and OUTONLY edges, so it only excludes
 edges records that are marked as INONLY edges.

 NOTE: This function determines the out-degree by counting. An extension
       could cache the out-degree value of each vertex and update the
       cached value as edges are added and deleted.
 ********************************************************************/

int gp_GetVertexOutDegree(graphP theGraph, int v)
{
    int e, degree;

    if (theGraph == NULL ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
    {
#ifdef DEBUG
        NOTOK;
#endif

        return 0;
    }

    degree = 0;

    e = gp_GetFirstEdge(theGraph, v);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetDirection(theGraph, e) != EDGEFLAG_DIRECTION_INONLY)
            degree++;
        e = gp_GetNextEdge(theGraph, e);
    }

    return degree;
}

/********************************************************************
 _AttachEdgeRecord()

 This routine adds newEdge into v's adjacency list at a position
 adjacent to the edge record for e, either before or after e,
 depending on link.  If e is not an edge (e.g. if e is NIL),
 then link is assumed to indicate whether the newEdge is to be
 placed at the beginning or end of v's adjacency list.

 NOTE: The caller can pass NIL for v if e is not NIL, since the
       vertex is implied (gp_GetNeighbor(theGraph, eTwin))

 The newEdge is assumed to already exist in the data structure (i.e.
 the storage of edges), as only a whole edge (both edge records) can
 be inserted into or deleted from the data structure.

 See also _RestoreEdgeRecord()
 ********************************************************************/

void _AttachEdgeRecord(graphP theGraph, int v, int e, int link, int newEdge)
{
    if (gp_IsEdge(theGraph, e))
    {
        int e2 = gp_GetAdjacentEdge(theGraph, e, link);

        // e's link is newEdge, and newEdge's 1^link is e
        gp_SetAdjacentEdge(theGraph, e, link, newEdge);
        gp_SetAdjacentEdge(theGraph, newEdge, 1 ^ link, e);

        // newEdge's link is e2
        gp_SetAdjacentEdge(theGraph, newEdge, link, e2);

        // if e2 is an edge, then e2's 1^link is newEdge,
        // else v's 1^link is newEdge
        if (gp_IsEdge(theGraph, e2))
            gp_SetAdjacentEdge(theGraph, e2, 1 ^ link, newEdge);
        else
            gp_SetEdgeByLink(theGraph, v, 1 ^ link, newEdge);
    }
    else
    {
        int e2 = gp_GetEdgeByLink(theGraph, v, link);

        // v's link is newEdge, and newEdge's 1^link is NIL
        gp_SetEdgeByLink(theGraph, v, link, newEdge);
        gp_SetAdjacentEdge(theGraph, newEdge, 1 ^ link, NIL);

        // newEdge's elink is e2
        gp_SetAdjacentEdge(theGraph, newEdge, link, e2);

        // if e2 is an edge, then e2's 1^link is newEdge,
        // else v's 1^link is newEdge
        if (gp_IsEdge(theGraph, e2))
            gp_SetAdjacentEdge(theGraph, e2, 1 ^ link, newEdge);
        else
            gp_SetEdgeByLink(theGraph, v, 1 ^ link, newEdge);
    }
}

/****************************************************************************
 _DetachEdge()

 This routine detaches edge record e from its adjacency list, but it does not
 delete it from the data structure (only a whole edge can be deleted).

 Some algorithms must temporarily detach an edge, perform some calculation,
 and eventually put the edge back. This routine supports that operation.
 The neighboring adjacency list nodes are cross-linked, but the two link
 members of edge record e are retained, so edge record e can be reattached
 later by invoking _RestoreEdgeRecord().

 A sequence of detached edge records can only be restored in the exact opposite
 order of their detachment. Thus, algorithms do not directly use this method to
 implement the temporary detach/restore method. Instead, gp_HideEdge() and
 gp_RestoreEdge() are used, and algorithms push and pop hidden edges onto and
 from a stack. A example of this is shown by detaching edges with
 gp_ContractEdge() or gp_IdentifyVertices(), and then reattaching them with
 gp_RestoreVertices(), which unwinds the stack with gp_RestoreVertex().
 ****************************************************************************/

void _DetachEdgeRecord(graphP theGraph, int e)
{
    int nextEdge = gp_GetNextEdge(theGraph, e),
        prevEdge = gp_GetPrevEdge(theGraph, e);

    if (gp_IsEdge(theGraph, nextEdge))
        gp_SetPrevEdge(theGraph, nextEdge, prevEdge);
    else
        gp_SetLastEdge(theGraph, gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e)), prevEdge);

    if (gp_IsEdge(theGraph, prevEdge))
        gp_SetNextEdge(theGraph, prevEdge, nextEdge);
    else
        gp_SetFirstEdge(theGraph, gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e)), nextEdge);
}

/********************************************************************
 gp_AddEdge()

 Adds the undirected edge (u,v) to the graph by placing edge records
 representing u into v's circular edge record list and v into u's
 circular edge record list.

 upos receives the location in G where the u record in v's list will be
 placed, and vpos is the location in G of the v record we placed in
 u's list.  These are used to initialize the short circuit links.

 ulink (0|1) indicates whether the edge record to v in u's list should
        become adjacent to u by its 0 or 1 link, i.e. u[ulink] == vpos.
 vlink (0|1) indicates whether the edge record to u in v's list should
        become adjacent to v by its 0 or 1 link, i.e. v[vlink] == upos.

 NOTE: Only the neighbor and link pointer data members are modified in
       the edge records. The edge records are otherwise assumed to be in
       initial state, either from graph initialization/reinitialization,
       or from edge record reinitialization during gp_DeleteEdge(), if
       the new edge is filling an edge hole in the edge array.This
       expectation of being in initial state includes data stored in
       parallel edge record extension arrays.

 NOTE: This method does not forbid the addition of duplicate and loop
       edges. Use with care because other API endpoints do not all
       support nor check for and eliminate duplicates and loops. The
       caller can guard against these conditions by pre-testing that
       u != v and that gp_FindEdge() returns NIL.

 Returns OK on success, NOTOK on failure (including when adding the
         edge would exceed the graph's edge capacity; the caller can
         use gp_DynamicAddEdge()).
 ********************************************************************/

int gp_AddEdge(graphP theGraph, int u, int ulink, int v, int vlink)
{
    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || v < gp_LowerBoundVertexStorage(theGraph) ||
        u >= gp_UpperBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph))
        return NOTOK;

    if ((ulink != 0 && ulink != 1) || (vlink != 0 && vlink != 1))
    {
        return NOTOK;
    }

    if (gp_InsertEdge(theGraph, u, NIL, ulink, v, NIL, vlink) != OK)
        return NOTOK;

    return OK;
}

/********************************************************************
 gp_DynamicAddEdge()
 Refer to documentation for gp_AddEdge() for parameter description.

 Calls gp_DynamicInsertEdge() with insertion positions that prepend or
 append the new edge records according to ulink and vlink.

 Returns OK on success, NOTOK on failure.
 ********************************************************************/
int gp_DynamicAddEdge(graphP theGraph, int u, int ulink, int v, int vlink)
{
    if (gp_DynamicInsertEdge(theGraph, u, NIL, ulink, v, NIL, vlink) != OK)
        return NOTOK;

    return OK;
}

/********************************************************************
 gp_DynamicInsertEdge()
 Refer to documentation for gp_InsertEdge() for parameter description.

 If the graph is at its edge capacity and has no reusable edge hole,
 doubles the edge capacity using gp_EnsureEdgeCapacity() before calling
 gp_InsertEdge().

 Returns OK on success, NOTOK on failure.
 ********************************************************************/
int gp_DynamicInsertEdge(graphP theGraph, int u, int e_u, int e_ulink,
                         int v, int e_v, int e_vlink)
{
    if (theGraph == NULL || gp_GetN(theGraph) <= 0)
        return NOTOK;

    if (gp_GetM(theGraph) >= theGraph->edgeCapacity && sp_IsEmpty(theGraph->edgeHoles))
    {
        // The new edge capacity is double the current capacity. Parallel
        // edges are supported, so the capacity is not capped at the number
        // of edges needed for an undirected clique on N vertices.
        long long newEdgeCapacity = ((long long)gp_GetEdgeCapacity(theGraph)) << 1;

        // If left shift would overflow signed integer, then cap it at INT_MAX.
        if (newEdgeCapacity > INT_MAX)
        {
            newEdgeCapacity = INT_MAX;
            // If unable to allocate more edges due to already being at INT_MAX,
            // then return failure.
            if (newEdgeCapacity <= gp_GetEdgeCapacity(theGraph))
                return NOTOK;
        }

        if (gp_EnsureEdgeCapacity(theGraph, (int)newEdgeCapacity) != OK)
            return NOTOK;
    }

    if (gp_InsertEdge(theGraph, u, e_u, e_ulink, v, e_v, e_vlink) != OK)
        return NOTOK;

    return OK;
}

/********************************************************************
 gp_InsertEdge()

 This function adds the edge (u, v) such that the edge record added
 to the adjacency list of u is adjacent to e_u and the edge record
 added to the adjacency list of v is adjacent to e_v.
 The direction of adjacency is given by e_ulink for e_u and e_vlink
 for e_v. Specifically, the new edge will be comprised of two edge
 records, n_u and n_v.  In u's (v's) adjacency list, n_u (n_v) will
 be added so that it is indicated by e_u's (e_v's) e_ulink (e_vlink).

 If e_u (or e_v) is not an edge, then e_ulink (e_vlink) indicates
 whether to prepend or append to the adjacency list for u (v).

 NOTE: See notes on gp_AddEdge().

 Returns OK on success, NOTOK on failure, or AT_EDGE_CAPACITY_LIMIT if
         adding the edge would exceed the graph's edge capacity (the
         caller can invoke gp_EnsureEdgeCapacity() beforehand to avoid
         an AT_EDGE_CAPACITY_LIMIT result).
 ********************************************************************/

int gp_InsertEdge(graphP theGraph, int u, int e_u, int e_ulink,
                  int v, int e_v, int e_vlink)
{
    int upos, vpos;

    if (theGraph == NULL)
        return NOTOK;

    if (u < gp_LowerBoundVertexStorage(theGraph) ||
        u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) ||
        v >= gp_UpperBoundVertexStorage(theGraph) ||
        (e_u < gp_LowerBoundEdges(theGraph) && gp_IsEdge(theGraph, e_u)) ||
        e_u >= gp_UpperBoundEdges(theGraph) ||
        (gp_IsEdge(theGraph, e_u) && gp_EdgeNotInUse(theGraph, e_u)) ||
        (e_v < gp_LowerBoundEdges(theGraph) && gp_IsEdge(theGraph, e_v)) ||
        e_v >= gp_UpperBoundEdges(theGraph) ||
        (gp_IsEdge(theGraph, e_v) && gp_EdgeNotInUse(theGraph, e_v)) ||
        e_ulink < 0 || e_ulink > 1 || e_vlink < 0 || e_vlink > 1)
        return NOTOK;

    if (sp_NonEmpty(theGraph->edgeHoles))
    {
        sp_Pop(theGraph->edgeHoles, vpos);
        theGraph->numEdgeHoles = sp_GetCurrentSize(theGraph->edgeHoles);
    }
    else if (gp_GetM(theGraph) >= theGraph->edgeCapacity)
        return AT_EDGE_CAPACITY_LIMIT;
    else
        vpos = gp_UpperBoundEdges(theGraph);

    // NOTE: We do not _InitEdgeRec() nor gp_InitEdgeFlags() here because
    // the vpos edge location is expected to be in initialized state,
    // either from graph initialization/reinitialization, or from
    // edge record reinitialization during gp_DeleteEdge, if vpos was
    // an edge hole. This expectation includes edge record extensions
    // in graph extensions.

    upos = gp_GetTwin(theGraph, vpos);

    gp_SetNeighbor(theGraph, upos, v);
    _AttachEdgeRecord(theGraph, u, e_u, e_ulink, upos);

    gp_SetNeighbor(theGraph, vpos, u);
    _AttachEdgeRecord(theGraph, v, e_v, e_vlink, vpos);

    theGraph->M++;

    return OK;
}

/****************************************************************************
 gp_DeleteEdge()

 This function deletes the given edge record e and its twin, reducing the
 number of edges M in the graph.

 NOTE: This method reinitializes the edge records for e and its twin
       in the base graph data structure. Extensions having parallel
       edge record extension data elements must overload gp_DeleteEdge().

 Returns OK on success, NOTOK on failure
 ****************************************************************************/

int gp_DeleteEdge(graphP theGraph, int e)
{
    if (theGraph == NULL ||
        e < gp_LowerBoundEdges(theGraph) ||
        e >= gp_UpperBoundEdges(theGraph) ||
        gp_EdgeNotInUse(theGraph, e))
        return NOTOK;

    return theGraph->functions->fpDeleteEdge(theGraph, e);
}

int _DeleteEdge(graphP theGraph, int e)
{
    // Delete the edge records e and eTwin from their adjacency lists.
    _DetachEdgeRecord(theGraph, e);
    _DetachEdgeRecord(theGraph, gp_GetTwin(theGraph, e));

    // Clear the two edge records
    // (the bit twiddle (e & ~1) chooses the lesser of e and its twin)
#ifdef USE_1BASEDARRAYS
    memset(theGraph->E + (e & ~1), NIL_CHAR, sizeof(edgeRec) << 1);
#else
    _InitEdgeRec(theGraph, e);
    _InitEdgeRec(theGraph, gp_GetTwin(theGraph, e));
#endif

    // Now we reduce the number of edges in the data structure
    theGraph->M--;

    // If records e and eTwin were not the last in the edge record array,
    // then record a new hole in the edge array.
    if (e < gp_UpperBoundEdges(theGraph))
    {
        if (theGraph->edgeHoles->size + 1 >= theGraph->edgeHoles->capacity)
            return NOTOK;

        sp_Push(theGraph->edgeHoles, e);
        theGraph->numEdgeHoles = sp_GetCurrentSize(theGraph->edgeHoles);
    }

    // Return the previously calculated successor of e.
    return OK;
}

int gp_ClearEdgeDirectionFlags(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    for (int e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); e += 2)
    {
        if (gp_EdgeInUse(theGraph, e))
        {
            // Clear direction flags if non-loop edge
            if (gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e)) != gp_GetNeighbor(theGraph, e))
                gp_SetDirection(theGraph, e, 0);
        }
    }

    theGraph->graphFlags &= ~GRAPHFLAGS_DIRECTEDEDGEDETECTED;
    return OK;
}

/*
 * Reverse every in-use directed edge. This can be used along with a directed
 * depth-first search when computing strongly connected components.
 */
int gp_TransposeDirectedGraph(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    for (int e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); e += 2)
    {
        if (gp_EdgeInUse(theGraph, e))
        {
            int direction = gp_GetDirection(theGraph, e);

            if (direction == EDGEFLAG_DIRECTION_INONLY ||
                direction == EDGEFLAG_DIRECTION_OUTONLY)
            {
                int transposedDirection = direction == EDGEFLAG_DIRECTION_INONLY
                                              ? EDGEFLAG_DIRECTION_OUTONLY
                                              : EDGEFLAG_DIRECTION_INONLY;

                gp_SetDirection(theGraph, e, 0);
                gp_SetDirection(theGraph, e, transposedDirection);
            }
        }
    }

    return OK;
}

/********************************************************************
 _RestoreEdgeRecord()

 This routine reinserts an edge record e into the adjacency list from
 which it was previously removed by _DetachEdgeRecord().

 The assumed processing model is that edge records will be restored in
 reverse of the order in which they were hidden, i.e. it is assumed
 that the hidden edges will be pushed on a stack from which they will
 be popped during restoration.
 ********************************************************************/
void _RestoreEdgeRecord(graphP theGraph, int e)
{
    int nextEdge = gp_GetNextEdge(theGraph, e),
        prevEdge = gp_GetPrevEdge(theGraph, e);

    if (gp_IsEdge(theGraph, nextEdge))
        gp_SetPrevEdge(theGraph, nextEdge, e);
    else
        gp_SetLastEdge(theGraph, gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e)), e);

    if (gp_IsEdge(theGraph, prevEdge))
        gp_SetNextEdge(theGraph, prevEdge, e);
    else
        gp_SetFirstEdge(theGraph, gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e)), e);
}

/********************************************************************
 gp_HideEdge()
 This routine removes the two edge records of an edge from the
 adjacency lists of its endpoint vertices, but it does not delete them
 from the storage data structure.

 Many algorithms must temporarily remove an edge, perform some
 calculation, and eventually put the edge back. This routine supports
 that operation.

 For each edge record of e, the neighboring adjacency list nodes are
 cross-linked, but the links in the edge record are retained because
 they indicate the neighbor edge records to which the edge record can
 be reattached by gp_RestoreEdge().
 ********************************************************************/

void gp_HideEdge(graphP theGraph, int e)
{
    if (theGraph == NULL ||
        e < gp_LowerBoundEdges(theGraph) || e >= gp_UpperBoundEdges(theGraph) ||
        gp_EdgeNotInUse(theGraph, e))
    {
#ifdef DEBUG
        NOTOK;
#endif
        return;
    }

    theGraph->functions->fpHideEdge(theGraph, e);
}

void _HideEdge(graphP theGraph, int e)
{
    _DetachEdgeRecord(theGraph, e);
    _DetachEdgeRecord(theGraph, gp_GetTwin(theGraph, e));
}

/********************************************************************
 gp_RestoreEdge()
 This routine reinserts two edge records of an edge into the adjacency
 lists of the edge's endpoints, the edge records having been previously
 removed by gp_HideEdge().

 The assumed processing model is that edges will be restored in
 reverse of the order in which they were hidden, i.e. it is assumed
 that the hidden edges will be pushed on a stack and the edges will
 be popped from the stack for restoration.

 NOTE: Since both edge records of an edge are restored, only one
       edge record needs to be  pushed on the stack for restoration.
       This routine restores the two edge records in the opposite order
       from the order in which they were hidden by gp_HideEdge().
 ********************************************************************/

void gp_RestoreEdge(graphP theGraph, int e)
{
    if (theGraph == NULL ||
        e < gp_LowerBoundEdges(theGraph) || e >= gp_UpperBoundEdges(theGraph) ||
        gp_EdgeNotInUse(theGraph, e))
    {
#ifdef DEBUG
        NOTOK;
#endif
        return;
    }

    theGraph->functions->fpRestoreEdge(theGraph, e);
}

void _RestoreEdge(graphP theGraph, int e)
{
    _RestoreEdgeRecord(theGraph, gp_GetTwin(theGraph, e));
    _RestoreEdgeRecord(theGraph, e);
}

/********************************************************************
 _HideInternalEdges()
 Pushes onto the graph's stack and hides all edge records of the given
 vertex's adjacency list except the first and last.

 This method is typically called on a vertex that is on the external
 face of a bicomp, where the first and last edge records are the ones
 that attach the vertex to the external face cycle, and any other
 edge records in the adjacency list are inside of that cycle.

 This method uses the stack. The caller is expected to clear the stack
 or save the stack size before invocation, since the stack size is
 needed to _RestoreInternalEdges().
 ********************************************************************/

int _HideInternalEdges(graphP theGraph, int vertex)
{
    int e = gp_GetFirstEdge(theGraph, vertex);

    // If the vertex adjacency list is empty or if it contains
    // only one edge, then there are no *internal* edges to hide
    if (e == gp_GetLastEdge(theGraph, vertex))
        return OK;

    // Start with the first internal edge
    e = gp_GetNextEdge(theGraph, e);

    // Cycle through all the edges, pushing each except stop
    // before pushing the last edge, which is not internal
    while (e != gp_GetLastEdge(theGraph, vertex))
    {
        sp_Push(theGraph->theStack, e);
        gp_HideEdge(theGraph, e);
        e = gp_GetNextEdge(theGraph, e);
    }

    return OK;
}

/********************************************************************
 _RestoreInternalEdges()

 Reverses the effects of _HideInternalEdges()
 ********************************************************************/

int _RestoreInternalEdges(graphP theGraph, int stackBottom)
{
    return _RestoreHiddenEdges(theGraph, stackBottom);
}

/********************************************************************
 _RestoreHiddenEdges()

 Each entry on the stack, down to stackBottom, is assumed to be an
 edge record pushed in concert with invoking gp_HideEdge().
 Each edge is restored using gp_RestoreEdge() in exact reverse of the
 hiding order. The stack is reduced in content size to stackBottom.

 Returns OK on success, NOTOK on internal failure.
 ********************************************************************/

int _RestoreHiddenEdges(graphP theGraph, int stackBottom)
{
    int e;

    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, e);
        if (gp_IsNotEdge(theGraph, e))
            return NOTOK;
        gp_RestoreEdge(theGraph, e);
    }

    return OK;
}

/********************************************************************
 gp_HideVertex()

 Pushes onto the graph's stack and hides all edge records of the
 vertex's adjacency list. Additional integers are then pushed so that
 the result is reversible by gp_RestoreVertex(). See that method for d
 etails on the expected stack segment.

 Returns OK for success, NOTOK for internal failure.
 ********************************************************************/

int gp_HideVertex(graphP theGraph, int vertex)
{
    if (theGraph == NULL ||
        vertex < gp_LowerBoundVertexStorage(theGraph) || vertex >= gp_UpperBoundVertexStorage(theGraph))
    {
        return NOTOK;
    }

    return theGraph->functions->fpHideVertex(theGraph, vertex);
}

int _HideVertex(graphP theGraph, int vertex)
{
    int hiddenEdgeStackBottom = sp_GetCurrentSize(theGraph->theStack);
    int e = gp_GetFirstEdge(theGraph, vertex);

    // Cycle through all the edges, pushing and hiding each
    while (gp_IsEdge(theGraph, e))
    {
        if (sp_GetCurrentSize(theGraph->theStack) >= sp_GetCapacity(theGraph->theStack))
        {
            gp_ErrorMessage("_HideVertex() is attempting to push to a full stack.");
            return NOTOK;
        }

        sp_Push(theGraph->theStack, e);
        gp_HideEdge(theGraph, e);
        e = gp_GetNextEdge(theGraph, e);
    }

    // Push the additional integers needed by gp_RestoreVertex()
    if (sp_GetCurrentSize(theGraph->theStack) + 7 > sp_GetCapacity(theGraph->theStack))
    {
        gp_ErrorMessage("_HideVertex() is attempting to push to a full stack.");
        return NOTOK;
    }

    sp_Push(theGraph->theStack, hiddenEdgeStackBottom);
    sp_Push(theGraph->theStack, NIL);
    sp_Push(theGraph->theStack, NIL);
    sp_Push(theGraph->theStack, NIL);
    sp_Push(theGraph->theStack, NIL);
    sp_Push(theGraph->theStack, NIL);
    sp_Push(theGraph->theStack, vertex);

    return OK;
}

/********************************************************************
 gp_ContractEdge()

 Contracts the edge e=(u,v).  This hides the edge (both e and its
 twin edge record), and it also identifies vertex v with u.
 See gp_IdentifyVertices() for further details.

 Returns OK for success, NOTOK for internal failure.
 ********************************************************************/

int gp_ContractEdge(graphP theGraph, int e)
{
    if (theGraph == NULL ||
        e < gp_LowerBoundEdges(theGraph) || e >= gp_UpperBoundEdges(theGraph) ||
        gp_EdgeNotInUse(theGraph, e))
    {
        return NOTOK;
    }

    return theGraph->functions->fpContractEdge(theGraph, e);
}

int _ContractEdge(graphP theGraph, int e)
{
    int eBefore, u, v;

    if (gp_IsNotEdge(theGraph, e))
        return NOTOK;

    u = gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e));
    v = gp_GetNeighbor(theGraph, e);

    eBefore = gp_GetNextEdge(theGraph, e);

    if (sp_GetCurrentSize(theGraph->theStack) >= sp_GetCapacity(theGraph->theStack))
    {
        gp_ErrorMessage("_ContractEdge() is attempting to push to a full stack.");
        return NOTOK;
    }

    sp_Push(theGraph->theStack, e);
    gp_HideEdge(theGraph, e);

    return gp_IdentifyVertices(theGraph, u, v, eBefore);
}

/********************************************************************
 gp_IdentifyVertices()

 Identifies vertex v with vertex u by transferring all adjacencies
 of v to u.  Any duplicate edges are removed as described below.
 The non-duplicate edges of v are added to the adjacency list of u
 without disturbing their relative order, and they are added before
 the edge record eBefore in u's list. If eBefore is NIL, then the
 edges are simply appended to u's list.

 If u and v are adjacent, then gp_HideEdge() is invoked to remove
 the edge e=(u,v). Then, the edges of v that indicate neighbors of
 u are also hidden.  This is done by setting the visited flags of
 u's neighbors, then traversing the adjacency list of v.  For each
 visited neighbor of v, the edge is hidden because it would duplicate
 an adjacency already expressed in u's list. Finally, the remaining
 edges of v are moved to u's list, and each twin edge record is
 adjusted to indicate u as a neighbor rather than v.

 This routine assumes that the visited flags are clear beforehand,
 and visited flag settings made herein are cleared before returning.

 The following are pushed, in order, onto the graph's built-in stack:
 1) an integer for each hidden edge
 2) the stack size before any hidden edges were pushed
 3) six integers that indicate u, v and the edges moved from v to u

 An algorithm that identifies a series of vertices, either through
 directly calling this method or via gp_ContractEdge(), can unwind
 the identifications using gp_RestoreVertices(), which
 invokes gp_RestoreVertex() repeatedly.

 Returns OK on success, NOTOK on internal failure
 ********************************************************************/

int gp_IdentifyVertices(graphP theGraph, int u, int v, int eBefore)
{
    if (theGraph == NULL ||
        u < gp_LowerBoundVertexStorage(theGraph) || u >= gp_UpperBoundVertexStorage(theGraph) ||
        v < gp_LowerBoundVertexStorage(theGraph) || v >= gp_UpperBoundVertexStorage(theGraph) ||
        (eBefore != NIL && eBefore < gp_LowerBoundEdges(theGraph)) ||
        eBefore >= gp_UpperBoundEdges(theGraph) ||
        (eBefore != NIL && gp_EdgeNotInUse(theGraph, eBefore)))
    {
        return NOTOK;
    }

    return theGraph->functions->fpIdentifyVertices(theGraph, u, v, eBefore);
}

int _IdentifyVertices(graphP theGraph, int u, int v, int eBefore)
{
    int e = _gp_FindEdge(theGraph, u, v);
    int hiddenEdgeStackBottom, eBeforePred;

    // If the vertices are adjacent, then the identification is
    // essentially an edge contraction with a bit of fixup.
    if (gp_IsEdge(theGraph, e))
    {
        int result = gp_ContractEdge(theGraph, e);
        int hiddenEdgesStackBottomIndex;
        int hiddenEdgesStackBottomValue;

        if (result != OK)
            return result;

        // The edge contraction operation pushes one hidden edge then
        // recursively calls this method. This method then pushes K
        // hidden edges then an integer indicating where the top of
        // stack was before the edges were hidden. That integer
        // indicator must be decremented, thereby incrementing the
        // number of hidden edges to K+1.
        // After pushing the K hidden edges and the stackBottom of
        // the hidden edges, the recursive call to this method pushes
        // six more integers to indicate edges that were moved from
        // v to u, so the "hidden edges stackBottom" is in the next
        // position down.
        hiddenEdgesStackBottomIndex = sp_GetCurrentSize(theGraph->theStack) - 7;
        hiddenEdgesStackBottomValue = sp_Get(theGraph->theStack, hiddenEdgesStackBottomIndex);

        sp_Set(theGraph->theStack, hiddenEdgesStackBottomIndex, hiddenEdgesStackBottomValue - 1);

        return result;
    }

    // Now, u and v are not adjacent. Before we do any edge hiding or
    // moving, we record the current stack size, as this is the
    // stackBottom for the edges that will be hidden next.
    hiddenEdgeStackBottom = sp_GetCurrentSize(theGraph->theStack);

    // Mark as visited all neighbors of u
    e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetVisited(theGraph, gp_GetNeighbor(theGraph, e)))
            return NOTOK;

        gp_SetVisited(theGraph, gp_GetNeighbor(theGraph, e));
        e = gp_GetNextEdge(theGraph, e);
    }

    // For each edge record of v, if the neighbor is visited, then
    // push and hide the edge.
    e = gp_GetFirstEdge(theGraph, v);
    while (gp_IsEdge(theGraph, e))
    {
        if (gp_GetVisited(theGraph, gp_GetNeighbor(theGraph, e)))
        {
            if (sp_GetCurrentSize(theGraph->theStack) >= sp_GetCapacity(theGraph->theStack))
            {
                gp_ErrorMessage("_IdentifyVertices() is attempting to push to a full stack.");
                e = gp_GetFirstEdge(theGraph, u);
                while (gp_IsEdge(theGraph, e))
                {
                    gp_ClearVisited(theGraph, gp_GetNeighbor(theGraph, e));
                    e = gp_GetNextEdge(theGraph, e);
                }
                return NOTOK;
            }

            sp_Push(theGraph->theStack, e);
            gp_HideEdge(theGraph, e);
        }
        e = gp_GetNextEdge(theGraph, e);
    }

    // Mark as unvisited all neighbors of u
    e = gp_GetFirstEdge(theGraph, u);
    while (gp_IsEdge(theGraph, e))
    {
        gp_ClearVisited(theGraph, gp_GetNeighbor(theGraph, e));
        e = gp_GetNextEdge(theGraph, e);
    }

    // Push the hiddenEdgeStackBottom as a record of how many hidden
    // edges were pushed (also, see above for Contract Edge adjustment)
    if (sp_GetCurrentSize(theGraph->theStack) + 7 > sp_GetCapacity(theGraph->theStack))
    {
        gp_ErrorMessage("_IdentifyVertices() is attempting to push to a full stack.");
        return NOTOK;
    }

    sp_Push(theGraph->theStack, hiddenEdgeStackBottom);

    // Moving v's adjacency list to u is aided by knowing the predecessor
    // of u's eBefore (the edge record in u's list before which the
    // edge records of v will be added).
    eBeforePred = gp_IsEdge(theGraph, eBefore)
                      ? gp_GetPrevEdge(theGraph, eBefore)
                      : gp_GetLastEdge(theGraph, u);

    // Turns out we only need to record six integers related to the edges
    // being moved in order to easily restore them later.
    sp_Push(theGraph->theStack, eBefore);
    sp_Push(theGraph->theStack, gp_GetLastEdge(theGraph, v));
    sp_Push(theGraph->theStack, gp_GetFirstEdge(theGraph, v));
    sp_Push(theGraph->theStack, eBeforePred);
    sp_Push(theGraph->theStack, u);
    sp_Push(theGraph->theStack, v);

    // For the remaining edge records of v, reassign the 'v' member
    //    of each twin edge record to indicate u rather than v.
    e = gp_GetFirstEdge(theGraph, v);
    while (gp_IsEdge(theGraph, e))
    {
        gp_SetNeighbor(theGraph, gp_GetTwin(theGraph, e), u);
        e = gp_GetNextEdge(theGraph, e);
    }

    // If v has any edges left after hiding edges, indicating common neighbors with u, ...
    if (gp_IsEdge(theGraph, gp_GetFirstEdge(theGraph, v)))
    {
        // Then perform the list union of v into u between eBeforePred and eBefore
        if (gp_IsEdge(theGraph, eBeforePred))
        {
            if (gp_IsEdge(theGraph, gp_GetFirstEdge(theGraph, v)))
            {
                gp_SetNextEdge(theGraph, eBeforePred, gp_GetFirstEdge(theGraph, v));
                gp_SetPrevEdge(theGraph, gp_GetFirstEdge(theGraph, v), eBeforePred);
            }
        }
        else
        {
            gp_SetFirstEdge(theGraph, u, gp_GetFirstEdge(theGraph, v));
        }

        if (gp_IsEdge(theGraph, eBefore))
        {
            if (gp_IsEdge(theGraph, gp_GetLastEdge(theGraph, v)))
            {
                gp_SetNextEdge(theGraph, gp_GetLastEdge(theGraph, v), eBefore);
                gp_SetPrevEdge(theGraph, eBefore, gp_GetLastEdge(theGraph, v));
            }
        }
        else
        {
            gp_SetLastEdge(theGraph, u, gp_GetLastEdge(theGraph, v));
        }

        gp_SetFirstEdge(theGraph, v, NIL);
        gp_SetLastEdge(theGraph, v, NIL);
    }

    return OK;
}

/********************************************************************
 gp_RestoreVertex()

 This method assumes the built-in graph stack contents are the result
 of vertex hide, vertex identify and edge contract operations.
 This content consists of segments of integers, each segment
 corresponding to the removal of a vertex during an edge contraction
 or vertex identification in which a vertex v was merged into a
 vertex u.  The segment contains two blocks of integers.
 The first block contains information about u, v, the edge records
 in v's adjacency list that were added to u, and where in u's
 adjacency list they were added.  The second block of integers
 contains a list of edges incident to v that were hidden from the
 graph because they were incident to neighbors of v that were also
 neighbors of u (so they would have produced duplicate edges had
 they been left in v's adjacency list when it was merged with u's
 adjacency list).

 This method pops the first block of the segment off the stack and
 uses the information to help remove v's adjacency list from u and
 restore it into v.  Then, the second block is removed from the
 stack, and each indicated edge is restored from the hidden state.

 It is anticipated that this method will be overloaded by extension
 algorithms to perform some processing as each vertex is restored.
 Before restoration, the topmost segment has the following structure:

 ... FHE ... LHE HESB e_u_succ e_v_last e_v_first e_u_pred u v
      ^------------|

 FHE = First hidden edge
 LHE = Last hidden edge
 HESB = Hidden edge stack bottom
 e_u_succ, e_u_pred = The edges of u between which the edges of v
                      were inserted. NIL can appear if the edges of v
                      were added to the beginning or end of u's list
 e_v_first, e_v_last = The first and last edges of v's list, once
                       the hidden edges were removed

 Returns OK for success, NOTOK for internal failure.
 ********************************************************************/

int gp_RestoreVertex(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    return theGraph->functions->fpRestoreVertex(theGraph);
}

int _RestoreVertex(graphP theGraph)
{
    int u, v, e_u_succ, e_u_pred, e_v_first, e_v_last, HESB, e;

    if (sp_GetCurrentSize(theGraph->theStack) < 7)
    {
        gp_ErrorMessage("_RestoreVertex() is attempting to pop from an empty stack.");
        return NOTOK;
    }

    sp_Pop(theGraph->theStack, v);
    sp_Pop(theGraph->theStack, u);
    sp_Pop(theGraph->theStack, e_u_pred);
    sp_Pop(theGraph->theStack, e_v_first);
    sp_Pop(theGraph->theStack, e_v_last);
    sp_Pop(theGraph->theStack, e_u_succ);

    // If u is not NIL, then vertex v was identified with u.  Otherwise, v was
    // simply hidden, so we skip to restoring the hidden edges.
    if (gp_IsVertex(theGraph, u))
    {
        // Remove v's adjacency list from u, including accounting for degree 0 case
        if (gp_IsEdge(theGraph, e_u_pred))
        {
            gp_SetNextEdge(theGraph, e_u_pred, e_u_succ);
            // If the successor edge exists, link it to the predecessor,
            // otherwise the predecessor is the new last edge
            if (gp_IsEdge(theGraph, e_u_succ))
                gp_SetPrevEdge(theGraph, e_u_succ, e_u_pred);
            else
                gp_SetLastEdge(theGraph, u, e_u_pred);
        }
        else if (gp_IsEdge(theGraph, e_u_succ))
        {
            // The successor edge exists, but not the predecessor,
            // so the successor is the new first edge
            gp_SetPrevEdge(theGraph, e_u_succ, NIL);
            gp_SetFirstEdge(theGraph, u, e_u_succ);
        }
        else
        {
            // Just in case u was degree zero
            gp_SetFirstEdge(theGraph, u, NIL);
            gp_SetLastEdge(theGraph, u, NIL);
        }

        // Place v's adjacency list into v, including accounting for degree 0 case
        gp_SetFirstEdge(theGraph, v, e_v_first);
        gp_SetLastEdge(theGraph, v, e_v_last);
        if (gp_IsEdge(theGraph, e_v_first))
            gp_SetPrevEdge(theGraph, e_v_first, NIL);
        if (gp_IsEdge(theGraph, e_v_last))
            gp_SetNextEdge(theGraph, e_v_last, NIL);

        // For each edge record restored to v's adjacency list, reassign the 'v' member
        //    of each twin edge record to indicate v rather than u.
        e = e_v_first;
        while (gp_IsEdge(theGraph, e))
        {
            gp_SetNeighbor(theGraph, gp_GetTwin(theGraph, e), v);
            e = (e == e_v_last ? NIL : gp_GetNextEdge(theGraph, e));
        }
    }

    // Restore the hidden edges of v, if any
    if (sp_IsEmpty(theGraph->theStack))
    {
        gp_ErrorMessage("_RestoreVertex() is attempting to pop from an empty stack.");
        return NOTOK;
    }

    sp_Pop(theGraph->theStack, HESB);
    return _RestoreHiddenEdges(theGraph, HESB);
}

/********************************************************************
 gp_RestoreVertices()

 This method assumes the built-in graph stack has content consistent
 with numerous vertex identification or edge contraction operations.
 This method unwinds the stack, moving edges back to their original
 vertex owners and restoring hidden edges.
 This method is a simple iterator that invokes gp_RestoreVertex()
 until the stack is empty, so extension algorithms are more likely
 to overload gp_RestoreVertex().

 Returns OK for success, NOTOK for internal failure.
 ********************************************************************/

int gp_RestoreVertices(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    while (sp_NonEmpty(theGraph->theStack))
    {
        if (gp_RestoreVertex(theGraph) != OK)
            return NOTOK;
    }

    return OK;
}

/****************************************************************************
 _ComputeEdgeRecordType()

 This is just a little helper function that automates a sequence of decisions
 that has to be made a number of times.
 An edge record is being added to the adjacency list of a; it indicates that
 b is a neighbor.  The edgeType can be either 'tree' (EDGE_TYPE_PARENT or
 EDGE_TYPE_CHILD) or 'cycle' (EDGE_TYPE_BACK or EDGE_TYPE_FORWARD).
 If a or b is a root copy, we translate to the non-virtual counterpart,
 then wedetermine which has the lesser DFI.  If a has the lower DFI then the
 edge record is a tree edge to a child (EDGE_TYPE_CHILD) if edgeType indicates
 a tree edge.  If edgeType indicates a cycle edge, then it is a forward cycle
 edge (EDGE_TYPE_FORWARD) to a descendant.
 Symmetric conditions define the types for a > b.
 ****************************************************************************/

int _ComputeEdgeRecordType(graphP theGraph, int a, int b, int edgeType)
{
    a = gp_IsVirtualVertex(theGraph, a) ? _gp_GetVertexFromBicompRoot(theGraph, a) : a;
    b = gp_IsVirtualVertex(theGraph, b) ? _gp_GetVertexFromBicompRoot(theGraph, b) : b;

    if (a < b)
        return edgeType == EDGE_TYPE_PARENT || edgeType == EDGE_TYPE_CHILD ? EDGE_TYPE_CHILD : EDGE_TYPE_FORWARD;

    return edgeType == EDGE_TYPE_PARENT || edgeType == EDGE_TYPE_CHILD ? EDGE_TYPE_PARENT : EDGE_TYPE_BACK;
}

/****************************************************************************
 _RestoreEdgeType()

 When we are restoring an edge, we must restore its type (tree edge or cycle edge).
 We can deduce what the type was based on other information in the graph.
 Each edge record of the edge gets the appropriate type setting (parent/child or
 back/forward). This method runs in constant time plus the degree of vertex u, or
 constant time if u is known to have a degree bound by a constant.
 ****************************************************************************/

int _RestoreEdgeType(graphP theGraph, int u, int v)
{
    int e, eTwin, u_orig, v_orig;

    // If u or v is a virtual vertex (a root copy), then get the non-virtual counterpart.
    u_orig = gp_IsVirtualVertex(theGraph, u) ? (_gp_GetVertexFromBicompRoot(theGraph, u)) : u;
    v_orig = gp_IsVirtualVertex(theGraph, v) ? (_gp_GetVertexFromBicompRoot(theGraph, v)) : v;

    // Get the edge for which we will set the type

    e = _gp_FindEdge(theGraph, u, v);
    eTwin = gp_GetTwin(theGraph, e);

    // If u_orig is the parent of v_orig, or vice versa, then the edge is a tree edge

    if (gp_GetVertexParent(theGraph, v_orig) == u_orig ||
        gp_GetVertexParent(theGraph, u_orig) == v_orig)
    {
        if (u_orig > v_orig)
        {
            gp_ResetEdgeType(theGraph, e, EDGE_TYPE_PARENT);
            gp_ResetEdgeType(theGraph, eTwin, EDGE_TYPE_CHILD);
        }
        else
        {
            gp_ResetEdgeType(theGraph, eTwin, EDGE_TYPE_PARENT);
            gp_ResetEdgeType(theGraph, e, EDGE_TYPE_CHILD);
        }
    }

    // Otherwise it is a back edge

    else
    {
        if (u_orig > v_orig)
        {
            gp_ResetEdgeType(theGraph, e, EDGE_TYPE_BACK);
            gp_ResetEdgeType(theGraph, eTwin, EDGE_TYPE_FORWARD);
        }
        else
        {
            gp_ResetEdgeType(theGraph, eTwin, EDGE_TYPE_BACK);
            gp_ResetEdgeType(theGraph, e, EDGE_TYPE_FORWARD);
        }
    }

    return OK;
}

/********************************************************************
 _DeleteUnmarkedEdgesInBicomp()

 This function deletes from a given biconnected component all edges
 whose visited member is zero.

 The stack is used but preserved. In debug mode, NOTOK can result if
 there is a stack overflow. This method pushes at most one integer
 per vertex in the bicomp.

 Returns OK on success, NOTOK on implementation failure
 ********************************************************************/

int _DeleteUnmarkedEdgesInBicomp(graphP theGraph, int BicompRoot)
{
    int V, e, eNext;
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, V);

        e = gp_GetFirstEdge(theGraph, V);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));

            eNext = gp_GetNextEdge(theGraph, e);
            if (!gp_GetEdgeVisited(theGraph, e))
                gp_DeleteEdge(theGraph, e);
            e = eNext;
        }
    }
    return OK;
}

/********************************************************************
 _ClearInvertedFlagsInBicomp()

 This function clears the inverted flag markers on any edges in a
 given biconnected component.

 The stack is used but preserved. In debug mode, NOTOK can result if
 there is a stack overflow. This method pushes at most one integer
 per vertex in the bicomp.

 Returns OK on success, NOTOK on implementation failure
 ********************************************************************/

int _ClearInvertedFlagsInBicomp(graphP theGraph, int BicompRoot)
{
    int V, e;
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, V);

        e = gp_GetFirstEdge(theGraph, V);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
            {
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));
                gp_ClearEdgeFlagInverted(theGraph, e);
            }

            e = gp_GetNextEdge(theGraph, e);
        }
    }
    return OK;
}

/********************************************************************
 _GetBicompSize()

 Determine the number of vertices in the bicomp.

 The stack is used but preserved. In debug mode, NOTOK can result if
 there is a stack overflow. This method pushes at most one integer
 per vertex in the bicomp.

 Returns a positive number on success, NOTOK on implementation failure
 ********************************************************************/

int _GetBicompSize(graphP theGraph, int BicompRoot)
{
    int V, e;
    int theSize = 0;
    int stackBottom = sp_GetCurrentSize(theGraph->theStack);

    sp_Push(theGraph->theStack, BicompRoot);
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, V);
        theSize++;
        e = gp_GetFirstEdge(theGraph, V);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                sp_Push(theGraph->theStack, gp_GetNeighbor(theGraph, e));

            e = gp_GetNextEdge(theGraph, e);
        }
    }
    return theSize;
}
