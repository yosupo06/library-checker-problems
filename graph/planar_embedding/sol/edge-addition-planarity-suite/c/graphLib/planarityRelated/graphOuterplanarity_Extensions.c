/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graphOuterplanarity.h"
#include "graphOuterplanarity.private.h"

#include <stdlib.h>

/****************************************************************************
 gp_ExtendWith_Outerplanarity()

 This function is intended to subclass a Planarity Graph by extending it with
 the outerplanar graph embedding and obstruction isolation capabilities.
 If the given graph has not already been extended with Planarity, then
 gp_ExtendWith_Planarity() is called.

 To use Outerplanarity during gp_Embed(), use EMBEDFLAGS_OUTERPLANAR.

 Returns OK for success, NOTOK for failure.
 ****************************************************************************/

int gp_ExtendWith_Outerplanarity(graphP theGraph)
{
    if (theGraph == NULL)
        return NOTOK;

    // If the Graph has already been extended with Outerplanarity,
    // then just return successfully
    if (gp_GetGraphFlags(theGraph) & GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY)
        return OK;

    // Ensure theGraph is a Planarity Graph
    if (gp_ExtendWith_Planarity(theGraph) != OK)
        return NOTOK;

    // Allocate supporting data structures as needed

    // Perform "on success" operations
    theGraph->graphFlags |= GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY;
    return OK;
}

/********************************************************************
 gp_Detach_Outerplanarity()

 This function is intended to disinherit the outerplanar graph embedding
 and obstruction isolation feature by removing the extension from the
 graph, which also frees any outerplanarity-specific data structures.

 Clears GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY after detaching support
 for Outerplanarity.

 Returns OK on success, NOTOK on failure
 ********************************************************************/

int gp_Detach_Outerplanarity(graphP theGraph)
{
    // Free any data structures allocated by the ExtendWith function

    // Indicate successful detachment of Outerplanarity
    theGraph->graphFlags &= ~GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY;
    return OK;
}
