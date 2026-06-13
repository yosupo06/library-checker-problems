#include <algorithm>
#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;

// Generates a random monic polynomial by first choosing a random prime p, then
// multiplying random monic factors of degree 1..4 with multiplicity 1..3 until
// the target degree is reached. The factors are not forced to be irreducible.
bool is_prime(ll n) {
    if (n <= 1) return false;
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }
    return true;
}

ll random_prime(Random& gen) {
    while (true) {
        ll p = gen.uniform<ll>(2, P_MAX);
        if (is_prime(p)) return p;
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b, ll p) {
    vector<ll> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            c[i + j] = (c[i + j] + a[i] * b[j]) % p;
        }
    }
    return c;
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll p = random_prime(gen);
    int target = gen.uniform<int>(1, N_MAX);
    vector<ll> f = {1};

    while ((int)f.size() - 1 < target) {
        int rem = target - ((int)f.size() - 1);
        int d = gen.uniform<int>(1, min(4, rem));
        vector<ll> g(d + 1);
        for (int i = 0; i < d; i++) g[i] = gen.uniform<ll>(0, p - 1);
        g[d] = 1;
        int e = gen.uniform<int>(1, min(3, rem / d));
        for (int i = 0; i < e; i++) f = multiply(f, g, p);
    }

    int n = (int)f.size() - 1;
    printf("%d %lld\n", n, p);
    for (int i = 0; i <= n; i++) {
        if (i) printf(" ");
        printf("%lld", f[i]);
    }
    printf("\n");
    return 0;
}
