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

struct RangeLinearAddRangeMin
{
    RangeLinearAddRangeMin() {}
    template <typename T>
    RangeLinearAddRangeMin(vector<T> &a)
    {
        n = 1, height = 0;
        while (n < SZ(a))
            n <<= 1, height++;
        base.resize(n * 2);
        lazy.resize(n * 2);
        bridges.resize(n * 2);
        rep(i, n, n * 2) base[i] = P(i - n, 1000000000000LL);
        rep(i, 0, SZ(a)) base[i + n] = P(i, a[i]);
        rep(i, 0, n * 2) lazy[i] = Linear{0, 0};
        rep(i, n, n * 2) bridges[i] = {base[i], base[i]};
        for (int i = n - 1; i >= 1; i--)
            find(i);
    }
    void update(int L, int R, ll a, ll b)
    {
        int lb = L + n, rb = R + n;
        while (lb < rb)
        {
            if (lb & 1)
            {
                lazy[lb] = merge(lazy[lb], Linear{a, b});
                lb++;
            }
            lb >>= 1;
            if (rb & 1)
            {
                rb--;
                lazy[rb] = merge(lazy[rb], Linear{a, b});
            }
            rb >>= 1;
        }
        lb = L + n, rb = R + n;
        for (int i = 1; i <= height; i++)
        {
            if (((lb >> i) << i) != lb)
                find(lb >> i);
            if (((rb >> i) << i) != rb)
                find((rb - 1) >> i);
        }
    }
    ll query(int L, int R)
    {
        int lb = L + n, rb = R + n;
        ll ret = INF;
        while (lb < rb)
        {
            if (lb & 1)
            {
                chmin(ret, subtree(lb));
                lb++;
            }
            lb >>= 1;
            if (rb & 1)
            {
                rb--;
                chmin(ret, subtree(rb));
            }
            rb >>= 1;
        }
        return ret;
    }

private:
    struct P
    {
        ll x, y;
        P(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
        P operator+(const P &p) const
        {
            return P(x + p.x, y + p.y);
        }
        P operator-(const P &p) const
        {
            return P(x - p.x, y - p.y);
        }
        bool operator<(const P &p) const
        {
            return (y != p.y ? y < p.y : x < p.x);
        }
        bool operator==(const P &p) const
        {
            return (x == p.x and y == p.y);
        }
        bool operator!=(const P &p) const
        {
            return (x != p.x or y != p.y);
        }
    };
    i128 cross(const P &a, const P &b)
    {
        return i128(a.x) * b.y - i128(a.y) * b.x;
    }

    int n, height;
    using Linear = pair<ll, ll>;
    using B = pair<P, P>;
    vector<P> base;
    vector<Linear> lazy;
    vector<B> bridges;

    void find(int i)
    {
        if (i >= n)
            return;
        Linear offset = {0, 0};
        for (int x = i; x; x >>= 1)
            offset = merge(offset, lazy[x]);

        int lb = i * 2, rb = i * 2 + 1;
        int border = rb;
        while (border < n)
            border <<= 1;
        border -= n;
        Linear Ladd = lazy[lb], Radd = lazy[rb];
        for (;;)
        {
            // cerr<<i<<' '<<lb<<' '<<rb<<'\n';
            if (lb >= n and rb >= n)
                break;
            P a = bridges[lb].first, b = bridges[lb].second;
            P c = bridges[rb].first, d = bridges[rb].second;
            a = apply(a, offset);
            b = apply(b, offset);
            c = apply(c, offset);
            d = apply(d, offset);
            a = apply(a, Ladd);
            b = apply(b, Ladd);
            c = apply(c, Radd);
            d = apply(d, Radd);

            if (a != b and cross(b - a, c - a) < 0)
            {
                lb = lb * 2;
                Ladd = merge(Ladd, lazy[lb]);
            }
            else if (c != d and cross(c - b, d - b) < 0)
            {
                rb = rb * 2 + 1;
                Radd = merge(Radd, lazy[rb]);
            }
            else if (a == b)
            {
                rb = rb * 2;
                Radd = merge(Radd, lazy[rb]);
            }
            else if (c == d)
            {
                lb = lb * 2 + 1;
                Ladd = merge(Ladd, lazy[lb]);
            }
            else
            {
                i128 c1 = cross(b - a, d - c);
                i128 c2 = cross(b - a, b - c);
                bool side;
                if (c1 == 0 and c2 == 0)
                    side = (c.x < border);
                else
                    side = (c.x * c1 + (d.x - c.x) * c2 < c1 * border);

                if (side)
                {
                    lb = lb * 2 + 1;
                    Ladd = merge(Ladd, lazy[lb]);
                }
                else
                {
                    rb = rb * 2;
                    Radd = merge(Radd, lazy[rb]);
                }
            }
        }
        bridges[i] = {apply(base[lb], Ladd), apply(base[rb], Radd)};
    }
    ll subtree(int i)
    {
        Linear add = {0, 0};
        for (int x = i; x; x >>= 1)
            add = merge(add, lazy[x]);
        while (i < n)
        {
            if (apply(bridges[i].first, add).y < apply(bridges[i].second, add).y)
                i = i * 2;
            else
                i = i * 2 + 1;
            add = merge(add, lazy[i]);
        }
        P ret = apply(base[i], add);
        return ret.y;
    }
    Linear merge(Linear a, Linear b)
    {
        a.first += b.first;
        a.second += b.second;
        return a;
    }
    P apply(P a, Linear b)
    {
        a.y += a.x * b.first + b.second;
        return a;
    }
};

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    rep(i, 0, n) scanf("%d", &a[i]);

    RangeLinearAddRangeMin seg(a);
    while (q--)
    {
        int t;
        scanf("%d", &t);
        if (t == 0)
        {
            int l, r, b, c;
            scanf("%d%d%d%d", &l, &r, &b, &c);
            seg.update(l, r, b, c);
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            ll ret = seg.query(l, r);
            printf("%lld\n", ret);
        }
    }
}