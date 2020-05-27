#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using namespace std;
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
    int n;
    scanf("%d", &n);
 
    auto g = VV<int>(n);
 
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> ans(n);
    auto dfs = [&](auto self, int p, int b, int dep = 0) -> void {
        ans[dep]++;
        for (int d: g[p]) {
            if (d == b) continue;
            self(self, d, p, dep + 1);
        }
    };
    for (int i = 0; i < n; i++) {
        dfs(dfs, i, -1);
    }

    for (int i = 1; i <= n - 1; i++) {
        if (i != 1) printf(" ");
        printf("%d", ans[i] / 2);
    }
    printf("\n");
    return 0;
}
