#include <iostream>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int n;
VV<ll> a;

pair<ll, V<bool>> solve(VV<ll> a, V<int> vs) {
    ll ans = TEN(18);
    V<bool> res(n);
    if (vs.size() == 2) {
        res[vs[1]] = true;
        return {a[vs[0]][vs[1]], res};
    }    
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    a = VV<ll>(n, V<ll>(n));
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        scanf("%d %d %lld", &u, &v, &w);
        a[u][v] += w;
        a[v][u] += w;
    }

    printf("%lld\n", -sm);
    for (int i = 0; i < n; i++) {
        printf("%d", hungarian.perm[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
