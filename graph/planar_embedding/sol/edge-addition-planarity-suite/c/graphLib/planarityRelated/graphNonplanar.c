/*
Copyright (c) 1997-2026, John M. Boyer
All rights reserved.
See the LICENSE.TXT file for licensing information.
*/

#define GRAPHNONPLANAR_C

// This source file implements subroutines of the main graph planarity method
#include "../planarityRelated/graphPlanarity.h"
#include "../planarityRelated/graphPlanarity.private.h"

/* Imported functions */

extern void _InitIsolatorContext(graphP theGraph);
extern int _ClearAllVisitedFlagsInBicomp(graphP theGraph, int BicompRoot);
extern int _ClearObstructionMarksInBicomp(graphP theGraph, int BicompRoot);
extern int _HideInternalEdges(graphP theGraph, int vertex);
extern int _RestoreInternalEdges(graphP theGraph, int stackBottom);

// extern int  _OrientVerticesInEmbedding(graphP theGraph);
extern int _OrientVerticesInBicomp(graphP theGraph, int BicompRoot, int PreserveSigns);

/* Private functions (exported to system) */

int _ChooseTypeOfNonplanarityMinor(graphP theGraph, int v, int R);
int _InitializeNonplanarityContext(graphP theGraph, int v, int R);

int _GetNeighborOnExtFace(graphP theGraph, int curVertex, int *pPrevLink);
void _FindActiveVertices(graphP theGraph, int R, int *pX, int *pY);
int _FindPertinentVertex(graphP theGraph);
int _SetVertexTypesForMarkingXYPath(graphP theGraph);

int _PopAndUnmarkVerticesAndEdges(graphP theGraph, int Z, int stackBottom);

int _MarkHighestXYPath(graphP theGraph);
int _MarkLowestXYPath(graphP theGraph);
int _MarkClosestXYPath(graphP theGraph, int targetVertex);
int _MarkZtoRPath(graphP theGraph);
int _FindFuturePertinenceBelowXYPath(graphP theGraph);

/****************************************************************************
 _gp_GetObstructionMinorType()
 ****************************************************************************/

unsigned gp_GetObstructionMinorType(graphP theGraph)
{
    if (theGraph == NULL || theGraphIC(theGraph) == NULL)
        return MINORTYPE_NONE;

    return theGraphIC(theGraph)->minorType;
}

/****************************************************************************
 _ChooseTypeOfNonplanarityMinor()
 ****************************************************************************/

int _ChooseTypeOfNonplanarityMinor(graphP theGraph, int v, int R)
{
    int W, Px, Py, Z;

    /* Create the initial non-planarity minor state in the isolator context */

    if (_InitializeNonplanarityContext(theGraph, v, R) != OK)
        return NOTOK;

    R = theGraphIC(theGraph)->r;
    W = theGraphIC(theGraph)->w;

    /* If the root copy is not a root copy of the current vertex v,
            then the Walkdown terminated because it couldn't find
            a viable path along a child bicomp, which is Minor A. */

    if (_gp_GetVertexFromBicompRoot(theGraph, R) != v)
    {
        theGraphIC(theGraph)->minorType |= MINORTYPE_A;
        return OK;
    }

    /* If W has a pertinent and future pertinent child bicomp, then we've found Minor B */
    // NOTE: Each pertinent root is stored as the DFS child with which it is
    //       associated, so we test gp_IsVertex, not gp_IsVirtualVertex here.
    if (gp_IsVertex(theGraph, gp_GetVertexPertinentRootsList(theGraph, W)))
    {
        if (gp_GetVertexLowpoint(theGraph, gp_GetVertexLastPertinentRootChild(theGraph, W)) < v)
        {
            theGraphIC(theGraph)->minorType |= MINORTYPE_B;
            return OK;
        }
    }

    /* Find the highest obstructing X-Y path */

    if (_MarkHighestXYPath(theGraph) != OK || theGraphIC(theGraph)->py == NIL)
        return NOTOK;

    Px = theGraphIC(theGraph)->px;
    Py = theGraphIC(theGraph)->py;

    /* If either point of attachment is 'high' (P_x closer to R than X
         or P_y closer to R than Y along external face), then we've
         matched Minor C. */

    if (gp_GetObstructionMark(theGraph, Px) == ANYVERTEX_OBSTRUCTIONMARK_HIGH_RXW ||
        gp_GetObstructionMark(theGraph, Py) == ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW)
    {
        theGraphIC(theGraph)->minorType |= MINORTYPE_C;
        return OK;
    }

    /* For Minor D, we search for a path from an internal
         vertex Z along the X-Y path up to the root R of the bicomp. */

    if (_MarkZtoRPath(theGraph) != OK)
        return NOTOK;

    if (gp_IsVertex(theGraph, theGraphIC(theGraph)->z))
    {
        theGraphIC(theGraph)->minorType |= MINORTYPE_D;
        return OK;
    }

    /* For Minor E, we search for an future pertinent vertex Z
         below the points of attachment of the X-Y path */

    Z = _FindFuturePertinenceBelowXYPath(theGraph);
    if (gp_IsVertex(theGraph, Z))
    {
        theGraphIC(theGraph)->z = Z;
        theGraphIC(theGraph)->minorType |= MINORTYPE_E;
        return OK;
    }

    return NOTOK;
}

