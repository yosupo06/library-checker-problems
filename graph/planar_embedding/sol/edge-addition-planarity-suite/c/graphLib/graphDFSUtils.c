/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#define GRAPHDFSUTILS_C

#include "graphDFSUtils.h"
#include "graphDFSUtils.private.h"

// For LOGGING-related declarations
#include "lowLevelUtils/apiutils.private.h"

// Allows the default _SortVertices() to swap planarity vertex info, if present
#include "planarityRelated/graphPlanarity.private.h"

// Private methods, except exported within library
int _DepthFirstSearchDirected(graphP theGraph);
int _SortVertices(graphP theGraph);

// Imported methods
extern void _ClearVertexVisitedFlags(graphP theGraph, int includeVirtualVertices);
extern int _FillVertexVisitedIndexes(graphP theGraph, int FillValue);

/********************************************************************
 gp_ExtendWith_DFSUtils()

 Makes any necessary preparations for supporting DFS utility methods
 that create a DFS tree, sort vertices, and compute least ancestor.
 and lowpoint values. Those four utility methods automatically call
 this method to extend the graph, though this method can also be
 called beforehand.

 This method should be called after gp_EnsureVertexCapacity() or
 gp_Read() because the number of vertices must be known.

 On success, sets GRAPHFLAGS_EXTENDEDWITH_DFSUTILS.

 Returns OK on success, NOTOK on failure.
 ********************************************************************/

int gp_ExtendWith_DFSUtils(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    // if the Graph has already been extended with DFS Utils,
    // then just return successfully
    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_DFSUTILS)
        return OK;

    // Allocate supporting data structures as needed

    // Perform "on success" operations
    theGraph->graphFlags |= GRAPHFLAGS_EXTENDEDWITH_DFSUTILS;
    return OK;
}

/********************************************************************
 gp_Detach_DFSUtils()

 This function is intended to disinherit the DFS Utils feature by
 removing the extension from the graph, which also frees any
 DFS-specific data structures.

 Clears GRAPHFLAGS_EXTENDEDWITH_DFSUTILS after detaching support for
 the DFS utility methods.

 Returns OK for success, NOTOK for failure
 ********************************************************************/

int gp_Detach_DFSUtils(graphP theGraph)
{
    // Free any data structures allocated by the ExtendWith function

    // Indicate successful detachment of DFSUtils
    theGraph->graphFlags &= ~GRAPHFLAGS_EXTENDEDWITH_DFSUTILS;
    return OK;
}

/********************************************************************
 gp_DepthFirstSearch()

 This depth-first search (DFS) assigns a Depth First Index (DFI) to
 each vertex and records the DFS parent of each vertex in each DFS tree
 that forms during the depth-first search. Also, the type of each
 edge record of each edge is set to indicate whether the edge record's
 neighbor value points to a DFS child or parent (a DFS tree edge) or
 a farther DFS ancestor or descendant (the backward and forward
 edge records of a "back" edge/"cycle" edge/"co-tree" edge).

 NOTE: This is a utility function provided for general use. The core
        planarity algorithm uses its own DFS so it can build related
        data structures at the same time.
 ********************************************************************/

