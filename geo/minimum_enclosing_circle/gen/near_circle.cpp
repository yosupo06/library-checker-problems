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

    int lims[] = {X_AND_Y_ABS_MAX, 40};

    int LIM = lims[seed % 2];

    set<P> S;

    int n = gen.uniform<int>(N_MAX*49/50, N_MAX);
    int r = gen.uniform<int>(LIM/2, LIM*3/4);
    long double phi = gen.uniform<double>(0, 2 * M_PI);
    for (int i = 0; i < n; i++) {
        long double x = r * cos(i * 2 * M_PI / n + phi) + gen.uniform<int>(0, 1);
        long double y = r * sin(i * 2 * M_PI / n + phi) + gen.uniform<int>(0, 1);
        S.insert({(int)x, (int)y});
    }
    
    bool shuffle = gen.uniform_bool();
    out(S, shuffle);
    return 0;
}
