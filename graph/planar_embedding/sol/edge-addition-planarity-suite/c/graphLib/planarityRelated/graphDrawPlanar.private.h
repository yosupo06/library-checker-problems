#ifndef GRAPH_DRAWPLANAR_PRIVATE_H
#define GRAPH_DRAWPLANAR_PRIVATE_H

/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "../planarityRelated/graphPlanarity.private.h"

#ifdef __cplusplus
extern "C"
{
#endif

        // Additional equipment for each edge
        /*
                pos, start, end: used to store a visibility representation, or
                        horvert diagram of a planar graph.
                        For edges, horizontal position, vertical range
        */
        typedef struct
        {
                int pos, start, end;
        } DrawPlanar_EdgeRec;

        typedef DrawPlanar_EdgeRec *DrawPlanar_EdgeRecP;

        // Additional equipment for each vertex
        /*
                pos, start, end: used to store a visibility representation, or
                        horvert diagram, of a planar graph.
                        For vertices, vertical position, horizontal range
                drawingFlag, ancestor, ancestorChild: used to collect information needed
                        to help 'draw' a visibility representation.  During planar
                        embedding, a vertex is determined to be between its DFS parent and
                        a given ancestor (the vertex being processed) or beyond the parent
                        relative to the ancestor. In post processing, the relative
                        orientation of the parent and ancestor are determined,
                        then the notion of between/beyond resolves to above/below or
                        below/above depending on whether the ancestor is above or below,
                        respectively, the parent.  The ancestorChild are used to help r
                        esolve this latter question.
                tie[2]  stores information along the external face during embedding
                        that is pertinent to helping break ties in the decisions about
                        vertical vertex positioning.  When vertices are first merged
                        together into a bicomp, we cannot always decide right away which
                        vertices will be above or below others.  But as we traverse the
                        external face removing inactive vertices, these positional ties
                        can be resolved.
        */
        typedef struct
        {
                int pos, start, end;
                int drawingFlag, ancestor, ancestorChild;
                int tie[2];
        } DrawPlanar_VertexInfo;

        typedef DrawPlanar_VertexInfo *DrawPlanar_VertexInfoP;

#define DRAWINGFLAG_BEYOND 0
#define DRAWINGFLAG_TIE 1
#define DRAWINGFLAG_BETWEEN 2
#define DRAWINGFLAG_BELOW 3
#define DRAWINGFLAG_ABOVE 4

        typedef struct
        {
                // Helps distinguish initialize from re-initialize
                int initialized;

                // Indicates that the visibility representation data is valid
                int drawingDataValid;

                // The graph that this context augments
                graphP theGraph;

                // Parallel array for additional edge level equipment
                DrawPlanar_EdgeRecP E;

                // Parallel array for additional vertex level equipment
                DrawPlanar_VertexInfoP VI;

                // Overloaded function pointers
                graphFunctionTableStruct functions;

        } DrawPlanarContext;

        extern int DRAWPLANAR_ID;

        int gp_GetDrawPlanarExtensionIdentifier(void);

#ifdef __cplusplus
}
#endif

#endif
