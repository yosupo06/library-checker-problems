#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdint>
using namespace std;

#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define ALL(v) (v).begin(), (v).end()
#define UNIQUE(v) sort(ALL(v)), (v).erase(unique(ALL(v)), (v).end())
#define SZ(v) (int)v.size()
#define MIN(v) *min_element(ALL(v))
#define MAX(v) *max_element(ALL(v))
#define LB(v, x) int(lower_bound(ALL(v), (x)) - (v).begin())
#define UB(v, x) int(upper_bound(ALL(v), (x)) - (v).begin())

using ll = long long int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
const ll INF = 0x1fffffffffffffff;

template <typename T>
inline bool chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T>
inline bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T, typename U>
T ceil(T x, U y)
{
    assert(y != 0);
    if (y < 0)
        x = -x, y = -y;
    return (x > 0 ? (x + y - 1) / y : x / y);
}
template <typename T, typename U>
T floor(T x, U y)
{
    assert(y != 0);
    if (y < 0)
        x = -x, y = -y;
    return (x > 0 ? x / y : (x - y + 1) / y);
}
template <typename T>
int popcnt(T x) { return __builtin_popcountll(x); }
template <typename T>
int topbit(T x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
template <typename T>
int lowbit(T x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    vector<ll> a(n);
    rep(i, 0, n) scanf("%lld", &a[i]);

    while (q--)
    {
        int t;
        scanf("%d", &t);
        if (t == 0)
        {
            int l, r, b, c;
            scanf("%d%d%d%d", &l, &r, &b, &c);
            rep(i, l, r) a[i] += ll(b) * i + c;
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            ll ret = INF;
            rep(i, l, r) chmin(ret, a[i]);
            printf("%lld\n", ret);
        }
    }
}