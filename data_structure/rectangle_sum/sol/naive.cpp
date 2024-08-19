#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

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
    assert(ll(n) * q <= TEN(8));
    V<int> x(n), y(n);
    V<ll> w(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %lld", &x[i], &y[i], &w[i]);
    }
    for (int ph = 0; ph < q; ph++) {
        int l, d, r, u;
        scanf("%d %d %d %d", &l, &d, &r, &u);

        ll sm = 0;
        for (int i = 0; i < n; i++) {
            if (l <= x[i] && x[i] < r && d <= y[i] && y[i] < u) {
                sm += w[i];
            }
        }
        printf("%lld\n", sm);
    }
    return 0;
}
