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

    int lims[] = { 10, 1000, X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX };

    int LIM = lims[seed % 4];

    int n = gen.uniform<int>(100, 1000);
    vector<P> S;
    for (int i = 0; i < n; ++i) S.emplace_back(random_point(gen, LIM));

    out(S);
    return 0;
}