/****************************************************************************
 _InitializeNonplanarityContext()

 This method finds the stopping vertices X and Y, and the pertinent vertex W
 of a bicomp rooted by vertex R.

 If R is NIL, the routine first determines which bicomp produced non-planarity
 condition.  If the stack is non-empty, then R is on the top of the stack.
 Otherwise, an unembedded edge from the fwdEdgeList of vertex v is used in
 combination with the sortedDFSChildList of v to determine R.

 If the parameter R was not NIL, then this method assumes it must operate
 only on the bicomp rooted by R, and it also assumes that the caller has
 not cleared the visited flags in the bicomp, so they are cleared.

 This routine imparts consistent orientation to all vertices in bicomp R
 since several subroutines count on this. The edge signs are preserved so that
 the original orientations of all vertices can be restored.  If the vertices
 of the embedding are already consistently oriented, then this operation
 simply has no effect.

 Finally, in the bicomp R, the vertex types of all non-root vertices on the
 external face are classified according to whether or not they are closer to
 the root R than X and Y along the external face paths (R X W) and (R Y W).
 ****************************************************************************/

int _InitializeNonplanarityContext(graphP theGraph, int v, int R)
{
    // Blank out the isolator context, then assign the input graph reference
    // and the current vertext v into the context.
    _InitIsolatorContext(theGraph);
    theGraphIC(theGraph)->v = v;

    // The bicomp root provided was the one on which the WalkDown was performed,
    // but in the case of Minor A, the central bicomp of the minor is at the top
    // of the stack, so R must be changed to that value.
    if (sp_NonEmpty(theGraph->theStack))
    {
        // The top of stack has the pair R and 0/1 direction Walkdown traversal proceeds from R
        // Need only R, so pop and discard the direction, then pop R
        sp_Pop2_Discard1(theGraph->theStack, R);
    }

    theGraphIC(theGraph)->r = R;

    // A number of subroutines require the main bicomp of the minor to be
    // consistently oriented and its visited flags clear.
    if (_OrientVerticesInBicomp(theGraph, R, 1) != OK)
    {
        return NOTOK;
    }

    if (_ClearAllVisitedFlagsInBicomp(theGraph, R) != OK)
        return NOTOK;

    // Now we find the active vertices along both external face paths
    // extending from R.
    _FindActiveVertices(theGraph, R, &theGraphIC(theGraph)->x, &theGraphIC(theGraph)->y);

    // Now, we obtain the pertinent vertex W on the lower external face
    // path between X and Y (that path that does not include R).
    theGraphIC(theGraph)->w = _FindPertinentVertex(theGraph);

    // Now we can classify the vertices along the external face of the bicomp
    // rooted at R as 'high RXW', 'low RXW', 'high RXY', 'low RXY'
    // NOTE: We do not need to set up for xy path identification when we
    //       have minor A, which occurs when the parent copy vertex of
    //       bicomp root R is a descendant of v (not v).
    if (_gp_GetVertexFromBicompRoot(theGraph, R) == v)
    {
        if (_SetVertexTypesForMarkingXYPath(theGraph) != OK)
            return NOTOK;
    }

    // All work is done, so return success
    return OK;
}

