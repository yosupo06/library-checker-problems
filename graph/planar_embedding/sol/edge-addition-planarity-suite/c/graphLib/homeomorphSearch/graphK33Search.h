#ifndef GRAPH_K33SEARCH_H
#define GRAPH_K33SEARCH_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../planarityRelated/graphPlanarity.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Create a K33Search Graph, i.e., subclass a Planarity Graph by extending it with
// the ability to perform a search for a subgraph homeomorphic to K_{3,3}.
#define K33SEARCH_NAME "K33Search"

    int gp_ExtendWith_K33Search(graphP theGraph);
    int gp_Detach_K33Search(graphP theGraph);

#ifdef __cplusplus
}
#endif

#endif
