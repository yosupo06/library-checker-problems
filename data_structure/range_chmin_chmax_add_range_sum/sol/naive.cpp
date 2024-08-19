#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    assert(ll(n) * q <= TEN(8));

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        assert (llabs(a[i]) <= TEN(12));
    }

    for (int ph = 0; ph < q; ph++) {
        int ty, l, r;
        scanf("%d%d%d", &ty, &l, &r);
        if (ty == 0) {
            ll b;
            scanf("%lld", &b);
            assert (llabs(b) <= TEN(12));
            for (int i = l; i < r; i++) {
                a[i] = min(a[i], b);
            }
        } else if (ty == 1) {
            ll b;
            scanf("%lld", &b);
            assert (llabs(b) <= TEN(12));
            for (int i = l; i < r; i++) {
                a[i] = max(a[i], b);
            }
        } else if (ty == 2) {
            ll b;
            scanf("%lld", &b);
            for (int i = l; i < r; i++) {
                a[i] += b;
                assert (llabs(a[i]) <= TEN(12));
            }
        } else {
            ll sum = 0;
            for (int i = l; i < r; i++) {
                sum += a[i];
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}
