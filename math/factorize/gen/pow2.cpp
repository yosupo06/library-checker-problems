#include <iostream>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = gen.uniform(1LL, MAX_Q);
    vector<long long> a(q);
    for (int i = 0; i < q; i++) {
        a[i] = gen.uniform(1, 1'000'000'000);
        a[i] = a[i] * a[i];
    }

    printf("%d\n", q);
    for (auto x : a) {
        printf("%lld\n", x);
    }
    return 0;
}