/********************************************************************
 _GetNeighborOnExtFace()

 Each vertex contains two 'link' index pointers that indicate the
 first and last adjacency list edges.  If the vertex is on the
 external face, then these two edges are also on the external face.
 We want to take one of those edges to get to the next vertex on the
 external face.

 On input *pPrevLink indicates which link we followed to arrive at
 curVertex.  On output *pPrevLink will be set to the link we follow to
 get into the next vertex.

 To get to the next vertex, we use the opposite link from the one used
 to get into curVertex.  This takes us to an edge record.  The twin
 of that edge record carries us to an edge record in the next vertex.
 At least one of the two links in that edge record will lead to a vertex
 node in G, which is the next vertex.  Once we arrive at the next
 vertex, at least one of its links will lead back to the edge record,
 and that link becomes the output value of *pPrevLink.

 NOTE: This method intentionally ignores the extFace optimization
       links. It is invoked when the "real" external face must be
       traversed and hence when the constant time guarantee is not
       needed from the extFace short-circuit that connects the
       bicomp root to the first active vertices along each external
       face path emanating from the bicomp root.
 ********************************************************************/

int _GetNeighborOnExtFace(graphP theGraph, int curVertex, int *pPrevLink)
{
    /* Exit curVertex from whichever link was not previously used to enter it */

    int e = gp_GetEdgeByLink(theGraph, curVertex, 1 ^ (*pPrevLink));
    int nextVertex = gp_GetNeighbor(theGraph, e);

    /* This if stmt assigns the new prev link that tells us which edge
       record was used to enter nextVertex (so that we exit from the
       opposing edge record).

       However, if we are in a singleton bicomp, then both links in nextVertex
       lead back to curVertex.  We want the two edge records of a singleton bicomp
       to act like a cycle, so we just don't change the prev link in this case.

       But when nextVertex has more than one edge, we need to figure out
       whether the first edge or last edge (which are the two on the external
       face) was used to enter nextVertex so we can exit from the other one
       as traversal of the external face continues later. */

    if (gp_GetFirstEdge(theGraph, nextVertex) != gp_GetLastEdge(theGraph, nextVertex))
        *pPrevLink = gp_GetTwin(theGraph, e) == gp_GetFirstEdge(theGraph, nextVertex) ? 0 : 1;

    return nextVertex;
}

/****************************************************************************
 _FindActiveVertices()

 Descends from the root of a bicomp R along both external face paths (which
 are indicated by the first and last edge records in R's adjacency list),
 returning the first active vertex appearing in each direction.
 ****************************************************************************/

void _FindActiveVertices(graphP theGraph, int R, int *pX, int *pY)
{
    int XPrevLink = 1, YPrevLink = 0, v = theGraphIC(theGraph)->v;

    *pX = _GetNeighborOnExtFace(theGraph, R, &XPrevLink);
    *pY = _GetNeighborOnExtFace(theGraph, R, &YPrevLink);

    // For planarity algorithms, advance past inactive vertices
    // For outerplanarity algorithms, ignore the notion of inactive vertices
    // since all vertices must remain on the external face.
    if (!(gp_GetEmbedFlags(theGraph) & EMBEDFLAGS_OUTERPLANAR))
    {
        gp_UpdateVertexFuturePertinentChild(theGraph, *pX, v);
        while (INACTIVE(theGraph, *pX, v))
        {
            *pX = _GetNeighborOnExtFace(theGraph, *pX, &XPrevLink);
            gp_UpdateVertexFuturePertinentChild(theGraph, *pX, v);
        }

        gp_UpdateVertexFuturePertinentChild(theGraph, *pY, v);
        while (INACTIVE(theGraph, *pY, v))
        {
            *pY = _GetNeighborOnExtFace(theGraph, *pY, &YPrevLink);
            gp_UpdateVertexFuturePertinentChild(theGraph, *pY, v);
        }
    }
}

/****************************************************************************
 _FindPertinentVertex()

 Get the first vertex after x. Since x was obtained using a prevlink of 1 on r,
 we use the same prevlink so we don't go back to R.
 Then, we proceed around the lower path until we find a vertex W that either
 has pertinent child bicomps or is directly adjacent to the current vertex v.
 ****************************************************************************/

