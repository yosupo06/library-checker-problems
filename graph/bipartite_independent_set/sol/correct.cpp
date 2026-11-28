#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using std::vector;

// Hopcroft-Karp. The last BFS also gives the alternating paths from free left vertices.
vector<int> independent_set(const vector<vector<int>>& adj, int right_count) {
    int n = int(adj.size());
    const int infinity = n + 1;
    vector<int> left_match(n, -1), right_match(right_count, -1), level(n);
    vector<int> path;
    for (;;) {
        std::fill(level.begin(), level.end(), infinity);
        std::queue<int> queue;
        for (int u = 0; u < n; ++u) {
            if (left_match[u] == -1) {
                level[u] = 0;
                queue.push(u);
            }
        }
        int shortest = infinity;
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            if (level[u] >= shortest) continue;
            for (int v : adj[u]) {
                int next = right_match[v];
                if (next == -1) {
                    shortest = level[u] + 1;
                } else if (level[next] == infinity) {
                    level[next] = level[u] + 1;
                    queue.push(next);
                }
            }
        }
        if (shortest == infinity) break;

        // Find disjoint shortest augmenting paths without recursing on long paths.
        vector<int> cursor(n);
        for (int start = 0; start < n; ++start) {
            if (left_match[start] != -1) continue;
            path.clear();
            path.push_back(start);
            while (!path.empty()) {
                int u = path.back();
                if (cursor[u] == int(adj[u].size())) {
                    level[u] = infinity;
                    path.pop_back();
                    continue;
                }
                int v = adj[u][cursor[u]++];
                int next = right_match[v];
                if (next == -1 && level[u] + 1 == shortest) {
                    for (auto it = path.rbegin(); it != path.rend(); ++it) {
                        right_match[v] = *it;
                        std::swap(left_match[*it], v);
                        level[*it] = infinity;
                    }
                    break;
                }
                if (next != -1 && level[next] == level[u] + 1 && level[next] < shortest) {
                    path.push_back(next);
                }
            }
        }
    }

    // Take reachable left vertices and unreachable right vertices (Konig's theorem).
    vector<int> answer;
    for (int u = 0; u < n; ++u) {
        if (level[u] != infinity) answer.push_back(u);
    }
    for (int v = 0; v < right_count; ++v) {
        if (right_match[v] == -1 || level[right_match[v]] == infinity) answer.push_back(n + v);
    }
    return answer;
}

int main() {
    int l, r, m;
    std::scanf("%d%d%d", &l, &r, &m);
    vector<vector<int>> adj(l);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::scanf("%d%d", &a, &b);
        adj[a].push_back(b);
    }
    auto answer = independent_set(adj, r);
    std::printf("%d\n", int(answer.size()));
    for (int i = 0; i < int(answer.size()); ++i) {
        std::printf("%s%d", i == 0 ? "" : " ", answer[i]);
    }
    std::puts("");
    return 0;
}
