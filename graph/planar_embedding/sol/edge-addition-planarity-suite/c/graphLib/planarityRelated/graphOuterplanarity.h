#ifndef GRAPHOUTERPLANARITY_H
#define GRAPHOUTERPLANARITY_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graphPlanarity.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Create an Outerplanarity Graph, i.e., subclass a Planarity Graph by extending it
// with the ability to perform planar graph embedding and obstruction isolation.
#define OUTERPLANARITY_NAME "Outerplanarity"

    int gp_ExtendWith_Outerplanarity(graphP theGraph);
    int gp_Detach_Outerplanarity(graphP theGraph);

/* Graph Flags: see gp_GetGraphFlags()
        GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY is set by calling gp_ExtendWith_OuterPlanarity()
                This is automatically by gp_Embed() if not already done.
*/
#define GRAPHFLAGS_EXTENDEDWITH_OUTERPLANARITY 131072

#ifdef __cplusplus
}
#endif

#endif
