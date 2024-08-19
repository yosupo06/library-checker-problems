#include <iostream>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MAX - 200, N_MAX);
    int k = gen.uniform(M_MAX - 100, M_MAX);
    vector<int> a(k);
    vector<int> b(k);
    vector<int> c(k);
    set<pair<int, int>> st;
    for (int i = 0; i < k; i++) {
        do {
            a[i] = gen.uniform(0, n - 1);
            b[i] = gen.uniform(0, n - 1);
        } while (st.count({a[i], b[i]}));
        st.insert({a[i], b[i]});
        c[i] = gen.uniform<int>(1, MOD - 1);
    }

    printf("%d %d\n", n, k);
    for (int i = 0; i < k; i++) {
        printf("%d %d %d\n", a[i], b[i], c[i]);
    }
    return 0;
}
