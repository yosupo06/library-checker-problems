#include <cstdio>
#include <vector>
#include <utility>
#include <tuple>
#include <stack>
#include <functional>
#include <algorithm>
#include <cassert>
using Graph = std::vector< std::vector< std::pair<int, int> > >;

int main() {
    int N, M; scanf("%d%d", &N, &M);
    Graph G(N);
    std::vector<int> U(M), V(M);
    for(int i=0; i<M; i++) {
        scanf("%d%d", &U[i], &V[i]);
        G[ U[i] ].emplace_back(V[i], i);
    }

    std::vector<bool> visited(N), finished(N);
    std::stack<int> st;
    int base_point = -1;
    auto dfs = [&](auto &&self, int cur) -> bool {
        visited[cur] = true;
        for(auto edge : G[cur]) {
            int to, id; std::tie(to, id) = edge;
            st.emplace(id);
            if(visited[to] and !finished[to]) {
                base_point = to;
                return true;
            }
            if(!visited[to] and self(self, to)) return true;
            st.pop();
        }
        finished[cur] = true;
        return false;
    };
    for(int i=0; i<N; i++) {
        if(visited[i]) continue;        
        if(dfs(dfs, i)) {
            int v = base_point;
            std::vector<int> ans;
            while(st.size()) {
                int edge = st.top(); st.pop();
                assert(V[edge] == v);
                ans.emplace_back(edge);
                v = U[edge];
                if(v == base_point) break;
            }
            std::reverse(ans.begin(), ans.end());
            printf("%zu\n", ans.size());
            for(size_t i=0; i<ans.size(); i++) {
                printf("%d\n", ans[i]);
            }
            return 0;
        }
    }
    puts("-1");
    return 0;
}
