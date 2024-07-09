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

    vector<vector<P>> ALL;
    int n = 1;
    while ((n + 1) * (n + 1) <= N_MAX) ++n;

    int eps = 5;
    /*
    x[0],x[1],...,x[N-1]
    */
    int LIM = X_AND_Y_ABS_MAX;
    int d = LIM / (n - 1);

    auto get = [&](int i) -> int {
        int x = i * d - (LIM / 2);
        return x + gen.uniform<int>(-eps, eps);
    };

    vector<P> S;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        int x = get(i), y = get(j);
        S.emplace_back(x, y);
        }
    }

    gen.shuffle(S.begin(), S.end());

    out(S);
    return 0;
}
