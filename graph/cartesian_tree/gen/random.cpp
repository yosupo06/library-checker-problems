#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    // generate params randomly
    int n = seed == 0 ? N_MAX : gen.uniform(N_MIN, N_MAX);
    vector<int> a(n);
    set<int> used;
    for (int i = 0; i < n; i++) {
        do {
            a[i] = gen.uniform(A_MIN, A_MAX);
        } while (used.count(a[i]));
        used.insert(a[i]);
    }

    // print params
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d%c", a[i], i + 1 < n ? ' ' : '\n');
    }

    return 0;
}
