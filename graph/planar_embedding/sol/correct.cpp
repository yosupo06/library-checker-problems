// Model solution: planar embedding by the Boyer-Myrvold edge addition
// algorithm, using John M. Boyer's reference implementation, the Edge
// Addition Planarity Suite, vendored unmodified in edge-addition-planarity-suite/
// from tag Version_5.1.0.0:
// https://github.com/graph-algorithms/edge-addition-planarity-suite/tree/Version_5.1.0.0/c/graphLib
// See the README.md there for the list of files and the adaptations made in
// this file.
//
// The library's .c files are compiled as C++ in this single translation unit.
// Distributed under the BSD-3-Clause license, see
// edge-addition-planarity-suite/LICENSE.TXT.

#define USE_0BASEDARRAYS
#include "edge-addition-planarity-suite/c/graphLib/lowLevelUtils/apiutils.c"
#include "edge-addition-planarity-suite/c/graphLib/lowLevelUtils/listcoll.c"
#include "edge-addition-planarity-suite/c/graphLib/lowLevelUtils/stack.c"
// Apple's SDK marks sprintf() deprecated; sb_ConcatInt() in strbuf.c uses it.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "edge-addition-planarity-suite/c/graphLib/io/strbuf.c"
#pragma GCC diagnostic pop
#include "edge-addition-planarity-suite/c/graphLib/extensionSystem/graphExtensions.c"
#include "edge-addition-planarity-suite/c/graphLib/graph.c"
#include "edge-addition-planarity-suite/c/graphLib/graphDFSUtils.c"
// _gp_EmbedFlagsValid() passes `(void *)&context` to
// gp_FindExtension(graphP, int, void **): implicit in C, ill-formed in C++.
#define gp_FindExtension(theGraph, moduleID, pContext) \
    gp_FindExtension(theGraph, moduleID, static_cast<void **>(pContext))
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphEmbed.c"
#undef gp_FindExtension
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphNonplanar.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphIsolator.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphOuterplanarObstruction.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphOuterplanarity_Extensions.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphPlanarity_Extensions.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphPlanarity_Faces.c"
#include "edge-addition-planarity-suite/c/graphLib/planarityRelated/graphTests.c"

// Referenced by graph.c / graphEmbed.c but defined in files that are not
// vendored (the drawing and K_{2,3}/K_{3,3}/K_4 extensions and graph I/O).
// None of them is reached by gp_Embed(EMBEDFLAGS_PLANAR).
int DRAWPLANAR_ID = 0;
int K23SEARCH_ID = 0;
int K33SEARCH_ID = 0;
int K4SEARCH_ID = 0;
int _ReadPostprocess(graphP, char *) { return OK; }
int _WritePostprocess(graphP, char **) { return OK; }

#include <cstdlib>

#include "fastio.h"

int main() {
    library_checker::Scanner sc(stdin);
    library_checker::Printer pr(stdout);
    int T;
    sc.read(T);
    while (T--) {
        int N, M;
        sc.read(N, M);
        graphP g = gp_New();
        if (M > 0 && gp_EnsureEdgeCapacity(g, M) != OK) exit(1);
        if (gp_EnsureVertexCapacity(g, N) != OK) exit(1);
        for (int i = 0; i < M; i++) {
            int a, b;
            sc.read(a, b);
            if (gp_AddEdge(g, a, 0, b, 0) != OK) exit(1);
        }
        int r = gp_Embed(g, EMBEDFLAGS_PLANAR);
        if (r == OK) {
            // gp_Embed leaves the vertices in DFS order; restore the input numbering.
            if (gp_SortVertices(g) != OK) exit(1);
            pr.writeln("Yes");
            for (int v = gp_LowerBoundVertices(g); v < gp_UpperBoundVertices(g); v++) {
                bool first = true;
                for (int e = gp_GetFirstEdge(g, v); gp_IsEdge(g, e); e = gp_GetNextEdge(g, e)) {
                    if (!first) pr.write(' ');
                    first = false;
                    pr.write(gp_GetNeighbor(g, e));
                }
                pr.write('\n');
            }
        } else if (r == NONEMBEDDABLE) {
            pr.writeln("No");
        } else {
            exit(1);
        }
        gp_Free(&g);
    }
    return 0;
}
