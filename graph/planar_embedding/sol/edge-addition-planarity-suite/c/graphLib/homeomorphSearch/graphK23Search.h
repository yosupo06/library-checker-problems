#ifndef GRAPH_K23SEARCH_H
#define GRAPH_K23SEARCH_H

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

// Create a K23Search Graph, i.e., subclass an Outerplanarity Graph by extending it
// with the ability to perform a search for a subgraph homeomorphic to K_{2,3}.
#define K23SEARCH_NAME "K23Search"

    int gp_ExtendWith_K23Search(graphP theGraph);
    int gp_Detach_K23Search(graphP theGraph);

#ifdef __cplusplus
}
#endif

#endif
