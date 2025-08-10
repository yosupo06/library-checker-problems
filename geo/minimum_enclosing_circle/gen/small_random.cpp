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

void out(set<P> S, bool shuffle) {
    int n = S.size();
    printf("%d\n", n);
    vector<P> V(S.begin(), S.end());
    if (shuffle) {
        std::random_shuffle(V.begin(), V.end());
    }
    for (auto& [x, y]: V) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int lims[] = {X_AND_Y_ABS_MAX, 2, 5, 10};

    int LIM = lims[seed % 4];

    set<P> S;

    int n = gen.uniform<int>(2, 20);
    while((int(S.size()) < n)) {
        P p = random_point(gen, LIM);
        S.insert(p);
    }
    bool shuffle = gen.uniform_bool();
    out(S, shuffle);
    return 0;
}
