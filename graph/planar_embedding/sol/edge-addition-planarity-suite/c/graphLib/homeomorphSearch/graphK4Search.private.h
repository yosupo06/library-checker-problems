#ifndef GRAPH_K4SEARCH_PRIVATE_H
#define GRAPH_K4SEARCH_PRIVATE_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../planarityRelated/graphOuterplanarity.private.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Additional equipment for each EdgeRec

       pathConnector:
          Used in the edge records of a reduction edge to indicate the
          endpoints of a path that has been reduced from (removed from) the
          embedding so that the search for a K4 can continue.
          We only need a pathConnector because we reduce subgraphs that are
          separable by a 2-cut, so they can contribute at most one path to a
          subgraph homeomorphic to K4, if one is indeed found. Thus, we first
          delete all edges except for the desired path(s), then we reduce any
          retained path to an edge.
     */
    typedef struct
    {
        int pathConnector;
    } K4Search_EdgeRec;

    typedef K4Search_EdgeRec *K4Search_EdgeRecP;

    /* Additional equipment for each vertex: None */

    typedef struct
    {
        // Helps distinguish initialize from re-initialize
        int initialized;

        // The graph that this context augments
        graphP theGraph;

        // Parallel array for additional edge level equipment
        K4Search_EdgeRecP E;

        // Overloaded function pointers
        graphFunctionTableStruct functions;

        // Internal variable for converting a tail recursion into a simple loop
        int handlingBlockedBicomp;

    } K4SearchContext;

    extern int K4SEARCH_ID;

#ifdef __cplusplus
}
#endif

#endif