int _FindPertinentVertex(graphP theGraph)
{
    int W = theGraphIC(theGraph)->x, WPrevLink = 1;

    W = _GetNeighborOnExtFace(theGraph, W, &WPrevLink);

    while (W != theGraphIC(theGraph)->y)
    {
        if (PERTINENT(theGraph, W))
            return W;

        W = _GetNeighborOnExtFace(theGraph, W, &WPrevLink);
    }

    return NIL;
}

/****************************************************************************
 _SetVertexTypesForMarkingXYPath()

 Label the vertices along the external face of the bicomp rooted at R as
 'high RXW', 'low RXW', 'high RXY', 'low RXY'
 ****************************************************************************/

int _SetVertexTypesForMarkingXYPath(graphP theGraph)
{
    int R, X, Y, W, Z, ZPrevLink, ZType;

    // Unpack the context for efficiency of loops
    R = theGraphIC(theGraph)->r;
    X = theGraphIC(theGraph)->x;
    Y = theGraphIC(theGraph)->y;
    W = theGraphIC(theGraph)->w;

    // Ensure basic preconditions of this routine are met
    if (gp_IsNotVirtualVertex(theGraph, R) || gp_IsNotVertex(theGraph, X) ||
        gp_IsNotVertex(theGraph, Y) || gp_IsNotVertex(theGraph, W))
    {
        return NOTOK;
    }

    // Clear the type member of each vertex in the bicomp
    if (_ClearObstructionMarksInBicomp(theGraph, R) != OK)
        return NOTOK;

    // Traverse from R to W in the X direction
    ZPrevLink = 1;
    Z = _GetNeighborOnExtFace(theGraph, R, &ZPrevLink);
    ZType = ANYVERTEX_OBSTRUCTIONMARK_HIGH_RXW;
    while (Z != W)
    {
        if (Z == X)
            ZType = ANYVERTEX_OBSTRUCTIONMARK_LOW_RXW;
        gp_ResetObstructionMark(theGraph, Z, ZType);
        Z = _GetNeighborOnExtFace(theGraph, Z, &ZPrevLink);
    }

    // Traverse from R to W in the Y direction
    ZPrevLink = 0;
    Z = _GetNeighborOnExtFace(theGraph, R, &ZPrevLink);
    ZType = ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW;
    while (Z != W)
    {
        if (Z == Y)
            ZType = ANYVERTEX_OBSTRUCTIONMARK_LOW_RYW;
        gp_ResetObstructionMark(theGraph, Z, ZType);
        Z = _GetNeighborOnExtFace(theGraph, Z, &ZPrevLink);
    }

    return OK;
}

/****************************************************************************
 _PopAndUnmarkVerticesAndEdges()

 Pop all vertex/edge pairs from the top of the stack up to a terminating
 vertex Z and mark as unvisited.  If Z is NIL, then all vertex/edge pairs
 are popped and marked as unvisited.
 The stackBottom indicates where other material besides the vertex/edge
 pairs may appear.
 ****************************************************************************/

int _PopAndUnmarkVerticesAndEdges(graphP theGraph, int Z, int stackBottom)
{
    int V, e;

    // Pop vertex/edge pairs until all have been popped from the stack,
    // and all that's left is what was under the pairs, or until...
    while (sp_GetCurrentSize(theGraph->theStack) > stackBottom)
    {
        sp_Pop(theGraph->theStack, V);

        // If we pop the terminating vertex Z, then put it back and break
        if (V == Z)
        {
            sp_Push(theGraph->theStack, V);
            break;
        }

        // Otherwise, pop the edge part of the vertex/edge pair
        sp_Pop(theGraph->theStack, e);

        // Now unmark the vertex and edge (i.e. revert to "unvisited")
        gp_ClearVisited(theGraph, V);
        gp_ClearEdgeVisited(theGraph, e);
        gp_ClearEdgeVisited(theGraph, gp_GetTwin(theGraph, e));
    }

    return OK;
}

/****************************************************************************
 _MarkHighestXYPath()

 Sets the visited flags on the highest X-Y path, i.e. the one closest to the
 root vertex R of the biconnected component containing X and Y as well as a
 pertinent vertex W that the Walkdown could not reach due to the future
 pertinent vertices X and Y being along both external face paths
 emanating from the root R.

 The caller receives an OK result if the method succeeded in operating or
 NOTOK on an internal failure. However, there may or may not be any X-Y path,
 in which case no visitation flags are set and the return result is still OK
 because the caller must decide whether the absence of an X-Y path is an
 operational error.

 This method also sets the isolator context's points of attachment on the
 external face of the marked X-Y path, if there was an X-Y path.  So, the
 caller can also use this call to decide if there was an X-Y path by
 testing whether theGraphIC(theGraph)->px and py have been set to non-NIL values.
 ****************************************************************************/

