#ifndef GRAPH_H
#define GRAPH_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#ifdef __cplusplus
extern "C"
{
#endif

// Basic declarations, such as for OK, NOTOK, and NIL
#include "lowLevelUtils/appconst.h"

    ///////////////////////////////////////////////////////////////////////////////
    // The top-level operations at the graph, vertex, and edge levels
    ///////////////////////////////////////////////////////////////////////////////

    // Forward declaration of graph structure and graph pointer type definitions
    // (see the end of this header file).
    typedef struct graphStruct graphStruct;
    typedef graphStruct *graphP;

    // Methods related to graph allocation and destruction
    graphP gp_New(void);

    int gp_EnsureVertexCapacity(graphP theGraph, int N);
    int gp_EnsureEdgeCapacity(graphP theGraph, int requiredEdgeCapacity);
    void gp_ResetGraphStorage(graphP theGraph);

    void gp_Free(graphP *pGraph);

// N=# of vertices; NV=# of virtual vertices; M=# of edges
#define gp_GetN(theGraph) ((theGraph)->N)
#define gp_GetNV(theGraph) ((theGraph)->NV)
#define gp_GetM(theGraph) ((theGraph)->M)
#define gp_GetEdgeCapacity(theGraph) ((theGraph)->edgeCapacity)

    // Basic graph utility methods
    int gp_CopyGraph(graphP dstGraph, graphP srcGraph);
    graphP gp_DupGraph(graphP theGraph);
    int gp_CopyAdjacencyLists(graphP dstGraph, graphP srcGraph);

    int gp_CreateRandomGraph(graphP theGraph);
    int gp_CreateRandomGraphEx(graphP theGraph, int numEdges);

    // Basic graph I/O methods: see graphIO.h
    // Intermediate graph I/O methods: see g6-read-iterator.h and g6-write-iterator.h

    // Basic vertex interrogators
    int gp_IsNeighbor(graphP theGraph, int u, int v);
    int gp_FindEdge(graphP theGraph, int u, int v);
    int gp_GetVertexDegree(graphP theGraph, int v);

    // Basic interrogators for directed graphs
    // The direction can be EDGEFLAG_DIRECTION_INONLY or EDGEFLAG_DIRECTION_OUTONLY
    int gp_IsNeighborDirected(graphP theGraph, int u, int v, unsigned direction);
    int gp_FindDirectedEdge(graphP theGraph, int u, int v, unsigned direction);
    int gp_GetVertexInDegree(graphP theGraph, int v);
    int gp_GetVertexOutDegree(graphP theGraph, int v);

    // Basic graph structure manipulators
    int gp_AddEdge(graphP theGraph, int u, int ulink, int v, int vlink);
    int gp_DynamicAddEdge(graphP theGraph, int u, int ulink, int v, int vlink);
    int gp_InsertEdge(graphP theGraph, int u, int e_u, int e_ulink,
                      int v, int e_v, int e_vlink);
    int gp_DynamicInsertEdge(graphP theGraph, int u, int e_u, int e_ulink,
                             int v, int e_v, int e_vlink);
    int gp_DeleteEdge(graphP theGraph, int e);
    int gp_ClearEdgeDirectionFlags(graphP theGraph);
    int gp_TransposeDirectedGraph(graphP theGraph);

    // Intermediate graph structure manipulators
    void gp_HideEdge(graphP theGraph, int e);
    void gp_RestoreEdge(graphP theGraph, int e);
    int gp_HideVertex(graphP theGraph, int vertex);
    int gp_RestoreVertex(graphP theGraph);

    // Advanced graph structure manipulators
    int gp_ContractEdge(graphP theGraph, int e);
    int gp_IdentifyVertices(graphP theGraph, int u, int v, int eBefore);
    int gp_RestoreVertices(graphP theGraph);

    // For methods and declarations related to depth-first search (DFS), see graphDFSUtils.h

/* Graph Flags (bit flags set by various public graphLib APIs):
        Bits 0-3 reserved for base graph class
        Bits 4-7 reserved for graph I/O
        Bits 8-15 reserved for DFS Utils
        Bits 16-23 reserved for Planarity-Related
        bits 24-31 reserved for future expansion
*/
#define GRAPHFLAGS_DIRECTEDEDGEDETECTED 1
#define gp_GetGraphFlags(theGraph) ((theGraph)->graphFlags)

    // For graph embedding methods and declarations, see graphPlanarity.h

    /********************************************************************
     Vertex Record Definition (For non-virtual and virtual vertices)

     This record definition provides the data members needed for the
     core structural information for both vertices and virtual vertices.
     Non-virtual vertices are also equipped with additional information
     provided by private vertexInfo records.

     The vertices of a graph are stored in the first N locations of array V.
     Virtual vertices are secondary vertices used to help represent the
     main vertices in substructural components of a graph (such as in
     biconnected components).

     link[2]: the first and last edge records in the adjacency list
              of the vertex.

     index: In vertices, stores either the depth first index of a vertex or
            the original array index of the vertex if the vertices of the
            graph are sorted by DFI.
            In virtual vertices, the index may be used to indicate the vertex
            that the virtual vertex represents, unless an algorithm has some
            other way of making the association (for example, the planarity
            algorithms rely on biconnected components and therefore place
            virtual vertices of a vertex at positions corresponding to the
            DFS children of the vertex).

     flags: Bits 0-15 reserved for library; bits 16 and higher for apps
            Bit 0: visited, for vertices and virtual vertices
            Bit 1: marked, 2nd visited flag, for while visiting all
                    Used in K4 homeomorph search algorithm
            Bit 2: Obstruction type VERTEX_TYPE_SET (versus not set, i.e. VERTEX_TYPE_UNKNOWN)
            Bit 3: Obstruction type qualifier RYW (set) versus RXW (clear)
            Bit 4: Obstruction type qualifier high (set) versus low (clear)
                    Bits 2-4 used in planarity-related algorithms
     ********************************************************************/

    struct vertexRec
    {
        int link[2];
        int index;
        unsigned flags;
    };

    typedef struct vertexRec vertexRec;
    typedef vertexRec *vertexRecP;

////////////////////////////////////////////
// Accessors for vertex adjacency list links
// such as for adjacency list iteration
// (see also gp_GetNextEdge and gp_IsEdge)
////////////////////////////////////////////
#define gp_GetFirstEdge(theGraph, v) (theGraph->V[v].link[0])
#define gp_GetLastEdge(theGraph, v) (theGraph->V[v].link[1])
#define gp_GetEdgeByLink(theGraph, v, theLink) (theGraph->V[v].link[theLink])

// Setters for adjacency list links
#define gp_SetFirstEdge(theGraph, v, newFirstEdge) (theGraph->V[v].link[0] = newFirstEdge)
#define gp_SetLastEdge(theGraph, v, newLastEdge) (theGraph->V[v].link[1] = newLastEdge)
#define gp_SetEdgeByLink(theGraph, v, theLink, newEdge) (theGraph->V[v].link[theLink] = newEdge)

///////////////////////////////////
// Vertex iteration-related methods
///////////////////////////////////

// The original N non-virtual vertices of a graph start at the lowest allowed storage location.
// The upper bound is one-past-the-end of the storage for the N non-virtual vertices.
#ifdef USE_1BASEDARRAYS
#define gp_LowerBoundVertices(theGraph) (1)
#else
#define gp_LowerBoundVertices(theGraph) (0)
#endif

#define gp_UpperBoundVertices(theGraph) (gp_LowerBoundVertexStorage(theGraph) + gp_GetN(theGraph))

// The virtual vertices start at the one-past-the-end upper bound of the non-virtual vertices.
// The upper bound is one-past-the-end of the virtual vertex storage locations.
#define gp_LowerBoundVirtualVertices(theGraph) gp_UpperBoundVertices(theGraph)
#define gp_UpperBoundVirtualVertices(theGraph) (gp_LowerBoundVertexStorage(theGraph) + gp_GetN(theGraph) + gp_GetNV(theGraph))

// These lower and upper bounds for all vertex storage are used for tasks like initializing
// that must iterate through all of non-virtual and virtual vertex records.
#define gp_LowerBoundVertexStorage(theGraph) gp_LowerBoundVertices(theGraph)
#define gp_UpperBoundVertexStorage(theGraph) gp_UpperBoundVirtualVertices(theGraph)

#ifdef USE_1BASEDARRAYS
// The use of *Vertex* alone consistently refers to the first N vertices.
// The use of *VirtualVertex* refers to vertex array locations after the first N.
#ifndef DEBUG
#define gp_IsVertex(theGraph, v) (v)
#define gp_IsVirtualVertex(theGraph, v) ((v) > gp_GetN(theGraph))
#else
// See below for definitions common to 1-based and 0-based
#endif

#else // Using 0-based Arrays
#ifndef DEBUG
#define gp_IsVertex(theGraph, v) ((v) != NIL)
#define gp_IsVirtualVertex(theGraph, v) ((v) >= gp_GetN(theGraph))
#else
// See below for definitions common to 1-based and 0-based
#endif
#endif // End of 0-based Arrays

// The same for 1-based and 0-based when debugging
#ifdef DEBUG
#define gp_IsVertex(theGraph, v) \
    ((v) == NIL ? 0 : ((v) < gp_LowerBoundVertices(theGraph) ? (NOTOK, 0) : ((v) >= gp_UpperBoundVertices(theGraph) ? (NOTOK, 0) : 1)))

// NOTE: gp_IsVirtualVertex() is sometimes called to distinguish between
// an existing non-virtual and a virtual
#define gp_IsVirtualVertex(theGraph, v)                                    \
    ((v) == NIL                                                            \
         ? 0                                                               \
         : ((v) < gp_LowerBoundVirtualVertices(theGraph)                   \
                ? ((v) < gp_LowerBoundVertices(theGraph) ? (NOTOK, 0) : 0) \
                : ((v) >= gp_UpperBoundVirtualVertices(theGraph) ? (NOTOK, 0) : 1)))

#endif

#define gp_IsNotVertex(theGraph, v) (!(gp_IsVertex(theGraph, v)))
#define gp_IsNotVirtualVertex(theGraph, v) (!(gp_IsVirtualVertex(theGraph, v)))

#define gp_VirtualVertexInUse(theGraph, virtualVertex) (gp_IsEdge(theGraph, gp_GetFirstEdge(theGraph, virtualVertex)))
#define gp_VirtualVertexNotInUse(theGraph, virtualVertex) (gp_IsNotEdge(theGraph, gp_GetFirstEdge(theGraph, virtualVertex)))
///////////////////////////////////////////
// End of Vertex iteration-related methods
//////////////////////////////////////////

// Accessors for non-virtual and virtual vertex index value
#define gp_GetIndex(theGraph, v) (theGraph->V[v].index)
#define gp_SetIndex(theGraph, v, theIndex) (theGraph->V[v].index = theIndex)

// Initializer for non-virtual and virtual vertex flags
#define gp_InitFlags(theGraph, v) (theGraph->V[v].flags = 0)

// Definition and accessors for the non-virtual and virtual vertex visited flag
#define VERTEX_VISITED_MASK 1
#define gp_GetVisited(theGraph, v) (theGraph->V[v].flags & VERTEX_VISITED_MASK)
#define gp_ClearVisited(theGraph, v) (theGraph->V[v].flags &= ~VERTEX_VISITED_MASK)
#define gp_SetVisited(theGraph, v) (theGraph->V[v].flags |= VERTEX_VISITED_MASK)

// Definition and accessors for the non-virtual and virtual vertex marked flag
// Essentially, this is a second visitation flag that can help applications that
// must visit all vertices to analyze and mark the ones important for some purpose.
#define VERTEX_MARKED_MASK 2
#define gp_GetMarked(theGraph, v) (theGraph->V[v].flags & VERTEX_MARKED_MASK)
#define gp_ClearMarked(theGraph, v) (theGraph->V[v].flags &= ~VERTEX_MARKED_MASK)
#define gp_SetMarked(theGraph, v) (theGraph->V[v].flags |= VERTEX_MARKED_MASK)

    /********************************************************************
     Edge Record Definition

     An edge is defined by a pair of edge records allocated in array E
     of a graph. A pair of edge records represents the edge in the
     adjacency lists of each vertex to which the edge is incident.

     link[2]: the next and previous edge records in the adjacency
              list that contains this edge record.

     v: The vertex neighbor of the vertex whose adjacency list contains
        this edge record (an index into array V).

     flags: Bits 0-15 reserved for library; bits 16 and higher for apps
            Bit 0: Visited
            Bit 1: Marked (2nd visited flag, for while visiting all)
            Bit 2: DFS type has been set, versus not set
            Bit 3: DFS tree edge, versus cycle edge (co-tree edge, etc.)
            Bit 4: DFS edge pointing to descendant, versus to ancestor
            Bit 5: Inverted (same as marking an edge with a "sign" of -1)
            Bit 6: Edge record is directed into the containing vertex only
            Bit 7: Edge record is directed from the containing vertex only
     ********************************************************************/

    struct edgeRec
    {
        int link[2];
        int neighbor;
        unsigned flags;
    };

    typedef struct edgeRec edgeRec;
    typedef edgeRec *edgeRecP;

// An edge is represented by two consecutive edge records in the edge array E.
// If an even number, xor 1 will add one; if an odd number, xor 1 will subtract 1
#define gp_GetTwin(theGraph, e) ((e) ^ 1)

////////////////////////////////////////////
// Access to adjacency list pointers
// such as for adjacency list iteration
////////////////////////////////////////////
#define gp_GetNextEdge(theGraph, e) (theGraph->E[e].link[0])
#define gp_GetPrevEdge(theGraph, e) (theGraph->E[e].link[1])
#define gp_GetAdjacentEdge(theGraph, e, theLink) (theGraph->E[e].link[theLink])

#define gp_SetNextEdge(theGraph, e, newNextEdge) (theGraph->E[e].link[0] = newNextEdge)
#define gp_SetPrevEdge(theGraph, e, newPrevEdge) (theGraph->E[e].link[1] = newPrevEdge)
#define gp_SetAdjacentEdge(theGraph, e, theLink, newEdge) (theGraph->E[e].link[theLink] = newEdge)

////////////////////////////////////////////
// gp_IsEdge() helps detect the end of an
// adjacency list iteration loop
////////////////////////////////////////////
#ifdef USE_1BASEDARRAYS
#define gp_IsEdge(theGraph, e) (e)
#define gp_IsNotEdge(theGraph, e) (!(e))
#else
#define gp_IsEdge(theGraph, e) ((e) != NIL)
#define gp_IsNotEdge(theGraph, e) ((e) == NIL)
#endif

// Get/set 'neighbor' member indicated by edge record e
#define gp_GetNeighbor(theGraph, e) (theGraph->E[e].neighbor)
#define gp_SetNeighbor(theGraph, e, v) (theGraph->E[e].neighbor = v)

// Initializer for edge flags
#define gp_InitEdgeFlags(theGraph, e) (theGraph->E[e].flags = 0)

// Definitions of and access to edge flags
#define EDGE_VISITED_MASK 1
#define gp_GetEdgeVisited(theGraph, e) (theGraph->E[e].flags & EDGE_VISITED_MASK)
#define gp_ClearEdgeVisited(theGraph, e) (theGraph->E[e].flags &= ~EDGE_VISITED_MASK)
#define gp_SetEdgeVisited(theGraph, e) (theGraph->E[e].flags |= EDGE_VISITED_MASK)

// Definition and accessors for the edge marked flag
// Essentially, this is a second visitation flag that can help applications that
// must visit all edges to analyze and mark the ones important for some purpose.
#define EDGE_MARKED_MASK 2
#define gp_GetEdgeMarked(theGraph, e) (theGraph->E[e].flags & EDGE_MARKED_MASK)
#define gp_ClearEdgeMarked(theGraph, e) (theGraph->E[e].flags &= ~EDGE_MARKED_MASK)
#define gp_SetEdgeMarked(theGraph, e) (theGraph->E[e].flags |= EDGE_MARKED_MASK)

// The edge type is defined by bits 2-4 and 8, 4+8+16+256=284
// Bit 2 set means the edge record neighbor field indicates a parent (in a
//       tree edge) or ancestor (in a "back" edge, aka a cotree edge)
// Bit 3 set means edge record is part of a "tree" edge whose endpoints share
//       the direct DFS parent/child relationship
// Bit 4 set means the edge record's neighbor field indicates either a child
//       (in a tree edge) or a descendant (in a "back" edge, aka "cotree" edge)
// Bit 5 set means the edge record is in a "cross" edge that is neither a
//       tree edge nor a back edge (so, bits 2, 3, and 4 are clear).
#define EDGE_TYPE_MASK 284

// EDGE_TYPE_NOTDEFINED - the edge record type has not been defined
#define EDGE_TYPE_NOTDEFINED 0

// EDGE_TYPE_TREE - gives a name to the bit indicating a tree edge
// EDGE_TYPE_PARENT - edge record neighbor field indicates DFS parent
// EDGE_TYPE_CHILD - edge record neighbor field indicates a DFS child
#define EDGE_TYPE_TREE 8
#define EDGE_TYPE_PARENT 12
#define EDGE_TYPE_CHILD 28

// EDGE_TYPE_BACK - edge record points to a DFS ancestor, not the DFS parent
// EDGE_TYPE_FORWARD - edge record points to a DFS descendant, not a DFS child
#define EDGE_TYPE_BACK 4
#define EDGE_TYPE_FORWARD 20

// EDGE_TYPE_CROSS - edge record and its twin represent a cross edge
//    Bit3 is not set because the edge is not a tree edge
//    Bits 2 and 4 are not set because the edge's endpoings are not
//        in a parent-or-ancestor/child-or-descendant relationship
#define EDGE_TYPE_CROSS 256

#define gp_GetEdgeType(theGraph, e) (theGraph->E[e].flags & EDGE_TYPE_MASK)
#define gp_ClearEdgeType(theGraph, e) (theGraph->E[e].flags &= ~EDGE_TYPE_MASK)
#define gp_SetEdgeType(theGraph, e, type) (theGraph->E[e].flags |= type)
#define gp_ResetEdgeType(theGraph, e, type) \
    (theGraph->E[e].flags = (theGraph->E[e].flags & ~EDGE_TYPE_MASK) | type)

#define EDGEFLAG_INVERTED_MASK 32
#define gp_GetEdgeFlagInverted(theGraph, e) (theGraph->E[e].flags & EDGEFLAG_INVERTED_MASK)
#define gp_SetEdgeFlagInverted(theGraph, e) (theGraph->E[e].flags |= EDGEFLAG_INVERTED_MASK)
#define gp_ClearEdgeFlagInverted(theGraph, e) (theGraph->E[e].flags &= (~EDGEFLAG_INVERTED_MASK))
#define gp_XorEdgeFlagInverted(theGraph, e) (theGraph->E[e].flags ^= EDGEFLAG_INVERTED_MASK)

#define EDGEFLAG_DIRECTION_INONLY 64
#define EDGEFLAG_DIRECTION_OUTONLY 128
#define EDGEFLAG_DIRECTION_MASK 192

// NOTE: Edge 'flags' bit 8 used by EDGE_TYPE_CROSS above,
//       so next available bit is bit 9 = 512

// Returns the direction, if any, of the edge record
#define gp_GetDirection(theGraph, e) (theGraph->E[e].flags & EDGEFLAG_DIRECTION_MASK)

// A direction of 0 clears directedness. Otherwise, edge record e is set
// to direction and e's twin edge record is set to the opposing setting.
#define gp_SetDirection(theGraph, e, direction)                                                   \
    {                                                                                             \
        if (direction == EDGEFLAG_DIRECTION_INONLY)                                               \
        {                                                                                         \
            theGraph->E[e].flags |= EDGEFLAG_DIRECTION_INONLY;                                    \
            theGraph->E[gp_GetTwin(theGraph, e)].flags |= EDGEFLAG_DIRECTION_OUTONLY;             \
            if (gp_GetNeighbor(theGraph, e) != gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e))) \
            {                                                                                     \
                theGraph->graphFlags |= GRAPHFLAGS_DIRECTEDEDGEDETECTED;                          \
            }                                                                                     \
        }                                                                                         \
        else if (direction == EDGEFLAG_DIRECTION_OUTONLY)                                         \
        {                                                                                         \
            theGraph->E[e].flags |= EDGEFLAG_DIRECTION_OUTONLY;                                   \
            theGraph->E[gp_GetTwin(theGraph, e)].flags |= EDGEFLAG_DIRECTION_INONLY;              \
            if (gp_GetNeighbor(theGraph, e) != gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e))) \
            {                                                                                     \
                theGraph->graphFlags |= GRAPHFLAGS_DIRECTEDEDGEDETECTED;                          \
            }                                                                                     \
        }                                                                                         \
        else                                                                                      \
        {                                                                                         \
            theGraph->E[e].flags &= ~EDGEFLAG_DIRECTION_MASK;                                     \
            theGraph->E[gp_GetTwin(theGraph, e)].flags &= ~EDGEFLAG_DIRECTION_MASK;               \
        }                                                                                         \
    }

