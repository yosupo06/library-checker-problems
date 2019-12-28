#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {

    int n, q;
    scanf("%d %d", &n, &q);

    assert(ll(n) * q <= TEN(7));

    V<ll> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    auto g = VV<int>(n);
    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        g[p].push_back(i);
    }

    for (int i = 0; i < q; i++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int u; ll x;
            scanf("%d %lld", &u, &x);
            a[u] += x;
        } else {
            int u;
            scanf("%d", &u);
            auto dfs = [&](auto dfs, int v) -> ll {
                ll sum = a[v];
                for (auto w: g[v]) {
                    sum += dfs(dfs, w);
                }
                return sum;
            };
            printf("%lld\n", dfs(dfs, u));
        }
    }
    return 0;
}
