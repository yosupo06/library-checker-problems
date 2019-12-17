#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

ll pow_mod(ll x, ll n, ll md) {
    ll r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

const ll STEP = 32000;

ll discrete_logarithm(ll start, ll x, ll y, ll m) {
    auto mul = [&](ll a, ll b) {
        return (a * b) % m;
    };
    unordered_map<ll, ll> mp;
    ll big = 1; // x^m
    for (ll i = 0; i < STEP; i++) {
        mp[y] = i;
        y = mul(y, x);
        big = mul(big, x);
    }
    for (ll step = 0; step < m + 10; step += STEP) {
        start = mul(start, big);
        // check [step + 1, step + STEP]
        if (mp.count(start)) {
            return (step + STEP) - mp[start];
        }
    }
    return -1;
}

ll discrete_logarithm(ll x, ll y, ll m) {
    if (m == 1) return 0;
    auto mul = [&](ll a, ll b) {
        return (a * b) % m;
    };
    ll start = 1;
    for (int i = 0; i < 100; i++) {
        if (start == y) return i;
        start = mul(start, x);
    }
    ll pred = 100 + discrete_logarithm(start, x, y, m);
    if (pow_mod(x, pred, m) != y) return -1;
    return pred;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        ll x, y, m;
        cin >> x >> y >> m;
        cout << discrete_logarithm(x, y, m) << "\n";
    }
    return 0;
}