int _MarkHighestXYPath(graphP theGraph)
{
    return _MarkClosestXYPath(theGraph, theGraphIC(theGraph)->r);
}

/****************************************************************************
 _MarkLowestXYPath()

 Sets the visited flags on the lowest X-Y path, i.e. the one closest to the
 pertinent vertex W that the Walkdown could not reach due to future pertinent
 vertices X and Y along both external face paths emanating from the root R
 of the biconnected component containing W, X and Y.

 The caller receives an OK result if the method succeeded in operating or
 NOTOK on an internal failure. However, there may or may not be any X-Y path,
 in which case no visitation flags are set and the return result is still OK
 because the caller must decide whether the absence of an X-Y path is an
 operational error.

 This method also sets the isolator context's points of attachment on the
 external face of the marked X-Y path, if there was an X-Y path.  So, the
 caller can also use this call to decide if there was an X-Y path by
 testing whether theGraphIC(theGraph)->px and py have been set to non-NIL values.
 ****************************************************************************/

int _MarkLowestXYPath(graphP theGraph)
{
    return _MarkClosestXYPath(theGraph, theGraphIC(theGraph)->w);
}

/****************************************************************************
 _MarkClosestXYPath()

 This method searches for and marks the X-Y path in the bicomp rooted by R
 that is either closest to R (highest) or closest to W (lowest). This method
 will return NOTOK if the targetVertex parameter is other than R or W.

 The closest X-Y path is the path through the inside of the bicomp that
 only attaches to the external face at its two endpoint vertices and
 those endpoints are closer along the external face path emanating from
 the targetVertex than the attachment points of any other X-Y path.

 This method returns NOTOK if there is an internal processing error and
 otherwise it returns OK. If there is no X-Y path, the method still returns
 OK to indicate no internal failures, but on return the caller can detect
 whether there was an X-Y path by testing whether the attachment points in
 the isolator context have been set to non-NIL values. Specifically, test
 whether theGraphIC(theGraph)->px and py have been set to non-NIL values. The caller
 must decide whether the absence of an X-Y path is an error. For example,
 in core planarity, the proof of correctness guarantees an X-Y path exists
 by the time this method is called, so that caller would decide to return
 NOTOK since there should be an X-Y path.

 If there is an X-Y path, it is marked using the visited flags on the
 vertices and edges.

 PRECONDITION: During non-planarity context initialization, the vertices along
 the external face (other than R and W) have been classified as 'high RXW',
 'low RXW', 'high RXY', or 'low RXY'. Once the vertices have been categorized,
 we proceed with trying to set the visitation flags of vertices and edges.
 First, we remove all edges incident to the targetVertex, except the two edges
 that join it to the external face. The result is that the targetVertex and its
 two remaining edges are a 'corner' in the external face but also in a single
 proper face whose boundary includes the X-Y path with the closest attachment
 points. Thus, we simply need to walk this proper face to find the desired
 X-Y path. Note, however, that the resulting face boundary may have attached
 cut vertices.  Any such separable component contains a vertex neighbor of
 the targetVertex, but the edge to the targetVertex has been temporarily hidden.
 The algorithm removes loops of vertices and edges along the proper face so
 that only the desired path is identified.

 To walk the proper face containing the targetVertex, we first identify an
 edge record that will be considered to be the one used to enter the targetVertex.
 When the first loop iteration exits the targetVertex, it comes out on the
 RXW side (even though it may be an internal vertex not marked RXW).
 Then we take either the next edge (if targetVertex==W) or previous edge
 (if targetVertex==R) at every subsequent corner to determine the edge record
 to use to exit the vertex. Then, we use the twin of the exit edge record to
 determine the edge record to use to enter the next vertex.

 For each vertex, we mark as visited the vertex as well as both edge records
 of the edge used to enter the vertex. We also push the visited vertices and
 edges onto a stack. Each time the traversal lands on an external face
 vertex on the RXW side, it is recorded as a candidate point of attachment Px.
 We also pop and unmark all previously visited vertices and edges because they
 are now known to not be part of the internal X-Y path after encountering the
 point of attachment. Instead, these preceding edges and vertices were part
 of a path parallel to the external face that does not obstruct the space
 between R and W inside the bicomp.

 As we walk the proper face, we keep track of the last vertex P_x we visited of
 type RXW (high or low). If we encounter antipodalVertex of the targetVertex
 (i.e., W if the targetVertex is R, or R if the targetVertex is W), then there
 is no obstructing X-Y path since we removed only edges incident to the
 targetVertex, so we pop the stack unmarking everything then clear the
 X-Y path points of attachment in the isolator context so the caller will know
 that no X-Y path was found (and then we return OK since there was no internal
 error).

 If, during the traversal, we encounter a vertex Z previously visited, then we
 pop the stack, unmarking the vertices and edges popped, until we find the
 prior occurrence of Z on the stack. This is because we have traversed a path
 that would connect back to the targetVertex had we not hidden the internal
 edges of the targetVertex.

 Otherwise, the first time we encounter a vertex of type 'RYW', we stop
 because the obstructing X-Y path has been marked visited and its points of
 attachment to the external face have been found. This second point of
 attachment Py is stored in the isolator context.

 Once the X-Y path is identified (or once we have found that there is no
 X-Y path), we restore the previously hidden edges incident to the targetVertex.

 This method uses the stack, but it preserves any prior content.
 The stack space used is no greater than 3N.  The first N accounts for hiding
 the edges incident to the targetVertex.  The other 2N accounts for the fact
 that each iteration of the main loop visits a vertex, pushing its index and
 the location of an edge record.  If a vertex is encountered that is already
 on the stack, then it is not pushed again (and in fact part of the stack
 is removed).

 Returns OK on successful operation and NOTOK on internal failure.
 Also, if an X-Y path is found (which will be the closest), then
 the graph isolator context contains its attachment points on the
 external face of the bicomp rooted by R, and the edges and vertices
 in the X-Y path will have been marked visited.
 ****************************************************************************/

