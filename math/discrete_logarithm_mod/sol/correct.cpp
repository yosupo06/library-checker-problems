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

const ll STEP = 32000;

ll discrete_logarithm(ll x, ll y, ll m) {
    if (m == 1) return 0;
    if (y == 1) return 0;
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
    ll z = 1;
    for (ll step = 0; step < m + 10; step += STEP) {
        z = mul(z, big);
        // check [step + 1, step + STEP]
        if (mp.count(z)) {
            return (step + STEP) - mp[z];
        }
        z = mul(z, big);        
    }
    return -1;
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
