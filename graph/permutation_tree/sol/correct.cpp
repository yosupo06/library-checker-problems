#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
#include "permutation_tree.hpp"

int main()
{
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    perm_tree<int> pt(p);
    auto root = pt.get();
    using np = decltype(root);
    vector<tuple<int, int, string>> v;
    auto dfs = [&](auto dfs, np t) -> void {
        v.emplace_back(t->l, t->r, (t->is_join ? "linear" : "prime"));
        for (auto e : t->ch) {
            dfs(dfs, e);
        }
    };
    dfs(dfs, root);
    printf("%zu\n", v.size());
    for (auto [l, r, s] : v) {
        printf("%d %d %s\n", l, r-1, s.c_str());
    }
}