int _MarkClosestXYPath(graphP theGraph, int targetVertex)
{
    int e, Z;
    int R, W, antipodalVertex;
    int stackBottom1, stackBottom2;

    /* Initialization */

    R = theGraphIC(theGraph)->r;
    W = theGraphIC(theGraph)->w;
    theGraphIC(theGraph)->px = theGraphIC(theGraph)->py = NIL;

    /* This method only makes sense for a targetVertex of R or W */
    if (targetVertex != R && targetVertex != W)
        return NOTOK;

    /* The vertex opposite the targetVertex is needed to detect when
       there is no X-Y path */

    antipodalVertex = targetVertex == R ? W : R;

    /* Save the stack bottom before we start hiding internal edges, so
       we will know how many edges to restore */

    stackBottom1 = sp_GetCurrentSize(theGraph->theStack);

    /* Remove the internal edges incident to targetVertex (R or W) */

    if (_HideInternalEdges(theGraph, targetVertex) != OK)
        return NOTOK;

    /* Now we're going to use the stack to collect the vertices of potential
     * X-Y paths, so we need to store where the hidden internal edges are
     * located because we must, at times, pop the collected vertices if
     * the path being collected doesn't work out. */

    stackBottom2 = sp_GetCurrentSize(theGraph->theStack);

    /* Walk the proper face containing targetVertex to find and mark the
        closest X-Y path.  */

    Z = targetVertex;

    // Now we will get the edge considered to be the one used to enter
    // the targetVertex. This will be an edge on the RYW side, and the
    // first line of the loop code will get the previous or next edge
    // that will be used to exit the targetVertex on the RXW side of the
    // bicomp (that one operation to get previous or next, circular, will
    // switch sides because all internal edges of targetVertex are hidden).
    e = targetVertex == R ? gp_GetLastEdge(theGraph, R) : gp_GetFirstEdge(theGraph, W);

    while (gp_GetObstructionMark(theGraph, Z) != ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW &&
           gp_GetObstructionMark(theGraph, Z) != ANYVERTEX_OBSTRUCTIONMARK_LOW_RYW)
    {
        /* Advance e and Z along the proper face containing the targetVertex */

        // Get the opposing edge of the corner at vertex Z, as the edge to exit Z
        e = targetVertex == R ? gp_GetPrevEdgeCircular(theGraph, e)
                              : gp_GetNextEdgeCircular(theGraph, e);

        // Now use the exit edge record to get the next Z to visit
        Z = gp_GetNeighbor(theGraph, e);

        // And get the entry edge record of the new Z being visited
        e = gp_GetTwin(theGraph, e);

        /* If Z is already visited, then pop everything since the last time
              we visited Z because its all part of a separable component. */

        if (gp_GetVisited(theGraph, Z))
        {
            if (_PopAndUnmarkVerticesAndEdges(theGraph, Z, stackBottom2) != OK)
                return NOTOK;
        }

        /* If we have not visited this vertex before... */

        else
        {
            /* If we find the antipodalVertex of the targetVertex (W if R, R if W),
               then there is no X-Y path. Never happens for Kuratowski subgraph
               isolator, but this routine is also used to test for certain X-Y paths.
               So, we clean up and bail out in that case. */

            if (Z == antipodalVertex)
            {
                if (_PopAndUnmarkVerticesAndEdges(theGraph, NIL, stackBottom2) != OK)
                    return NOTOK;
                break;
            }

            /* If we found another vertex along the RXW path, then blow off
               all the vertices we visited so far because they're not part of
               the obstructing path */

            if (gp_GetObstructionMark(theGraph, Z) == ANYVERTEX_OBSTRUCTIONMARK_HIGH_RXW ||
                gp_GetObstructionMark(theGraph, Z) == ANYVERTEX_OBSTRUCTIONMARK_LOW_RXW)
            {
                theGraphIC(theGraph)->px = Z;
                if (_PopAndUnmarkVerticesAndEdges(theGraph, NIL, stackBottom2) != OK)
                    return NOTOK;
            }

            /* Push the current vertex onto the stack of vertices visited
               since the last RXW vertex was encountered */

            sp_Push(theGraph->theStack, e);
            sp_Push(theGraph->theStack, Z);

            /* Mark the vertex Z as visited as well as its edge of entry
               (except the entry edge for P_x).*/

            gp_SetVisited(theGraph, Z);
            if (Z != theGraphIC(theGraph)->px)
            {
                gp_SetEdgeVisited(theGraph, e);
                gp_SetEdgeVisited(theGraph, gp_GetTwin(theGraph, e));
            }

            /* If we found an RYW vertex, then we have successfully finished
               identifying the closest X-Y path, so we record the point of
               attachment and break the loop. */

            if (gp_GetObstructionMark(theGraph, Z) == ANYVERTEX_OBSTRUCTIONMARK_HIGH_RYW ||
                gp_GetObstructionMark(theGraph, Z) == ANYVERTEX_OBSTRUCTIONMARK_LOW_RYW)
            {
                theGraphIC(theGraph)->py = Z;
                break;
            }
        }
    }

    /* Remove any remaining vertex-edge pairs on the top of the stack, then
        Restore the internal edges incident to R that were previously removed. */

    sp_SetCurrentSize(theGraph->theStack, stackBottom2);

    if (_RestoreInternalEdges(theGraph, stackBottom1) != OK)
        return NOTOK;

    /* Return the result */

    if (!gp_IsVertex(theGraph, theGraphIC(theGraph)->py))
        theGraphIC(theGraph)->px = NIL;

    return OK;
}

