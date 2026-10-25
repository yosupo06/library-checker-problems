#ifndef GRAPH_DRAWPLANAR_H
#define GRAPH_DRAWPLANAR_H

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

#define DRAWPLANAR_NAME "DrawPlanar"

    int gp_ExtendWith_DrawPlanar(graphP theGraph);
    int gp_Detach_DrawPlanar(graphP theGraph);

    int gp_DrawPlanar_RenderToFile(graphP theEmbedding, char *theFileName);
    int gp_DrawPlanar_RenderToString(graphP theEmbedding, char **pRenditionString);

    int gp_DrawPlanar_GetVertexPosition(graphP theEmbedding, int v);
    int gp_DrawPlanar_GetVertexStart(graphP theEmbedding, int v);
    int gp_DrawPlanar_GetVertexEnd(graphP theEmbedding, int v);

    int gp_DrawPlanar_GetEdgePosition(graphP theEmbedding, int e);
    int gp_DrawPlanar_GetEdgeStart(graphP theEmbedding, int e);
    int gp_DrawPlanar_GetEdgeEnd(graphP theEmbedding, int e);

    #ifdef __cplusplus
}
#endif

#endif
