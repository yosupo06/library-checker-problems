#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
using namespace std;

// template
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
const int inf = 0x3fffffff;
const ll INF = 0x1fffffffffffffff;
// end

vector<int> mobius(int n)
{
    vector<int> prime(n + 1, 1), mobius(n + 1, 1);
    rep(i, 2, n + 1) if (prime[i])
    {
        mobius[i] = -1;
        for (int j = i * 2; j <= n; j += i)
        {
            prime[j] = 0;
            mobius[j] *= -1;
        }
        for (ll j = ll(i) * i; j <= n; j += i * i)
        {
            mobius[j] = 0;
        }
    }
    return mobius;
}

int sq(ll n)
{
    ll x = int(sqrt(n));
    while (x * x < n)
        x++;
    while (x * x > n)
        x--;
    return x;
}

ll calc(ll n)
{
    if (n <= 33)
    {
        int sq = round(sqrt(n));
        auto table = mobius(sq);
        ll s = 0;
        rep(i, 1, sq + 1) s += table[i] * (n / i / i);
        return s;
    }
    ll I = max<ll>(1, pow(n, .2));
    int D = (sq(n / I));
    auto table = mobius(D);

    ll s1 = 0;
    rep(i, 1, D + 1)
    {
        s1 += table[i] * (n / i / i);
    }
    vector<ll> ms = {0};
    ll M = 0;
    rep(i, 1, SZ(table))
    {
        M += table[i];
        ms.push_back(M);
    }
    vector<ll> mxis;
    ll Mxis = 0;
    for (int i = I - 1; i >= 1; i--)
    {
        ll Mxi = 1;
        ll xi = int(sq(n / i));
        ll sqd = int(sq(xi));
        rep(j, 1, xi / (sqd + 1) + 1)
        {
            Mxi -= (xi / j - xi / (j + 1)) * ms[j];
        }
        rep(j, 2, sqd + 1)
        {
            if (xi / j <= D)
                Mxi -= ms[xi / j];
            else
                Mxi -= mxis[I - j * j * i - 1];
        }
        mxis.push_back(Mxi);
        Mxis += Mxi;
    }
    ll s2 = Mxis - (I - 1) * ms.back();
    return s1 + s2;
}

int main()
{
    ll n;
    scanf("%lld", &n);
    printf("%lld\n", calc(n));
    return 0;
}
