#include "random.h"
#include "../params.h"
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    vector<pair<ll, ll>> line;
    ll grad = n / 2;
    const ll step = 2 * A_ABS_MAX / n - 1;
    ll x = -A_ABS_MAX;
    ll y = 0;
    for (int i = 0; i < n; i++) {
        ll a = grad--;
        ll b = y - grad * x;
        y += step * a;
        x += step;
        line.push_back(make_pair(a, b));
    }
    gen.shuffle(line.begin(), line.end());
    for (auto p : line) {
        printf ("%lld %lld\n", p.first, p.second);
    }
    vector<int> ask;
    int p = -A_ABS_MAX + 1;
    for (int i = 0; i < q; i++) {
        ask.push_back(p);
        p += step;
    }
    gen.shuffle(ask.begin(), ask.end());
    for (auto p : ask) {
        printf("1 %d\n", p);
    }
    return 0;
}
