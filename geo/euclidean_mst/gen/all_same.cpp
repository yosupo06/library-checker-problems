#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

P random_point(Random& gen, int LIM) {
    int x = gen.uniform(-LIM, LIM);
    int y = gen.uniform(-LIM, LIM);
    return {x, y};
}

void out(vector<P> S) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    auto [x, y] = random_point(gen, X_AND_Y_ABS_MAX);
    vector<P> S(n, { x,y });

    out(S);
    return 0;
}
