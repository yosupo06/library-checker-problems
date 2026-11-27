/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#include "graphPlanarity.h"
#include "graphPlanarity.private.h"
#include "../io/strbuf.h"

#include <stdlib.h>

static int _ClearEmbeddingFaceEdgeVisitedFlags(graphP theGraph)
{
    int e, eTwin;

    if (theGraph == NULL)
        return NOTOK;

    for (e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); e += 2)
    {
        if (gp_EdgeInUse(theGraph, e))
        {
            gp_ClearEdgeVisited(theGraph, e);
            eTwin = gp_GetTwin(theGraph, e);
            gp_ClearEdgeVisited(theGraph, eTwin);
        }
    }

    return OK;
}

static int _AppendEmbeddingFaceListHeader(strBufP faceList, int componentNumber)
{
    return sb_ConcatString(faceList, "Component_") == OK &&
                   sb_ConcatInt(faceList, componentNumber) == OK &&
                   sb_ConcatString(faceList, ": |\n") == OK
               ? OK
               : NOTOK;
}

static int _AppendEmbeddingFace(strBufP faceList, graphP theGraph, int eStart)
{
    int e = eStart, eNext, faceVertex, firstVertex = NIL, firstInFace = TRUE;

    if (sb_ConcatString(faceList, "    ") != OK)
        return NOTOK;

    do
    {
        faceVertex = gp_GetNeighbor(theGraph, gp_GetTwin(theGraph, e));

        if (firstInFace)
        {
            firstVertex = faceVertex;
            firstInFace = FALSE;
        }
        else if (sb_ConcatString(faceList, ", ") != OK)
            return NOTOK;

        if (sb_ConcatInt(faceList, faceVertex) != OK)
            return NOTOK;

        eNext = gp_GetNextEdgeCircular(theGraph, gp_GetTwin(theGraph, e));
        if (gp_GetEdgeVisited(theGraph, eNext))
            return NOTOK;

        gp_SetEdgeVisited(theGraph, eNext);
        e = eNext;
    } while (e != eStart);

    return sb_ConcatString(faceList, ", ") == OK &&
                   sb_ConcatInt(faceList, firstVertex) == OK &&
                   sb_ConcatChar(faceList, '\n') == OK
               ? OK
               : NOTOK;
}

/********************************************************************
 gp_CountEmbeddingFaces()

 Traverses all faces of a graph structure containing a planar embedding
 and returns the number of faces if the traversal succeeds and the face
 count agrees with the extended Euler formula. Returns -1 on error.
 ********************************************************************/

int gp_CountEmbeddingFaces(graphP theGraph)
{
    stackP theStack;
    int v, e, eTwin, eStart, eNext, NumFaces, connectedComponents;

    if (theGraph == NULL || !(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED))
        return -1;

    theStack = theGraph->theStack;
    if (theStack == NULL || sp_GetCapacity(theStack) < 2 * gp_GetM(theGraph))
        return -1;

    sp_ClearStack(theStack);

    for (e = gp_LowerBoundEdges(theGraph); e < gp_UpperBoundEdges(theGraph); e += 2)
    {
        if (gp_EdgeInUse(theGraph, e))
        {
            sp_Push(theStack, e);
            gp_ClearEdgeVisited(theGraph, e);

            eTwin = gp_GetTwin(theGraph, e);
            sp_Push(theStack, eTwin);
            gp_ClearEdgeVisited(theGraph, eTwin);
        }
    }

    if (sp_GetCurrentSize(theStack) != 2 * gp_GetM(theGraph))
        return -1;

    NumFaces = 0;
    while (sp_NonEmpty(theStack))
    {
        sp_Pop(theStack, eStart);
        if (gp_GetEdgeVisited(theGraph, eStart))
            continue;

        e = eStart;
        do
        {
            eNext = gp_GetNextEdgeCircular(theGraph, gp_GetTwin(theGraph, e));
            if (gp_GetEdgeVisited(theGraph, eNext))
                return -1;

            gp_SetEdgeVisited(theGraph, eNext);
            e = eNext;
        } while (e != eStart);

        NumFaces++;
    }

    connectedComponents = 0;
    for (v = gp_LowerBoundVertices(theGraph); v < gp_UpperBoundVertices(theGraph); ++v)
    {
        if (_gp_IsDFSTreeRoot(theGraph, v))
        {
            if (gp_GetVertexDegree(theGraph, v) > 0)
                NumFaces--;
            connectedComponents++;
        }
    }

    NumFaces++;

    return NumFaces == gp_GetM(theGraph) - gp_GetN(theGraph) + 1 + connectedComponents
               ? NumFaces
               : -1;
}

