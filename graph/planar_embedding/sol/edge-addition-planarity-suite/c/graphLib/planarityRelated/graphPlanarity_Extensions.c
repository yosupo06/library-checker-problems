/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graphPlanarity.h"
#include "graphPlanarity.private.h"

#include <stdlib.h>

/****************************************************************************
 gp_ExtendWith_Planarity()

 This function is intended to subclass a DFSUtils Graph by extending it with
 the planar graph embedding and obstruction isolation capabilities and any
 additional required data structures. If the given graph has not already
 been extended with DFSUtils, then gp_ExtendWith_DFSUtils() is called.

 To use Planarity during gp_Embed(), use EMBEDFLAGS_PLANAR.

 Returns OK for success, NOTOK for failure.
 ****************************************************************************/

int gp_ExtendWith_Planarity(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    // If the Graph has already been extended with Planarity,
    // then just return successfully
    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_PLANARITY)
        return OK;

    // Ensure theGraph is a DFSUtils Graph
    if (gp_ExtendWith_DFSUtils(theGraph) != OK)
        return NOTOK;

    // Allocate supporting data structures as needed

    // Perform "on success" operations
    theGraph->graphFlags |= GRAPHFLAGS_EXTENDEDWITH_PLANARITY;
    return OK;
}

/********************************************************************
 gp_Detach_Planarity()

 This function is intended to disinherit the planar graph embedding and
 obstruction isolation feature by remove the extension from the graph,
 which also frees any planarity-specific data structures.

 Clears GRAPHFLAGS_EXTENDEDWITH_PLANARITY after detaching support
 for Planarity.

 Returns OK on success, NOTOK on failure
 ********************************************************************/

int gp_Detach_Planarity(graphP theGraph)
{
    // Free any data structures allocated by the ExtendWith function

    // Indicate successful detachment of Planarity
    theGraph->graphFlags &= ~GRAPHFLAGS_EXTENDEDWITH_PLANARITY;
    return OK;
}
