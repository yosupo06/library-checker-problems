#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

void out(vector<P> S) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int x0 = gen.uniform<int>(1, 10);
    int y0 = gen.uniform<int>(1, 10);
    int lim = X_AND_Y_ABS_MAX / max(x0, y0);

    int n = N_MAX;
    vector<P> S;
    for (int i = 0; i < n; ++i) {
        int t = gen.uniform<int>(-lim, lim);
        int x = x0 * t, y = y0 * t;
        S.emplace_back(x, y);
    }

    out(S);
    return 0;
}
