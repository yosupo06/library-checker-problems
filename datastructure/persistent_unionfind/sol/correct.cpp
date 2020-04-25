#include <cstdio>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <stack>
#include <cassert>
using namespace std;

struct RollBackUnionFind {
    using elem_tp = tuple<int, int, int, int>;

    vector<int> node, size_vec;
    stack<elem_tp> info;
    RollBackUnionFind(int N) : node(N), size_vec(N, 1) {
        for(int i=0; i<N; i++) node[i] = i;
    }

    int find(int u) {
        return node[u] == u ? u : find(node[u]);
    }
    int size(int u) {
        return size_vec[find(u)];
    }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        info.emplace(u, node[u], v, node[v]);
        if(u == v) return false;

        if(size(u) > size(v)) swap(u, v);
        node[u] = v;
        size_vec[v] += size_vec[u];
        return true;
    }
    int same(int u, int v) {
        return find(u) == find(v);
    }
    void rollback() {
        assert(info.size());
        int u, nu, v, nv; tie(u, nu, v, nv) = info.top(); info.pop();
        node[u] = nu, node[v] = nv;
    }
};

int main() {
    int N, Q; scanf("%d%d", &N, &Q);
    
    vector<int> t(Q+1), u(Q+1), v(Q+1), ans(Q+1);
    vector< vector<int> > queries(Q+1);
    for(int i=0; i<Q; i++) {
        int k; scanf("%d%d%d%d", &t[i+1], &k, &u[i+1], &v[i+1]); k++;
        queries[k].emplace_back(i+1);
    }

    RollBackUnionFind uf(N);
    auto dfs = [&](auto &&self, int cur) -> void {
        if(t[cur] == 0) {
            uf.unite(u[cur], v[cur]);
        }
        if(t[cur] == 1) {
            ans[cur] = uf.same(u[cur], v[cur]);
        }

        for(auto to : queries[cur]) {
            self(self, to);
        }
        
        if(t[cur] == 0) {
            uf.rollback();
        }
    };
    dfs(dfs, 0);

    for(int i=1; i<=Q; i++) if(t[i] == 1) printf("%d\n", ans[i]);
    return 0;
}