// Iterate through all edges with gp_LowerBoundEdges, gp_UpperBoundEdges, and gp_EdgeInUse
#ifdef USE_1BASEDARRAYS
#define gp_LowerBoundEdges(theGraph) (2)
#define gp_UpperBoundEdges(theGraph) (gp_LowerBoundEdges(theGraph) + ((gp_GetM(theGraph) + (theGraph)->numEdgeHoles) << 1))

#define gp_EdgeInUse(theGraph, e) (gp_GetNeighbor(theGraph, e))
#define gp_EdgeNotInUse(theGraph, e) (!gp_GetNeighbor(theGraph, e))

#else
#define gp_LowerBoundEdges(theGraph) (0)
#define gp_UpperBoundEdges(theGraph) (gp_LowerBoundEdges(theGraph) + ((gp_GetM(theGraph) + (theGraph)->numEdgeHoles) << 1))

#define gp_EdgeInUse(theGraph, e) (gp_GetNeighbor(theGraph, e) != NIL)
#define gp_EdgeNotInUse(theGraph, e) (gp_GetNeighbor(theGraph, e) == NIL)
#endif

// These lower and upper bounds for edge storage are used for tasks like initializing that
// must iterate through all of the edge storage, including space not yet containing edges.
#define gp_LowerBoundEdgeStorage(theGraph) (gp_LowerBoundEdges(theGraph))
#define gp_UpperBoundEdgeStorage(theGraph) (gp_LowerBoundEdgeStorage(theGraph) + ((theGraph)->edgeCapacity << 1))

