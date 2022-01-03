#include<iostream>
#include<tuple>
#include<vector>

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
        v.emplace_back(t->l, t->r, (t->is_join ? "join" : "cut"));
        for (auto e : t->ch) {
            dfs(dfs, e);
        }
    };
    dfs(dfs, root);
    cout << v.size() << endl;
    for (auto [l, r, s] : v) {
        cout << l << " " << r << " " << s << endl;
    }
}