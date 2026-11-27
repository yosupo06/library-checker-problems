#ifndef GRAPH_K4SEARCH_H
#define GRAPH_K4SEARCH_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../planarityRelated/graphOuterplanarity.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Create a K4Search Graph, i.e., subclass an Outerplanarity Graph by extending it
// with the ability to perform a search for a subgraph homeomorphic to K_4.
#define K4SEARCH_NAME "K4Search"

    int gp_ExtendWith_K4Search(graphP theGraph);
    int gp_Detach_K4Search(graphP theGraph);

#ifdef __cplusplus
}
#endif

#endif