/****************************************************************************
 _MarkZtoRPath()

 This function assumes that _MarkHighestXYPath() has already been called,
 which marked as visited the vertices and edges along the X-Y path.

 We begin at the point of attachment P_x, take its last edge and traverse
 the predecessor edges until we find one marked visited, which leads to the
 first internal vertex along the X-Y path.  We begin with this vertex
 (and its edge of entry), and we run until we find P_y. For each internal
 vertex Z and its edge of entry ZPrevEdge, we take the predecessor edge record
 of ZPrevEdge, called ZNextEdge. If ZNextEdge is marked visited then it is
 along the X-Y path, so we use it to exit Z and go to the next vertex on the
 X-Y path.

 If ZNextEdge is not visited, then when _MarkHighestXYPath() ran, it exited
 Z from ZNextedge, then eventually reentered Z.  In other words, Z became a
 cut vertex when we removed the internal edges incident to R. Thus, ZNextEdge
 indicates the first edge in an internal path to R.

 When we find an unvisited ZNextEdge, we stop running the X-Y path and instead
 begin marking the Z to R path.  We move to successive vertices using a
 twin edge record then its predecessor in the adjacency list, only this time
 we have not removed the internal edges incident to R, so this technique does
 eventually lead us all the way to R.

 If we do not find an unvisited ZNextEdge for any vertex Z on the X-Y path and
 inside the bicomp, then there is no Z to R path, so we return.

 Returns OK if a Z-to-R path has been marked or if it has been found that
            there is not a Z-to-R path; returns NOTOK on error
 ****************************************************************************/