// The initial setting for the edge storage capacity expressed as a constant factor of N,
// which is the number of vertices in the graph. By default, array E is allocated enough
// space to contain 3N edges, which is 6N edge records, but this initial setting can be
// overridden using gp_EnsureEdgeCapacity(). It is especially efficient to change to ensure
// a higher edge capacity if done before calling gp_EnsureVertexCapacity() or gp_Read().
#define DEFAULT_EDGE_CAPACITY_FACTOR 3

// This value is returned by gp_AddEdge() and gp_InsertEdge() if adding or inserting
// the edge would exceed the edge capacity limit. The limit can be increased by
// calling gp_EnsureEdgeCapacity(), gp_DynamicAddEdge(), or gp_DynamicInsertEdge().
#define AT_EDGE_CAPACITY_LIMIT -1

// A bounds-checking version of gp_IsEdge() for DEBUG mode compilation
#ifdef DEBUG
#undef gp_IsEdge
#define gp_IsEdge(theGraph, e)                                                                    \
    ((e) == NIL                                                                                   \
         ? 0                                                                                      \
         : ((e) < gp_LowerBoundEdgeStorage(theGraph) || (e) >= gp_UpperBoundEdgeStorage(theGraph) \
                ? (NOTOK, 0)                                                                      \
                : 1))
