#ifndef GRAPHPLANARITY_H
#define GRAPHPLANARITY_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../graphDFSUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Create a Planarity Graph, i.e., subclass a DFSUtils Graph by extending it with
// the ability to perform planar graph embedding and obstruction isolation.
#define PLANARITY_NAME "Planarity"

    int gp_ExtendWith_Planarity(graphP theGraph);
    int gp_Detach_Planarity(graphP theGraph);

/* Graph Flags: see gp_GetGraphFlags()
        GRAPHFLAGS_EXTENDEDWITH_PLANARITY is set by calling gp_ExtendWith_Planarity()
                This is automatically by gp_Embed() if not already done.
*/
#define GRAPHFLAGS_EXTENDEDWITH_PLANARITY 65536

    // Graph embedding and result validation methods
    // The embedResult output by gp_Embed() and input to gp_TestEmbedResultIntegrity()
    // can be OK if the graph is embedded or embeddable, NONEMBEDDABLE if a minimal
    // subgraph obstructing embedding has been isolated, or NOTOK on error
    int gp_Embed(graphP theGraph, unsigned embedFlags);
    int gp_TestEmbedResultIntegrity(graphP theGraph, graphP origGraph, int embedResult);

    // Graph embedding face enumeration and listing methods
    int gp_CountEmbeddingFaces(graphP theGraph);
    int gp_CreateEmbeddingFaceList(graphP theGraph, char **pFaceList);

// A return result value for gp_Embed() to indicate success prior to embedding completion,
// due to finding an obstruction to embedding.
#define NONEMBEDDABLE -1

// Below are the possible graph embedFlags to pass to gp_Embed() and which are
// then set into the graph by gp_Embed() and returned by this method.
#define gp_GetEmbedFlags(theGraph) ((theGraph)->embedFlags)

#define EMBEDFLAGS_PLANAR 1
#define EMBEDFLAGS_OUTERPLANAR 2

#define EMBEDFLAGS_DRAWPLANAR (4 | EMBEDFLAGS_PLANAR)

#define EMBEDFLAGS_SEARCHFORK23 (8 | EMBEDFLAGS_OUTERPLANAR)
#define EMBEDFLAGS_SEARCHFORK33 (16 | EMBEDFLAGS_PLANAR)
#define EMBEDFLAGS_SEARCHFORK4 (32 | EMBEDFLAGS_OUTERPLANAR)

// Reserve flag bits for possible future embedding-related extension modules
#define EMBEDFLAGS_SEARCHFORK5 (64 | EMBEDFLAGS_PLANAR)
#define EMBEDFLAGS_SEARCHFORK5MINOR (128 | EMBEDFLAGS_PLANAR)
#define EMBEDFLAGS_MAXIMALPLANARSUBGRAPH (256 | EMBEDFLAGS_PLANAR)
#define EMBEDFLAGS_PROJECTIVEPLANAR 512
#define EMBEDFLAGS_TOROIDAL 1024

    // After gp_Embed(), if the result is NONEMBEDDABLE, then this method
    // returns the obstructing minor type from the list below.
    // It is best to compare using a bitwise-and operation.
    unsigned gp_GetObstructionMinorType(graphP theGraph);

#define MINORTYPE_NONE 0
#define MINORTYPE_A 1
#define MINORTYPE_B 2
#define MINORTYPE_C 4
#define MINORTYPE_D 8
#define MINORTYPE_E 16
#define MINORTYPE_E1 32
#define MINORTYPE_E2 64
#define MINORTYPE_E3 128
#define MINORTYPE_E4 256

#define MINORTYPE_E5 512
#define MINORTYPE_E6 1024
#define MINORTYPE_E7 2048

#ifdef __cplusplus
}
#endif

#endif