int gp_DepthFirstSearch(graphP theGraph)
{
    stackP theStack;
    int DFI, v, uparent, u, e;

    if (theGraph == NULL)
        return NOTOK;

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED)
        return OK;

    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    _gp_LogLine("\ngraphDFSUtils.c/gp_DepthFirstSearch() start");

    theStack = theGraph->theStack;

    /* There are 2M edge records and for each we can push 2 integers,
        plus one extra (NIL, NIL) at the beginning to represent
        arriving at a DFS tree root. So, a stack of 2 * 2 * (1+M)
        integers suffices.
        This stack is already in theGraph structure, so we make sure
        it has the capacity and, if so, that it's empty. */

    if (sp_GetCapacity(theStack) < 2 * 2 * gp_GetM(theGraph) + 2)
        return NOTOK;

    sp_ClearStack(theStack);

    /* Clear the visited flags because they are used to detect what has
        been visited as the DFS traverses the graph. */
    _ClearVertexVisitedFlags(theGraph, FALSE);

    /* This outer loop causes the connected subgraphs of a disconnected
            graph to be numbered */

    for (DFI = v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        if (_gp_IsNotDFSTreeRoot(theGraph, v))
            continue;

        sp_Push2(theStack, NIL, NIL);
        while (sp_NonEmpty(theStack))
        {
            sp_Pop2(theStack, uparent, e);
            u = gp_IsNotVertex(theGraph, uparent) ? v : gp_GetNeighbor(theGraph, e);

            if (!gp_GetVisited(theGraph, u))
            {
                _gp_LogLine(_gp_MakeLogStr3("V=%d, DFI=%d, Parent=%d", u, DFI, uparent));

                gp_SetVisited(theGraph, u);
                gp_SetIndex(theGraph, u, DFI++);
                gp_SetVertexParent(theGraph, u, uparent);
                if (gp_IsEdge(theGraph, e))
                {
                    gp_SetEdgeType(theGraph, e, EDGE_TYPE_CHILD);
                    gp_SetEdgeType(theGraph, gp_GetTwin(theGraph, e), EDGE_TYPE_PARENT);
                }

                /* Push edges to all unvisited neighbors. These will be either
                      tree edges to children or forward edge records of back edges */

                e = gp_GetFirstEdge(theGraph, u);
                while (gp_IsEdge(theGraph, e))
                {
                    if (!gp_GetVisited(theGraph, gp_GetNeighbor(theGraph, e)))
                        sp_Push2(theStack, u, e);
                    e = gp_GetNextEdge(theGraph, e);
                }
            }
            else
            {
                // If the edge leads to a visited vertex, then it is
                // the forward component of a back edge.
                gp_SetEdgeType(theGraph, e, EDGE_TYPE_FORWARD);
                gp_SetEdgeType(theGraph, gp_GetTwin(theGraph, e), EDGE_TYPE_BACK);
            }
        }
    }

    _gp_LogLine("graphDFSUtils.c/gp_DepthFirstSearch() end\n");

    theGraph->graphFlags |= GRAPHFLAGS_DFSNUMBERED;

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED_DIRECTED)
    {
        theGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED_DIRECTED;
        if (_FillVertexVisitedIndexes(theGraph, 0) != OK)
            return NOTOK;
    }

    return OK;
}

/********************************************************************
 gp_DepthFirstSearchEx()

 Routes to the requested depth-first search variant.
 ********************************************************************/

int gp_DepthFirstSearchEx(graphP theGraph, unsigned mode)
{
    if (theGraph == NULL)
        return NOTOK;

    if (mode == DFSMODE_UNDIRECTED)
    {
        if (gp_DepthFirstSearch(theGraph) == OK)
            return OK;
        else
            return NOTOK;
    }
    else if (mode == DFSMODE_DIRECTED)
    {
        if (_DepthFirstSearchDirected(theGraph) == OK)
            return OK;
        else
            return NOTOK;
    }

    return NOTOK;
}

/********************************************************************
 _DepthFirstSearchDirected()

 Performs a directed depth-first search. Discovery times are stored
 in vertex index fields and finish times are stored in visitedIndex.
 Only outgoing and undirected edge records are traversed.
 ********************************************************************/