#endif

    // Declaration of package-private data type for managing a
    // stack of integers
    typedef struct stackStruct stackStruct;
    typedef stackStruct *stackP;

    // Declaration of package private data types for extending the base Graph class
    // with subclasses having data members and function overloads
    typedef struct graphExtensionStruct graphExtensionStruct;
    typedef graphExtensionStruct *graphExtensionP;

    typedef struct graphFunctionTableStruct graphFunctionTableStruct;
    typedef graphFunctionTableStruct *graphFunctionTableP;

    /********************************************************************
         Graph structure definition
                V : Array of vertex records (allocated size N + NV)
                N : Number of non-virtual vertices (the "order" of the graph)
                NV: Number of virtual vertices (currently always equal to N)

                E : Array of edge records (edge records come in pairs and represent
                    an edge in each of the two vertex endpoints of the edge)
                M: Number of edges (the "size" of the graph)
                edgeCapacity: the maximum number of edges allowed in E
                edgeHoles: free locations in E where edges have been deleted
                numEdgeHoles: package private member indicating the number of edge holes.

                graphFlags: Additional state information about the graph
                embedFlags: records the type of embedding requested (uses EMBEDFLAGS)

                theStack: Used by methods of the base Graph class and its subclasses

                extensions: an object-oriented hierarchy of graph classes is implemented
                            manually as a list of extensions for data of any subclasses
                            with which a graph has been extended.
                extensionLookupTable: if not NULL, keeps an array of pointers to the
                                      extensions indexed by ID for constant-time lookup.
                functions: object-oriented class hierarchies includes virtual function
                           overloading, which is provided by this function pointer table.

                privateData: pointer to a package private data structure that can be
                             backwards compatibly changed in releases of graphLib.
        */

    struct graphStruct
    {
        vertexRecP V;
        int N, NV;

        edgeRecP E;
        int M, edgeCapacity;
        stackP edgeHoles;
        int numEdgeHoles;

        unsigned graphFlags, embedFlags;

        // Used by base Graph class and its subclasses
        stackP theStack;

        // Provides ability to subclass the base Graph,
        // including virtual function overloads by subclasses
        graphExtensionP extensions;
        graphExtensionP *extensionLookupTable;
        graphFunctionTableP functions;

        void *privateData;
    };

    typedef struct graphStruct graphStruct;
    typedef graphStruct *graphP;

#ifdef __cplusplus
}
#endif

#endif
