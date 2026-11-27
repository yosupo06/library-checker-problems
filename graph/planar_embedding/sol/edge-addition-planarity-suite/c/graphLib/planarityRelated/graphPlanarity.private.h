/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifndef GRAPHPLANARITY_PRIVATE_H
#define GRAPHPLANARITY_PRIVATE_H

#include "../graphDFSUtils.private.h"

#ifdef __cplusplus
extern "C"
{
#endif

// PLANARITY-RELATED ONLY VERTEX FLAGS
//
// The ANYVERTEX_OBSTRUCTIONMARK_MASK bits are bits 2-4, 4+8+16=28
// They are used by planarity-related algorithms to identify the four
// regions of the external face cycle of a bicomp, relative to an
// XY-path in the bicomp.
// Bit 2 - 4 if the OBSTRUCTIONMARK is set, 0 if not
// Bit 3 - 8 if the OBSTRUCTIONMARK indicates Y side, 0 if X side
// Bit 4 - 16 if the OBSTRUCTIONMARK indicates high, 0 if low
#define ANYVERTEX_OBSTRUCTIONMARK_MASK 28

// Call gp_GetObstructionMark, then compare to one of these four possibilities
// ANYVERTEX_OBSTRUCTIONMARK_HIGH_RXW - On the external face path between vertices R and X
// ANYVERTEX_OBSTRUCTIONMARK_LOW_RXW  - X or on the external face path between vertices X and W
// ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW - On the external face path between vertices R and Y
// ANYVERTEX_OBSTRUCTIONMARK_LOW_RYW  - Y or on the external face path between vertices Y and W
// ANYVERTEX_OBSTRUCTIONMARK_UNMARKED  - corresponds to all three bits off
#define ANYVERTEX_OBSTRUCTIONMARK_HIGH_RXW 20
#define ANYVERTEX_OBSTRUCTIONMARK_LOW_RXW 4
#define ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW 28
#define ANYVERTEX_OBSTRUCTIONMARK_LOW_RYW 12
#define ANYVERTEX_OBSTRUCTIONMARK_UNMARKED 0

#define gp_GetObstructionMark(theGraph, v) (theGraph->V[v].flags & ANYVERTEX_OBSTRUCTIONMARK_MASK)
#define gp_ClearObstructionMark(theGraph, v) (theGraph->V[v].flags &= ~ANYVERTEX_OBSTRUCTIONMARK_MASK)
#define gp_SetObstructionMark(theGraph, v, type) (theGraph->V[v].flags |= type)
#define gp_ResetObstructionMark(theGraph, v, type) \
    (theGraph->V[v].flags = (theGraph->V[v].flags & ~ANYVERTEX_OBSTRUCTIONMARK_MASK) | type)

    /********************************************************************
    // PLANARITY-RELATED ONLY
    //
     This structure defines a pair of links used by each vertex and virtual vertex
        to create "short circuit" paths that eliminate unimportant vertices from
        the external face, enabling more efficient traversal of the external face.

        It is also possible to embed the "short circuit" edges, but this approach
        creates a better separation of concerns, imparts greater clarity, and
        removes exceptionalities for handling additional fake "short circuit" edges.

        vertex[2]: The two adjacent vertices along the external face, possibly
                short-circuiting paths of inactive vertices.
    */

    struct extFaceLinkRec
    {
        int vertex[2];
    };

    typedef struct extFaceLinkRec extFaceLinkRec;
    typedef extFaceLinkRec *extFaceLinkRecP;

#define gp_GetExtFaceVertex(theGraph, v, link) (theGraphExtFace(theGraph)[v].vertex[link])
#define gp_SetExtFaceVertex(theGraph, v, link, theVertex) (theGraphExtFace(theGraph)[v].vertex[link] = theVertex)

    /********************************************************************
    // PLANARITY-RELATED ONLY
    //
    Planarity-specific additional vertex information.

        pertinentEdge: Used by the planarity method; during Walkup, each vertex
                    that is directly adjacent via a back edge to the vertex v
                    currently being embedded will have the forward edge's index
                    stored in this field.  During Walkdown, each vertex for which
                    this field is set will cause a back edge to be embedded.
                    Implicitly resets at each vertex step of the planarity method
        pertinentRootsList: used by Walkup to store a list of child bicomp roots of
                    a vertex descendant of the current vertex that are pertinent
                    and must be merged by the Walkdown in order to embed the cycle
                    edges of the current vertex.  Future pertinent child bicomp roots
                    are placed at the end of the list to ensure bicomps that are
                    only pertinent are processed first.
        futurePertinentChild: indicates a DFS child with a lowpoint less than the
                    current vertex v.  This member is initialized to the start of
                    the sortedDFSChildList and is advanced in a relaxed manner as
                    needed until one with a lowpoint less than v is found or until
                    there are no more children.
        sortedDFSChildList: at the start of embedding, the list of DFS children of
                    this vertex is calculated in ascending order by DFI (sorted in
                    linear time). The list is used during Walkdown processing of
                    a vertex to process all of its children.  It is also used in
                    future pertinence management when processing the ancestors of
                    the vertex. When a child C is merged into the same bicomp as
                    the vertex, it is removed from the list.
        fwdEdgeList: at the start of embedding, the "back" edges from a vertex to
                    its DFS *descendants* (i.e. the forward edge records) are
                    separated from the main adjacency list and placed in a
                    circular list until they are embedded. The list is sorted in
                    ascending DFI order of the descendants (in linear time).
                    This member indicates (by index) a node in that list.
    */

    struct Planarity_VertexInfo
    {
        int pertinentEdge,
            pertinentRoots,
            futurePertinentChild,
            sortedDFSChildList,
            fwdEdgeList;
    };

    typedef struct Planarity_VertexInfo Planarity_VertexInfo;
    typedef Planarity_VertexInfo *Planarity_VertexInfoP;

#define gp_GetVertexPertinentEdge(theGraph, v) (theGraphPVI(theGraph)[v].pertinentEdge)
#define gp_SetVertexPertinentEdge(theGraph, v, e) (theGraphPVI(theGraph)[v].pertinentEdge = e)

#define gp_GetVertexPertinentRootsList(theGraph, v) (theGraphPVI(theGraph)[v].pertinentRoots)
#define gp_SetVertexPertinentRootsList(theGraph, v, pertinentRootsHead) (theGraphPVI(theGraph)[v].pertinentRoots = pertinentRootsHead)

#define gp_GetVertexFirstPertinentRoot(theGraph, v) gp_GetBicompRootFromDFSChild(theGraph, theGraphPVI(theGraph)[v].pertinentRoots)
#define gp_GetVertexFirstPertinentRootChild(theGraph, v) (theGraphPVI(theGraph)[v].pertinentRoots)
#define gp_GetVertexLastPertinentRoot(theGraph, v) gp_GetBicompRootFromDFSChild(theGraph, LCGetPrev(theGraphBicompRootLists(theGraph), theGraphPVI(theGraph)[v].pertinentRoots, NIL))
#define gp_GetVertexLastPertinentRootChild(theGraph, v) LCGetPrev(theGraphBicompRootLists(theGraph), theGraphPVI(theGraph)[v].pertinentRoots, NIL)

#define gp_DeleteVertexPertinentRoot(theGraph, v, R)                                     \
    gp_SetVertexPertinentRootsList(theGraph, v,                                          \
                                   LCDelete(theGraphBicompRootLists(theGraph),           \
                                            gp_GetVertexPertinentRootsList(theGraph, v), \
                                            gp_GetDFSChildFromBicompRoot(theGraph, R)))

#define gp_PrependVertexPertinentRoot(theGraph, v, R)                                     \
    gp_SetVertexPertinentRootsList(theGraph, v,                                           \
                                   LCPrepend(theGraphBicompRootLists(theGraph),           \
                                             gp_GetVertexPertinentRootsList(theGraph, v), \
                                             gp_GetDFSChildFromBicompRoot(theGraph, R)))

#define gp_AppendVertexPertinentRoot(theGraph, v, R)                                     \
    gp_SetVertexPertinentRootsList(theGraph, v,                                          \
                                   LCAppend(theGraphBicompRootLists(theGraph),           \
                                            gp_GetVertexPertinentRootsList(theGraph, v), \
                                            gp_GetDFSChildFromBicompRoot(theGraph, R)))

#define gp_GetVertexFuturePertinentChild(theGraph, v) (theGraphPVI(theGraph)[v].futurePertinentChild)
#define gp_SetVertexFuturePertinentChild(theGraph, v, theFuturePertinentChild) (theGraphPVI(theGraph)[v].futurePertinentChild = theFuturePertinentChild)

// Used to advance futurePertinentChild of w to the next separated DFS child with a lowpoint less than v
// Once futurePertinentChild advances past a child, no future planarity operation could make that child
// relevant to future pertinence.
#define gp_UpdateVertexFuturePertinentChild(theGraph, w, v)                                             \
    while (gp_IsVertex(theGraph, theGraphPVI(theGraph)[w].futurePertinentChild))                        \
    {                                                                                                   \
        /* Skip children that 1) aren't future pertinent, 2) have been merged into the bicomp with w */ \
        if (gp_GetVertexLowpoint(theGraph, theGraphPVI(theGraph)[w].futurePertinentChild) >= v ||       \
            gp_IsNotSeparatedDFSChild(theGraph, theGraphPVI(theGraph)[w].futurePertinentChild))         \
        {                                                                                               \
            theGraphPVI(theGraph)[w].futurePertinentChild =                                             \
                gp_GetVertexNextDFSChild(theGraph, w, gp_GetVertexFuturePertinentChild(theGraph, w));   \
        }                                                                                               \
        else                                                                                            \
            break;                                                                                      \
    }

#define gp_GetVertexSortedDFSChildList(theGraph, v) (theGraphPVI(theGraph)[v].sortedDFSChildList)
#define gp_SetVertexSortedDFSChildList(theGraph, v, theSortedDFSChildList) (theGraphPVI(theGraph)[v].sortedDFSChildList = theSortedDFSChildList)

#define gp_GetVertexNextDFSChild(theGraph, v, c) LCGetNext(theGraphSortedDFSChildLists(theGraph), gp_GetVertexSortedDFSChildList(theGraph, v), c)

#define gp_AppendDFSChild(theGraph, v, c) \
    LCAppend(theGraphSortedDFSChildLists(theGraph), gp_GetVertexSortedDFSChildList(theGraph, v), c)

#define gp_GetVertexFwdEdgeList(theGraph, v) (theGraphPVI(theGraph)[v].fwdEdgeList)
#define gp_SetVertexFwdEdgeList(theGraph, v, theFwdEdgeList) (theGraphPVI(theGraph)[v].fwdEdgeList = theFwdEdgeList)

    /********************************************************************
    // PLANARITY-RELATED ONLY
    //
     Variables needed in embedding by Kuratowski subgraph isolator:
            minorType: the type of planarity obstruction found.
            v: the current vertex being processed
            r: the root of the bicomp on which the Walkdown failed
            x,y: stopping vertices on bicomp rooted by r
            w: pertinent vertex on ext. face path below x and y
            px, py: attachment points of x-y path,
            z: Unused except in minors D and E (not needed in A, B, C).

            ux,dx: endpoints of unembedded edge that helps connext x with
                    ancestor of v
            uy,dy: endpoints of unembedded edge that helps connext y with
                    ancestor of v
            dw: descendant endpoint in unembedded edge to v
            uz,dz: endpoints of unembedded edge that helps connext z with
                    ancestor of v (for minors B and E, not A, C, D).
    */

    struct isolatorContextStruct
    {
        unsigned minorType;
        int v, r, x, y, w, px, py, z;
        int ux, dx, uy, dy, dw, uz, dz;
    };

    typedef struct isolatorContextStruct isolatorContextStruct;
    typedef isolatorContextStruct *isolatorContextP;

//********************************************************************
// A few simple integer selection macros for obstruction isolation
//********************************************************************
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN3(x, y, z) MIN(MIN((x), (y)), MIN((y), (z)))
#define MAX3(x, y, z) MAX(MAX((x), (y)), MAX((y), (z)))

/********************************************************************
 PERTINENT()
    A vertex is pertinent in a partially processed graph if there is an
    unprocessed back edge between the vertex v whose edges are currently
    being processed and either the vertex or a DFS descendant D of the
    vertex not in the same bicomp as the vertex.

    The vertex is either directly adjacent to v by an unembedded back edge
    or there is an unembedded back edge (v, D) and the vertex is a cut
    vertex in the partially processed graph along the DFS tree path from
    D to v.

    Pertinence is a dynamic property that can change for a vertex after
    each edge addition.  In other words, a vertex can become non-pertinent
    during step v as more back edges to v are embedded.

    NOTE: Pertinent roots are stored using the DFS children with which
    they are associated, so we test 'is vertex' (rather than virtual).
    ********************************************************************/
#define PERTINENT(theGraph, theVertex)                                      \
    (gp_IsEdge(theGraph, gp_GetVertexPertinentEdge(theGraph, theVertex)) || \
     gp_IsVertex(theGraph, gp_GetVertexPertinentRootsList(theGraph, theVertex)))

#define NOTPERTINENT(theGraph, theVertex)                                      \
    (gp_IsNotEdge(theGraph, gp_GetVertexPertinentEdge(theGraph, theVertex)) && \
     gp_IsNotVertex(theGraph, gp_GetVertexPertinentRootsList(theGraph, theVertex)))

/********************************************************************
 FUTUREPERTINENT()
    A vertex is future-pertinent in a partially processed graph if
    there is an unprocessed back edge between a DFS ancestor A of the
    vertex v whose edges are currently being processed and either
    theVertex or a DFS descendant D of theVertex not in the same bicomp
    as theVertex.

    Either theVertex is directly adjacent to A by an unembedded back edge
    or there is an unembedded back edge (A, D) and theVertex is a cut
    vertex in the partially processed graph along the DFS tree path from
    D to A.

    If no more edges are added to the partially processed graph prior to
    processing the edges of A, then the vertex would be pertinent.
    The addition of edges to the partially processed graph can alter
    both the pertinence and future pertinence of a vertex.  For example,
    if the vertex is pertinent due to an unprocessed back edge (v, D1) and
    future pertinent due to an unprocessed back edge (A, D2), then the
    vertex may lose both its pertinence and future pertinence when edge
    (v, D1) is added if D2 is in the same subtree as D1.

    Generally, pertinence and future pertinence are dynamic properties
    that can change for a vertex after each edge addition.

    Note that gp_UpdateVertexFuturePertinentChild() must be called before
    this macro. Since it is a statement and not a void expression, the
    desired commented out version does not compile (except with special
    compiler extensions not assumed by this code).
    ********************************************************************/
#define FUTUREPERTINENT(theGraph, theVertex, v)                                       \
    (theGraphDVI(theGraph)[theVertex].leastAncestor < v ||                            \
     (gp_IsVertex(theGraph, theGraphPVI(theGraph)[theVertex].futurePertinentChild) && \
      theGraphDVI(theGraph)[theGraphPVI(theGraph)[theVertex].futurePertinentChild].lowpoint < v))

#define NOTFUTUREPERTINENT(theGraph, theVertex, v)                                       \
    (theGraphDVI(theGraph)[theVertex].leastAncestor >= v &&                              \
     (gp_IsNotVertex(theGraph, theGraphPVI(theGraph)[theVertex].futurePertinentChild) || \
      theGraphDVI(theGraph)[theGraphPVI(theGraph)[theVertex].futurePertinentChild].lowpoint >= v))

/********************************************************************
 INACTIVE()
    For planarity algorithms, a vertex is inactive if it is neither pertinent
    nor future pertinent.
    ********************************************************************/
#define INACTIVE(theGraph, theVertex, v)  \
    (NOTPERTINENT(theGraph, theVertex) && \
     NOTFUTUREPERTINENT(theGraph, theVertex, v))

#ifdef __cplusplus
}
#endif

#endif /* GRAPHPLANARITY_PRIVATE_H */