int _DepthFirstSearchDirected(graphP theGraph)
{
    stackP theStack;
    int timer = 1;
    int v, u, w, e, stackItem, numEdgesPushed;

    if (theGraph == NULL)
        return NOTOK;

    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    theStack = theGraph->theStack;

    // One integer is pushed per eligible edge record, plus at most one
    // finish event per active DFS tree vertex. The graph stack capacity
    // required by the undirected DFS is sufficient for these events.
    if (sp_GetCapacity(theStack) < 2 * 2 * gp_GetM(theGraph) + 2)
        return NOTOK;

    sp_ClearStack(theStack);

    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        gp_SetIndex(theGraph, v, 0);
        gp_SetVertexVisitedIndex(theGraph, v, 0);
        gp_SetVertexParent(theGraph, v, NIL);
    }

    for (e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); ++e)
    {
        if (gp_EdgeInUse(theGraph, e))
        {
            gp_ClearEdgeType(theGraph, e);
            gp_ClearEdgeMarked(theGraph, e);
        }
    }

    // Process each directed DFS tree, including isolated vertices.
    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        if (gp_GetIndex(theGraph, v) != 0)
            continue;

        gp_SetIndex(theGraph, v, timer++);
        gp_SetVertexParent(theGraph, v, NIL);

        numEdgesPushed = 0;
        // Adjacencies are stored in the reverse of their file order, so
        // walking first-to-last pushes the displayed list right-to-left.
        e = gp_GetFirstEdge(theGraph, v);
        while (gp_IsEdge(theGraph, e))
        {
            if (gp_GetDirection(theGraph, e) != EDGEFLAG_DIRECTION_INONLY)
            {
                // This first-pushed edge is the last edge that will be
                // processed for v because the stack reverses the order.
                if (numEdgesPushed == 0)
                    gp_SetEdgeMarked(theGraph, e);
                sp_Push(theStack, e);
                ++numEdgesPushed;
            }
            e = gp_GetNextEdge(theGraph, e);
        }

        if (numEdgesPushed == 0)
            gp_SetVertexVisitedIndex(theGraph, v, timer++);

        while (sp_NonEmpty(theStack))
        {
            sp_Pop(theStack, stackItem);

            // A negative stack item is a deferred finish event. Deferring
            // this event is necessary when a vertex's marked final edge is
            // a tree edge: the new child's subtree must finish first.
            if (stackItem < gp_LowerBoundEdges(theGraph))
            {
                u = -stackItem - 1;
                gp_SetVertexVisitedIndex(theGraph, u, timer++);
                continue;
            }

            e = stackItem;
            u = gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e));
            w = gp_GetNeighbor(theGraph, e);

            if (gp_GetIndex(theGraph, w) == 0)
            {
                gp_ResetEdgeType(theGraph, e, EDGE_TYPE_TREE);
                gp_SetIndex(theGraph, w, timer++);
                gp_SetVertexParent(theGraph, w, u);

                if (gp_GetEdgeMarked(theGraph, e))
                {
                    gp_ClearEdgeMarked(theGraph, e);
                    sp_Push(theStack, -u - 1);
                }

                numEdgesPushed = 0;
                e = gp_GetFirstEdge(theGraph, w);
                while (gp_IsEdge(theGraph, e))
                {
                    if (gp_GetDirection(theGraph, e) != EDGEFLAG_DIRECTION_INONLY)
                    {
                        if (numEdgesPushed == 0)
                            gp_SetEdgeMarked(theGraph, e);
                        sp_Push(theStack, e);
                        ++numEdgesPushed;
                    }
                    e = gp_GetNextEdge(theGraph, e);
                }

                if (numEdgesPushed == 0)
                    gp_SetVertexVisitedIndex(theGraph, w, timer++);
            }
            else
            {
                if (gp_GetVertexVisitedIndex(theGraph, w) == 0)
                    gp_ResetEdgeType(theGraph, e, EDGE_TYPE_BACK);
                else if (gp_GetIndex(theGraph, w) < gp_GetIndex(theGraph, u))
                    gp_ResetEdgeType(theGraph, e, EDGE_TYPE_CROSS);
                else
                    gp_ResetEdgeType(theGraph, e, EDGE_TYPE_FORWARD);

                if (gp_GetEdgeMarked(theGraph, e))
                {
                    gp_ClearEdgeMarked(theGraph, e);
                    gp_SetVertexVisitedIndex(theGraph, u, timer++);
                }
            }
        }
    }

    theGraph->graphFlags |= GRAPHFLAGS_DFSNUMBERED_DIRECTED;
    theGraph->graphFlags &= ~GRAPHFLAGS_DFSNUMBERED;

    return OK;
}

