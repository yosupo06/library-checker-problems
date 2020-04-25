#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <stack>
#include <cassert>
#include "random.h"
#include "../params.h"
using namespace std;

struct QuickFind {
    vector<int> v_to_s;
    vector< vector<int> > s_to_vs;
    stack< tuple<int, int, int> > info;
    set< pair<int, int> > pq;
    
    QuickFind(int N) : v_to_s(N), s_to_vs(N) {
        for(int i=0; i<N; i++) {
            v_to_s[i] = i;
            s_to_vs[i].emplace_back(i);
            pq.emplace(-1, i);
        }
    }

    int find(int v) {
        if(v_to_s[v] == v) return v;
        return find(v_to_s[v]);
    }

    int size(int v) {
        return s_to_vs[find(v)].size();
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) {
            info.emplace(0, u, v);
            return false;
        }
        
        if(size(u) > size(v)) swap(u, v);
        pq.erase(make_pair(-size(u), u));
        pq.erase(make_pair(-size(v), v));

        info.emplace(size(u), u, v);
        v_to_s[u] = v;
        while(s_to_vs[u].size()) {
            int e = s_to_vs[u].back();
            s_to_vs[u].pop_back();
            s_to_vs[v].emplace_back(e);
        }
        pq.emplace(-size(v), v);
        return true;
    }
    
    const vector<int>& get_set(int v) {
        return s_to_vs[find(v)];
    }

    void rollback() {
        assert(info.size());
        int s, u, v; tie(s, u, v) = info.top(); info.pop();
        if(s == 0) return;

        pq.erase(make_pair(-size(v), v));
        v_to_s[u] = u;
        
        while(s--) {
            int e = s_to_vs[v].back();
            s_to_vs[v].pop_back();
            s_to_vs[u].emplace_back(e);
        }
        pq.emplace(-size(u), u);
        pq.emplace(-size(v), v);
    }
};

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(MAX_N, MAX_N);
    int Q = gen.uniform<int>(MAX_Q, MAX_Q);
    printf("%d %d\n", N, Q);

    QuickFind qf(N);
    vector<int> trans(Q+1), deg(Q+1), U(Q+1), V(Q+1), K(Q+1), T(Q+1);
    vector< vector<int> > nxt(Q+1);
    int id = 1;
    auto dfs = [&](auto &&self, int cur) -> void {
        if(id > Q) return;
        int t;
        do {
            t = gen.uniform<int>(0, 1);
            if(t == 0) {
                int k = id++;
                nxt[cur].emplace_back(k);
                K[k] = cur; T[k] = 0;
                int u = gen.uniform<int>(0, N-1);
                int v = gen.uniform<int>(0, N-1);
                qf.unite(u, v);
                U[k] = u, V[k] = v;
                self(self, k);
                qf.rollback();
            }
            if(t == 1) {
                int k = id++;
                nxt[cur].emplace_back(k);
                K[k] = cur; T[k] = 1;
                int u;
                {
                    int M = min<int>(50, qf.pq.size());
                    M = gen.uniform<int>(0, M-1);
                    auto ptr = qf.pq.begin();
                    while(M--) ptr = next(ptr);
                    u = ptr->second;
                }

                int v;
                const vector<int>& vtx_set = qf.get_set(u);
                if(gen.uniform<int>(0, 1)) {
                    int M = vtx_set.size();
                    do {
                        v = vtx_set[gen.uniform<int>(0, M-1)];
                        if(M == 1 or u != v) break;
                    }while(true);
                }
                else {
                    v = gen.uniform<int>(0, N-1);
                }
                U[k] = u, V[k] = v;
            }
        }while(id <= Q);
    };
    dfs(dfs, 0);

    for(int i=1; i<=Q; i++) {
        printf("%d %d %d %d\n", T[i], K[i] - 1, U[i], V[i]);
    }
    return 0;
}
