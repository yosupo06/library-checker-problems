#include <cassert>
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
    scanf("%d %d", &n, &q);
    assert(ll(n) * q <= TEN(8));
    using L = pair<ll, ll>;
    V<L> lines;
    for (int i = 0; i < n; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        lines.push_back({a, b});
    }
    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            // add
            ll a, b;
            scanf("%lld %lld", &a, &b);
            lines.push_back({a, b});
        } else {
            ll x;
            scanf("%lld", &x);
            ll ans = 3 * TEN(18);
            for (auto l : lines) {
                ans = min(ans, l.first * x + l.second);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