/********************************************************************
 gp_SortVertices()

 Once depth first numbering has been applied to the graph, the index
 member of each vertex contains the DFI.  This routine can reorder the
 vertices in linear time so that they appear in ascending order by DFI.
 Note that the index field is then used to store the original number
 of the vertex. Therefore, a second call to this method will put the
 vertices back to the original order and put the DFIs back into the
 index fields of the vertices.

 NOTE: This function is used by the core planarity algorithm, once its
 custom DFS has assigned DFIs to the vertices.  Once gp_Embed() has
 finished creating an embedding or obstructing subgraph, this function
 can be called to restore the original vertex numbering, if needed.
 ********************************************************************/

int gp_SortVertices(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    return theGraph->functions->fpSortVertices(theGraph);
}

// Give macro names to swap operations used when sorting vertices
// These are macros and hence not overloadable. If an extension
// needs to reorder parallel vertex data, then this must be done
// by a post-processing step in an overload of gp_SortVertices().
// The index values of the first N vertices are changed to hold
// the prior locations of vertices when they are rearranged to
// or from DFI order.
#define _gp_SwapVertexRec(dstGraph, vdst, srcGraph, vsrc) \
    {                                                     \
        vertexRec tempV = dstGraph->V[vdst];              \
        dstGraph->V[vdst] = srcGraph->V[vsrc];            \
        srcGraph->V[vsrc] = tempV;                        \
    }
#define _gp_SwapDFSUtilsVertexInfo(dstGraph, dstPos, srcGraph, srcPos) \
    {                                                                  \
        DFSUtils_VertexInfo tempDVI = theGraphDVI(dstGraph)[dstPos];   \
        theGraphDVI(dstGraph)[dstPos] = theGraphDVI(srcGraph)[srcPos]; \
        theGraphDVI(srcGraph)[srcPos] = tempDVI;                       \
    }
#define _gp_SwapPlanarityVertexInfo(dstGraph, dstPos, srcGraph, srcPos) \
    if (theGraphPVI(dstGraph) != NULL && theGraphPVI(srcGraph) != NULL) \
    {                                                                   \
        Planarity_VertexInfo tempPVI = theGraphPVI(dstGraph)[dstPos];   \
        theGraphPVI(dstGraph)[dstPos] = theGraphPVI(srcGraph)[srcPos];  \
        theGraphPVI(srcGraph)[srcPos] = tempPVI;                        \
    }

// This is the default method for sorting vertices into and back
// out of DFI order.
int _SortVertices(graphP theGraph)
{
    int v, srcPos, dstPos;

    if (theGraph == NULL)
        return NOTOK;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED))
        if (gp_DepthFirstSearch(theGraph) != OK)
            return NOTOK;

    _gp_LogLine("\ngraphDFSUtils.c/_SortVertices() start");

    /* Change labels of edges from v to DFI(v)-- or vice versa
       Also, if any links go back to locations 0 to n-1, then they
       need to be changed because we are reordering the vertices */

    if (theGraph->numEdgeHoles == 0)
    {
        // Slightly optimized loop body, for when edge deletion has not been used
        // (Optimization level O1 or higher hoists the upperBoundEdges calculation,
        //  so this is mainly just a little less work in the loop body).
        int upperBoundEdges = gp_LowerBoundEdges(theGraph) + (gp_GetM(theGraph) << 1);
        for (int e = gp_LowerBoundEdges(theGraph); e < upperBoundEdges; ++e)
            gp_SetNeighbor(theGraph, e, gp_GetIndex(theGraph, gp_GetNeighbor(theGraph, e)));
    }
    else
    {
        for (int e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); e += 2)
        {
            if (gp_EdgeInUse(theGraph, e))
            {
                gp_SetNeighbor(theGraph, e, gp_GetIndex(theGraph, gp_GetNeighbor(theGraph, e)));
                gp_SetNeighbor(theGraph, e + 1, gp_GetIndex(theGraph, gp_GetNeighbor(theGraph, e + 1)));
            }
        }
    }

    /* Convert DFSParent from v to DFI(v) or vice versa */

    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
        if (_gp_IsNotDFSTreeRoot(theGraph, v))
            gp_SetVertexParent(theGraph, v, gp_GetIndex(theGraph, gp_GetVertexParent(theGraph, v)));

    /* Sort by 'v using constant time random access. Move each vertex to its
       destination 'v', and store its source location in 'v'. */

    /* First we clear the visitation flags.  We need these to help mark
       visited vertices because we change the 'v' field to be the source
       location, so we cannot use index==v as a test for whether the
       correct vertex is in location 'index'. */

    _ClearVertexVisitedFlags(theGraph, FALSE);

    /* We visit each vertex location, skipping those marked as visited since
       we've already moved the correct vertex into that location. The
       inner loop swaps the vertex at location v into the correct position,
       given by the index of the vertex at location v.  Then it marks that
       location as visited, then sets its index to be the location from
       whence we obtained the vertex record. */

    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        srcPos = v;
        while (!gp_GetVisited(theGraph, v))
        {
            dstPos = gp_GetIndex(theGraph, v);

            _gp_SwapVertexRec(theGraph, dstPos, theGraph, v);
            _gp_SwapDFSUtilsVertexInfo(theGraph, dstPos, theGraph, v);
            _gp_SwapPlanarityVertexInfo(theGraph, dstPos, theGraph, v);

            gp_SetVisited(theGraph, dstPos);
            gp_SetIndex(theGraph, dstPos, srcPos);

            srcPos = dstPos;
        }
    }

    /* Invert the bit that records the sort order of the graph */

    theGraph->graphFlags &= ~GRAPHFLAGS_LOWPOINTSCOMPUTED;
    theGraph->graphFlags ^= GRAPHFLAGS_SORTEDBYDFI;

    _gp_LogLine("graphDFSUtils.c/_SortVertices() end\n");

    return OK;
}

