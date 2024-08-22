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

    // make them almost decreasing
    sort(a.rbegin(), a.rend());
    for (int k = 0; k < 100; k++) {
        int i = gen.uniform(0, n - 1);
        int j = (i + gen.uniform(0, 30)) % n;
        swap(a[i], a[j]);
    }

    // print params
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d%c", a[i], i + 1 < n ? ' ' : '\n');
    }

    return 0;
}
