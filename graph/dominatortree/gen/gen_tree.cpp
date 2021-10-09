#include <cassert>
#include <iostream>
#include <vector>

#include "random.h"

using namespace std;

vector<pair<int, int>> generate_random_tree(int n, Random& rng) {
    assert(n >= 3);
    vector<int> code(n - 2);
    for (int i = 0; i < n - 2; ++i) code[i] = rng.uniform(0, n - 1);
    vector<int> degree(n, 1);
    for (int i : code) degree[i]++;
    int ptr = 0;
    while (degree[ptr] != 1) ptr++;
    int leaf = ptr;
    vector<pair<int, int>> edges;
    for (int v : code) {
        edges.emplace_back(min(leaf, v), max(leaf, v));
        if (--degree[v] == 1 && v < ptr)
            leaf = v;
        else {
            ptr++;
            while (degree[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n - 1);
    return edges;
}

int main(int argc, char* argv[]) {
    assert(argc == 2);
    constexpr int n = 1e5;
    auto rng = Random(atoll(argv[1]));
    auto edges = generate_random_tree(n, rng);
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> p(n, -1);
    vector<vector<int>> depth(n);
    p[0] = 0;
    auto dfs = [&](auto&& self, int u, int d) -> void {
        depth[d].push_back(u);
        for (auto v : g[u]) {
            if (p[v] == -1) {
                p[v] = u;
                self(self, v, d + 1);
            }
        }
    };
    dfs(dfs, 0, 0);
    vector<pair<int, int>> extra;
    for (int i = 0; i + 1 < n; ++i) {
        if (depth[i + 1].size() == 0) break;
        for (auto v : depth[i]) {
            int u = depth[i + 1][rng.uniform(0, (int)depth[i + 1].size() - 1)];
            if (p[u] != v) extra.emplace_back(v, u);
        }
    }
    assert(extra.size() + n - 1 <= 200'000);
    cout << n << ' ' << n - 1 + extra.size() << ' ' << 0 << '\n';
    for (int i = 1; i < n; ++i) cout << p[i] << ' ' << i << '\n';
    for (auto [u, v] : extra) cout << u << ' ' << v << '\n';
}