/********************************************************************
 gp_CreateEmbeddingFaceList()

 Creates a caller-owned YAML string containing one face list section per
 connected component of a graph structure containing a planar embedding.
 Returns OK on success, NOTOK on failure.
 ********************************************************************/

int gp_CreateEmbeddingFaceList(graphP theGraph, char **pFaceList)
{
    stackP theStack;
    strBufP faceList = NULL;
    int *visitedVertices = NULL, *componentEdges = NULL;
    int componentEdgesCapacity, componentNumber = 0, Result = OK;
    int lowerVertex, upperVertex, v;

    if (theGraph == NULL || pFaceList == NULL || *pFaceList != NULL)
        return NOTOK;

    if (!(gp_GetGraphFlags(theGraph) & GRAPHFLAGS_DFSNUMBERED) ||
        gp_CountEmbeddingFaces(theGraph) < 0 ||
        _ClearEmbeddingFaceEdgeVisitedFlags(theGraph) != OK)
    {
        return NOTOK;
    }

    lowerVertex = gp_LowerBoundVertices(theGraph);
    upperVertex = gp_UpperBoundVertices(theGraph);
    theStack = theGraph->theStack;
    componentEdgesCapacity = 2 * gp_GetM(theGraph);
    if (componentEdgesCapacity == 0)
        componentEdgesCapacity = 1;

    faceList = sb_New(0);
    visitedVertices = (int *)calloc((size_t)gp_UpperBoundVertexStorage(theGraph), sizeof(int));
    componentEdges = (int *)calloc((size_t)componentEdgesCapacity, sizeof(int));

    if (faceList == NULL || visitedVertices == NULL || componentEdges == NULL)
    {
        Result = NOTOK;
        goto gp_CreateEmbeddingFaceList_Cleanup;
    }

    for (v = lowerVertex; v < upperVertex; ++v)
    {
        int componentEdgeCount = 0, i;

        if (visitedVertices[v])
            continue;

        componentNumber++;
        if (_AppendEmbeddingFaceListHeader(faceList, componentNumber) != OK)
        {
            Result = NOTOK;
            goto gp_CreateEmbeddingFaceList_Cleanup;
        }

        sp_ClearStack(theStack);
        sp_Push(theStack, v);

        while (sp_NonEmpty(theStack))
        {
            int u, e;

            sp_Pop(theStack, u);
            if (visitedVertices[u])
                continue;

            visitedVertices[u] = TRUE;
            e = gp_GetFirstEdge(theGraph, u);
            while (gp_IsEdge(theGraph, e))
            {
                if (componentEdgeCount >= componentEdgesCapacity)
                    goto gp_CreateEmbeddingFaceList_Cleanup;

                componentEdges[componentEdgeCount++] = e;

                if (!visitedVertices[gp_GetNeighbor(theGraph, e)])
                    sp_Push(theStack, gp_GetNeighbor(theGraph, e));

                e = gp_GetNextEdge(theGraph, e);
            }
        }

        for (i = 0; i < componentEdgeCount; ++i)
        {
            if (!gp_GetEdgeVisited(theGraph, componentEdges[i]) &&
                _AppendEmbeddingFace(faceList, theGraph, componentEdges[i]) != OK)
            {
                Result = NOTOK;
                goto gp_CreateEmbeddingFaceList_Cleanup;
            }
        }
    }

    *pFaceList = sb_TakeString(faceList);
    Result = *pFaceList == NULL ? NOTOK : OK;

gp_CreateEmbeddingFaceList_Cleanup:

    if (componentEdges != NULL)
    {
        free(componentEdges);
        componentEdges = NULL;
    }

    if (visitedVertices != NULL)
    {
        free(visitedVertices);
        visitedVertices = NULL;
    }

    sb_Free(&faceList);

    if (Result != OK && pFaceList != NULL)
    {
        if (*pFaceList != NULL)
        {
            free(*pFaceList);
            *pFaceList = NULL;
        }
    }

    return Result;
}
