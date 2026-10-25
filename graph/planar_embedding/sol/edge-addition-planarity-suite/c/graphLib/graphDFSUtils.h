/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifndef GRAPHDFSUTILS_H
#define GRAPHDFSUTILS_H

#include "graph.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Create a DFSUtils Graph, i.e., subclass a Graph by extending it with the
// ability to perform the depth-first search (DFS) utility methods below.
#define DFSUTILS_NAME "DFSUtils"

        int gp_ExtendWith_DFSUtils(graphP theGraph);
        int gp_Detach_DFSUtils(graphP theGraph);

/* Graph Flags: see gp_GetGraphFlags()
        GRAPHFLAGS_EXTENDEDWITH_DFSUTILS is set by calling gp_ExtendWith_DFSUtils()
                This is automatically called by the utility methods below that create
                a DFS tree, sort vertices, and compute least ancestors and lowpoints
        GRAPHFLAGS_DFSNUMBERED is set if DFS numbering has been performed on the graph,
                such as by calling the gp_DepthFirstSearch() utility method below
        GRAPHFLAGS_SORTEDBYDFI records whether the graph is in original vertex order
                or sorted by depth first index. Successive calls to the
                gp_SortVertices() utility method below toggle this bit.
        GRAPHFLAGS_LOWPOINTSCOMPUTED records whether lowpoint calculations have
                been performed on the graph.
        GRAPHFLAGS_DFSNUMBERED_DIRECTED is set when a directed depth-first search
                performs the DFS numbering.
*/
#define GRAPHFLAGS_EXTENDEDWITH_DFSUTILS 256
#define GRAPHFLAGS_DFSNUMBERED 512
#define GRAPHFLAGS_SORTEDBYDFI 1024
#define GRAPHFLAGS_LOWPOINTSCOMPUTED 2048
#define GRAPHFLAGS_DFSNUMBERED_DIRECTED 4096

        // DFS-related utility methods that create a DFS tree, sort vertices and
        // compute least ancestor and lowpoint values
        int gp_DepthFirstSearch(graphP theGraph);
        int gp_DepthFirstSearchEx(graphP theGraph, unsigned mode);

#define DFSMODE_UNDIRECTED 1
#define DFSMODE_DIRECTED 2

        int gp_SortVertices(graphP theGraph);
        int gp_ComputeLowpoints(graphP theGraph);
        int gp_ComputeLeastAncestors(graphP theGraph);

        // Additional DFS-related uitility methods (functions and macros) that assume
        // one or more of the above methods have been called to create a DFS tree,
        // sort vertices and/or compute least ancestor and lowpoint values
        int gp_CountConnectedComponents(graphP theGraph);
        int gp_GetParent(graphP theGraph, int v);
        int gp_GetVisitedIndex(graphP theGraph, int v);
        int gp_GetLeastAncestor(graphP theGraph, int v);
        int gp_GetLowpoint(graphP theGraph, int v);

// A DFS tree root is one that has no DFS parent. There is one DFS tree root
// per connected component of a graph (connected, not biconnected; component, not bicomp)
#define gp_IsDFSTreeRoot(theGraph, v) gp_IsNotVertex(theGraph, gp_GetParent(theGraph, v))
#define gp_IsNotDFSTreeRoot(theGraph, v) gp_IsVertex(theGraph, gp_GetParent(theGraph, v))

// Mapping between bicomp roots and virtual vertex locations used to store them.
// A cut vertex v separates one or more of its DFS children, say c1 and c2, from
// the DFS parent and ancesstors of v. Because a DFS tree contains only tree edges
// and back edges, there are no cross edges connecting vertices in the DFS subtree
// rooted by c1, T(c1), with vertices in the DFS subtree rooted by c2, T(c2).
// We say that v is a cut vertex because the only paths that go from vertices in
// T(c1) to vertices in T(c2) are paths that contain v.
//
// Therefore, bicomp root copies of v, say R1 and R2, can be created at locations
// c1 and c2 in virtual vertex space, in other words at locations N+c1 and N+c2.
// The bicomps rooted by R1 and R2 are called child bicomps of v, and they contain,
// respectively, c1 and c2 as well as possibly more vertices from, respectively,
// T(c1) and T(c2), depending on what back edges may exist in the graph between
// pairs of vertices in, respectively, T(c1) and T(c2).
#define gp_GetBicompRootFromDFSChild(theGraph, c) ((c) + gp_GetN(theGraph))
#define gp_GetDFSChildFromBicompRoot(theGraph, R) ((R) - gp_GetN(theGraph))
#define gp_GetVertexFromBicompRoot(theGraph, R) gp_GetParent(theGraph, gp_GetDFSChildFromBicompRoot(theGraph, R))
#define gp_IsBicompRoot(theGraph, v) ((v) >= gp_LowerBoundVirtualVertices(theGraph))

// If a vertex v is a cut vertex that separates one of its DFS children, say c,
// from the DFS ancestors and other children of v, then when the graph has been
// separated into bicomps, there will be a root copy of v in virtual vertex space
// at location c+N that will have at least one edge connecting it to c.
// These macros detect whether or not that is the case for a given DFS child.
#define gp_IsSeparatedDFSChild(theGraph, theChild) (gp_VirtualVertexInUse(theGraph, gp_GetBicompRootFromDFSChild(theGraph, theChild)))
#define gp_IsNotSeparatedDFSChild(theGraph, theChild) (gp_VirtualVertexNotInUse(theGraph, gp_GetBicompRootFromDFSChild(theGraph, theChild)))

#ifdef __cplusplus
}
#endif

#endif /* GRAPHDFSUTILS_H */