/********************************************************************
 gp_ComputeLowpoints()

        leastAncestor(v): min(v, ancestor neighbors of v, excluding parent)
        Lowpoint(v): min(leastAncestor(v), Lowpoint of DFS children of v)

 The Lowpoint of each vertex is computed via a post-order traversal of the
 DFS tree. Lowpoint calculations require leastAncestor calculations, so
 both are computed by this method.

 We push the root of the DFS tree, then we loop while the stack is not empty.
 We pop a vertex; if it is not marked, then we are on our way down the DFS
 tree, so we mark it and push it back on, followed by pushing its
 DFS children.  The next time we pop the node, all of its children
 will have been popped, marked+children pushed, and popped again.  On
 the second pop of the vertex, we can therefore compute the lowpoint
 values based on the childrens' lowpoints and the least ancestor from
 among the edges in the vertex's adjacency list.

 If they have not already been performed, gp_DepthFirstSearch() and
 gp_SortVertices() are invoked on the graph, and it is left in the
 sorted state on completion of this method.

 NOTE: This is a utility function provided for general use of the graph
       library. The core planarity algorithm computes leastAncestor during
       its initial DFS, and it computes the lowpoint of each a vertex as
       it embeds the tree edges to its children.
 ********************************************************************/

int gp_ComputeLowpoints(graphP theGraph)
{
    stackP theStack = NULL;
    int v, u, uneighbor, e, L, leastAncestor;

    if (theGraph == NULL)
        return NOTOK;

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DIRECTEDEDGEDETECTED)
    {
        gp_ErrorMessage("gp_ComputeLowpoints() does not support directed graphs.");
        return NOTOK;
    }

    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    theStack = theGraph->theStack;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED))
        if (gp_DepthFirstSearch(theGraph) != OK)
            return NOTOK;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_SORTEDBYDFI))
        if (gp_SortVertices(theGraph) != OK)
            return NOTOK;

    _gp_LogLine("\ngraphDFSUtils.c/gp_ComputeLowpoints() start");

    // A stack of size N suffices because at maximum every vertex is pushed only once
    // However, since a larger stack is needed for the main DFS, this is really
    // just 'documentation' of the requirement
    if (sp_GetCapacity(theStack) < gp_GetN(theGraph))
        return NOTOK;

    sp_ClearStack(theStack);

    _ClearVertexVisitedFlags(theGraph, FALSE);

    // This outer loop causes the connected subgraphs of a disconnected graph to be processed
    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph);)
    {
        if (gp_GetVisited(theGraph, v))
        {
            ++v;
            continue;
        }

        sp_Push(theStack, v);
        while (sp_NonEmpty(theStack))
        {
            sp_Pop(theStack, u);

            // If not visited, then we're on the pre-order visitation, so push u and its DFS children
            if (!gp_GetVisited(theGraph, u))
            {
                // Mark u as visited, then push it back on the stack
                gp_SetVisited(theGraph, u);
                ++v;
                sp_Push(theStack, u);

                // Push the DFS children of u
                e = gp_GetFirstEdge(theGraph, u);
                while (gp_IsEdge(theGraph, e))
                {
                    if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                    {
                        sp_Push(theStack, gp_GetNeighbor(theGraph, e));
                    }

                    e = gp_GetNextEdge(theGraph, e);
                }
            }

            // If u has been visited before, then this is the post-order visitation
            else
            {
                // Start with high values because we are doing a min function
                leastAncestor = L = u;

                // Compute leastAncestor and L, the least lowpoint from the DFS children
                e = gp_GetFirstEdge(theGraph, u);
                while (gp_IsEdge(theGraph, e))
                {
                    uneighbor = gp_GetNeighbor(theGraph, e);
                    if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                    {
                        if (L > gp_GetVertexLowpoint(theGraph, uneighbor))
                            L = gp_GetVertexLowpoint(theGraph, uneighbor);
                    }
                    else if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_BACK)
                    {
                        if (leastAncestor > uneighbor)
                            leastAncestor = uneighbor;
                    }

                    e = gp_GetNextEdge(theGraph, e);
                }

                /* Assign leastAncestor and Lowpoint to the vertex */
                gp_SetVertexLeastAncestor(theGraph, u, leastAncestor);
                gp_SetVertexLowpoint(theGraph, u, leastAncestor < L ? leastAncestor : L);
            }
        }
    }

    _gp_LogLine("graphDFSUtils.c/gp_ComputeLowpoints() end\n");

    theGraph->graphFlags |= GRAPHFLAGS_LOWPOINTSCOMPUTED;

    return OK;
}

