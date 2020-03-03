#include "random.h"
#include "../params.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    int x = gen.uniform(-A_ABS_MAX, A_ABS_MAX - 1);
    vector<pair<int, ll>> line(n);
    for (int i = 0; i < n; i++) {
        int d = gen.uniform(-(A_ABS_MAX / 2), A_ABS_MAX / 2);
        int a = 2 * d;
        ll b = (ll)d * (2 * x + 1);
        line[i] = make_pair(a, b);
    }
    sort(line.begin(), line.end());
    for (auto p : line) {
        printf("%d %lld\n", p.first, p.second);
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        printf("1 %d\n", x + t);
    }
    return 0;
}
