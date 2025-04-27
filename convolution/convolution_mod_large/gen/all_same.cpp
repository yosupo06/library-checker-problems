#include <cstdio>

#include "../fastio.h"
#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_M_MAX;
    int m = N_AND_M_MAX;

    int val1 = seed == 0 ? 1 : gen.uniform(0ll, MOD - 1);
    int val2 = seed == 0 ? 1 : gen.uniform(0ll, MOD - 1);

    vector<int> a(n, val1), b(m, val2);

    wtn(n, ' ', m);
    wtv(a);
    wtv(b);

    return 0;
}