/********************************************************************
 gp_ComputeLeastAncestors()

 By simple pre-order visitation, compute the least ancestor of each
 vertex that is directly adjacent to the vertex by a back edge.

 If they have not already been performed, gp_DepthFirstSearch() and
 gp_SortVertices() are invoked on the graph, and it is left in the
 sorted state on completion of this method.

 NOTE: This method is not called by gp_ComputeLowpoints(),
       which computes both values at the same time.
 ********************************************************************/

int gp_ComputeLeastAncestors(graphP theGraph)
{
    stackP theStack = NULL;
    int v, u, uneighbor, e, leastAncestor;

    if (theGraph == NULL)
        return NOTOK;

    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DIRECTEDEDGEDETECTED)
    {
        gp_ErrorMessage("gp_ComputeLeastAncestors() does not support directed graphs.");
        return NOTOK;
    }

    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    theStack = theGraph->theStack;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED))
        if (gp_DepthFirstSearch(theGraph) != OK)
            return NOTOK;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_SORTEDBYDFI))
        if (gp_SortVertices(theGraph) != OK)
            return NOTOK;

    _gp_LogLine("\ngraphDFSUtils.c/gp_ComputeLeastAncestors() start");

    // A stack of size N suffices because at maximum every vertex is pushed only once
    if (sp_GetCapacity(theStack) < gp_GetN(theGraph))
        return NOTOK;

    sp_ClearStack(theStack);

    // This outer loop causes the connected subgraphs of a disconnected graph to be processed
    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph);)
    {
        if (gp_GetVisited(theGraph, v))
        {
            ++v;
            continue;
        }

        sp_Push(theStack, v);
        while (sp_NonEmpty(theStack))
        {
            sp_Pop(theStack, u);

            if (!gp_GetVisited(theGraph, u))
            {
                gp_SetVisited(theGraph, u);
                ++v;
                leastAncestor = u;

                e = gp_GetFirstEdge(theGraph, u);
                while (gp_IsEdge(theGraph, e))
                {
                    uneighbor = gp_GetNeighbor(theGraph, e);
                    if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_CHILD)
                    {
                        sp_Push(theStack, uneighbor);
                    }
                    else if (gp_GetEdgeType(theGraph, e) == EDGE_TYPE_BACK)
                    {
                        if (leastAncestor > uneighbor)
                            leastAncestor = uneighbor;
                    }

                    e = gp_GetNextEdge(theGraph, e);
                }
                gp_SetVertexLeastAncestor(theGraph, u, leastAncestor);
            }
        }
    }

    _gp_LogLine("graphDFSUtils.c/gp_ComputeLeastAncestors() end\n");

    return OK;
}