int _MarkZtoRPath(graphP theGraph)
{
    int ZPrevEdge, ZNextEdge, Z, R, Px, Py;

    /* Initialize */

    R = theGraphIC(theGraph)->r;
    Px = theGraphIC(theGraph)->px;
    Py = theGraphIC(theGraph)->py;
    theGraphIC(theGraph)->z = NIL;

    /* Begin at Px and search its adjacency list for the edge leading to
       the first internal vertex of the X-Y path. */

    Z = Px;
    ZNextEdge = gp_GetLastEdge(theGraph, Z);
    while (ZNextEdge != gp_GetFirstEdge(theGraph, Z))
    {
        if (gp_GetEdgeVisited(theGraph, ZNextEdge))
            break;

        ZNextEdge = gp_GetPrevEdge(theGraph, ZNextEdge);
    }

    if (!gp_GetEdgeVisited(theGraph, ZNextEdge))
        return NOTOK;

    /* For each internal vertex Z, determine whether it has a path to root. */

    while (gp_GetEdgeVisited(theGraph, ZNextEdge))
    {
        ZPrevEdge = gp_GetTwin(theGraph, ZNextEdge);
        ZNextEdge = gp_GetPrevEdgeCircular(theGraph, ZPrevEdge);
    }

    ZPrevEdge = gp_GetTwin(theGraph, ZNextEdge);
    Z = gp_GetNeighbor(theGraph, ZPrevEdge);

    /* If there is no Z to R path, return */

    if (Z == Py)
        return OK;

    /* Otherwise, store Z in the isolation context */

    theGraphIC(theGraph)->z = Z;

    /* Walk the proper face starting with (Z, ZNextEdge) until we reach R, marking
            the vertices and edges encountered along the way, then Return OK. */

    while (Z != R)
    {
        /* If we ever encounter a non-internal vertex (other than the root R),
                then corruption has occurred, so we return NOTOK */

        if (gp_GetObstructionMark(theGraph, Z) != ANYVERTEX_OBSTRUCTIONMARK_UNMARKED)
            return NOTOK;

        /* Go to the next vertex indicated by ZNextEdge */

        Z = gp_GetNeighbor(theGraph, ZNextEdge);

        /* Mark the next vertex and the edge leading to it as visited. */

        gp_SetEdgeVisited(theGraph, ZNextEdge);
        gp_SetEdgeVisited(theGraph, ZPrevEdge);
        gp_SetVisited(theGraph, Z);

        /* Go to the next edge in the proper face */

        ZNextEdge = gp_GetPrevEdgeCircular(theGraph, ZPrevEdge);
        ZPrevEdge = gp_GetTwin(theGraph, ZNextEdge);
    }

    /* Found Z to R path, so indicate as much to caller */

    return OK;
}

/****************************************************************************
 _FindFuturePertinenceBelowXYPath()

 Get a future pertinent vertex along the lower external face path between
 the points of attachment P_x and P_y of a 'low' X-Y Path.
 NOTE: By the time this function is called, Px and Py have already been found
        to be at or below X and Y.
 ****************************************************************************/

int _FindFuturePertinenceBelowXYPath(graphP theGraph)
{
    int Z = theGraphIC(theGraph)->px, ZPrevLink = 1,
        Py = theGraphIC(theGraph)->py, v = theGraphIC(theGraph)->v;

    Z = _GetNeighborOnExtFace(theGraph, Z, &ZPrevLink);

    while (Z != Py)
    {
        gp_UpdateVertexFuturePertinentChild(theGraph, Z, v);
        if (FUTUREPERTINENT(theGraph, Z, v))
            return Z;

        Z = _GetNeighborOnExtFace(theGraph, Z, &ZPrevLink);
    }

    return NIL;
}
