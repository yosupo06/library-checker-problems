#pragma once
#include "graph.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

namespace nachia{

template<
    class S,
    class RakeFunc,
    class CompressFunc,
    typename std::enable_if_t<std::is_invocable_r_v<S, RakeFunc, S, S>, void*> = nullptr,
    typename std::enable_if_t<std::is_invocable_r_v<S, CompressFunc, S, int, int>, void*> = nullptr
>
class AnyDirectionTreeDP{
private:
    std::vector<S> low;
    std::vector<S> high;
    std::vector<int> XorEdge;
    std::vector<int> P;
    RakeFunc rake;
    CompressFunc compress;

public:

    // S rake(S a, S b)
    // S compress(S a, int edgeIndex, int newRoot)
    AnyDirectionTreeDP(const Graph& tree, std::vector<S> node, RakeFunc _rake, CompressFunc _compress)
        : rake(std::move(_rake))
        , compress(std::move(_compress))
    {
        int n = tree.numVertices();
        auto adj = tree.getEdgeIndexArray(true);
        XorEdge.resize(n-1);
        for(int i=0; i<n-1; i++) XorEdge[i] = tree[i].from ^ tree[i].to;
        std::vector<int> bfs(n, 0);
        int bfsi = 1;
        P.assign(n, -1);
        for(int v : bfs){
            for(int e : adj[v]){
                int w = v ^ XorEdge[e];
                if(P[v] != e){ P[w] = e; bfs[bfsi++] = w; }
            }
        }
        low = node;
        for(int i=n-1; i>=1; i--){
            int w = bfs[i];
            int v = w ^ XorEdge[P[w]];
            low[v] = rake(low[v], compress(low[w], P[w], v));
        }
        
        high = node;
        for(int i=0; i<n; i++){
            int v = bfs[i];
            int C = adj[v].size();
            S fold = node[0];
            if(v != 0) fold = compress(high[v], P[v], v);
            for(int ci=C-1; ci>=0; ci--){
                int e = adj[v][ci];
                if(P[v] == e) continue;
                int w = v ^ XorEdge[e];
                high[w] = fold;
                fold = rake(compress(low[w], e, v), fold);
            }
            fold = node[v];
            for(int ci=0; ci<C; ci++){
                int e = adj[v][ci];
                if(P[v] == e) continue;
                int w = v ^ XorEdge[e];
                high[w] = rake(high[w], fold);
                fold = rake(fold, compress(low[w], e, v));
            }
        }
    }

    S getAtVtx(int i){
        if(i == 0) return low[i];
        return rake(compress(high[i], P[i], i), low[i]);
    }
};

} // namespace nachia
