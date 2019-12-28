#include <iostream>
#include <vector>
#include <tuple>

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
    int lg = 1;
    while ((1 << lg) < n) lg++;

    V<int> dps(n, 0);
    VV<int> anc(lg, V<int>(n, -1));
    for (int i = 1; i < n; i++) {
        scanf("%d", &anc[0][i]);
        dps[i] = dps[anc[0][i]] + 1;
    }
    for (int i = 1; i < lg; i++) {
        for (int j = 0; j < n; j++) {
            anc[i][j] =
                (anc[i - 1][j] == -1) ? -1 : anc[i - 1][anc[i - 1][j]];
        }
    }

    auto query = [&](int u, int v) {
        if (dps[u] < dps[v]) swap(u, v);
        int dist = dps[u] - dps[v];
        for (int i = lg - 1; i >= 0; i--) {
            if (dist < (1 << i)) continue;
            dist -= 1 << i;
            u = anc[i][u];
        }
        if (u == v) return u;
        for (int i = lg - 1; i >= 0; i--) {
            if (anc[i][u] == anc[i][v]) continue;
            tie(u, v) = tie(anc[i][u], anc[i][v]);
        }
        return anc[0][u];
    };

    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", query(u, v));
    }
    return 0;
}