/********************************************************************
 gp_CountConnectedComponents()

 Once the DFS tree has been created in theGraph, this method returns
 the number of connected components identified by DFS tree roots.
 Returns -1 on error, such as a NULL graph or DFS tree not created yet.
 ********************************************************************/
int gp_CountConnectedComponents(graphP theGraph)
{
    int v, connectedComponents;

    if (theGraph == NULL)
        return -1;
        
    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED))
        return -1;

    connectedComponents = 0;
    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
        if (_gp_IsDFSTreeRoot(theGraph, v))
            connectedComponents++;

    return connectedComponents;
}

/********************************************************************
 gp_GetParent()

 Once the DFS tree has been created in theGraph, this method returns
 the DFS parent of the given vertex v. This includes returning NIL
 for a DFS tree root, which has no DFS parent. Also returns NIL on
 error, such as invalid parameters or DFS tree not created yet.
 ********************************************************************/
int gp_GetParent(graphP theGraph, int v)
{
    if (theGraph == NULL ||
        v < gp_LowerBoundVertices(theGraph) || v >= gp_UpperBoundVertices(theGraph))
    {
#ifdef DEBUG
        NOTOK;
        ;
#endif
        return NIL;
    }

    return gp_GetVertexParent(theGraph, v);
}

/********************************************************************
 gp_GetVisitedIndex()

 This method returns the visited index of the given vertex v.
 Returns NIL on error, such as invalid parameters.
 ********************************************************************/
int gp_GetVisitedIndex(graphP theGraph, int v)
{
    if (theGraph == NULL ||
        v < gp_LowerBoundVertices(theGraph) || v >= gp_UpperBoundVertices(theGraph))
    {
#ifdef DEBUG
        NOTOK;
        ;
#endif
        return NIL;
    }

    return gp_GetVertexVisitedIndex(theGraph, v);
}

/********************************************************************
 gp_GetLeastAncestor()

 Once the least ancestors have been computed in the graph, which
 includes when they are implicitly calculated as part of computing
 lowpoints, this method returns the least ancestor value for the
 given vertex v. Returns NIL on error, such as invalid parameters
 or least ancestor values not computed yet.
 ********************************************************************/
int gp_GetLeastAncestor(graphP theGraph, int v)
{
    if (theGraph == NULL ||
        v < gp_LowerBoundVertices(theGraph) || v >= gp_UpperBoundVertices(theGraph))
    {
#ifdef DEBUG
        NOTOK;
        ;
#endif
        return NIL;
    }

    return gp_GetVertexLeastAncestor(theGraph, v);
}

/********************************************************************
 gp_GetLowpoint()

 Once the lowpoints have been computed in the graph, this method
 returns the lowpoint value for the given vertex v. Returns NIL on
 error, such as invalid parameters or lowpoints not computed yet.
 ********************************************************************/
int gp_GetLowpoint(graphP theGraph, int v)
{
    if (theGraph == NULL ||
        v < gp_LowerBoundVertices(theGraph) || v >= gp_UpperBoundVertices(theGraph))
    {
#ifdef DEBUG
        NOTOK;
        ;
#endif
        return NIL;
    }

    return gp_GetVertexLowpoint(theGraph, v);
}
