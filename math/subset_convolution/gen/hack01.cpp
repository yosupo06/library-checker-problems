#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;
using uint = unsigned int;

template <class T> using V = vector<T>;

int popcnt(uint x) { return __builtin_popcount(x); }

using A = array<uint, N_MAX + 1>;
int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const int n = N_MAX;

    vector<int> binom(n + 1);
    binom[0] = 1;
    binom[n] = 1;
    for (int i = 1; i <= n - 1; ++i) {
        binom[i] = binom[i - 1] * (n - i) / i;
    }

    printf("%d\n", n);

    for (uint k = 0; k < (1U << n); k++) {
        int cnt = popcnt(k);
        int q = (MOD - 1) / binom[cnt];
        int a = gen.uniform<int>(q / 100 * 99, q);
        printf("%d", a);
        if (k != (1U << n) - 1) printf(" ");
    }
    printf("\n");

    for (uint k = 0; k < (1U << n); k++) {
        int cnt = popcnt(k);
        int q = (MOD - 1) / binom[cnt];
        int a = gen.uniform<int>(q / 100 * 99, q);
        printf("%d", a);
        if (k != (1U << n) - 1) printf(" ");
    }
    printf("\n");
    return 0;
}

