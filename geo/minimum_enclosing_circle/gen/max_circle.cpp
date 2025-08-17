#include <cmath>
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

void out(set<P> S) {
    int n = S.size();
    printf("%d\n", n);
    vector<P> V(S.begin(), S.end());
    for (auto& [x, y]: V) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    set<P> S;

    int n = N_MAX;
    int r = X_AND_Y_ABS_MAX;
    int x = 0, y = r;
    S.insert({x, y});
    S.insert({x, -y});
    while (x < r) {
        x++;
        while (y > 0 && x*x + y*y > r*r) y--;
        S.insert({x, y});
        S.insert({-x, y});
        S.insert({x, -y});
        S.insert({-x, -y});
    }

    int LIM = X_AND_Y_ABS_MAX;
    while (int(S.size()) < n) {
        P p = random_point(gen, LIM);
        if (p.first * p.first + p.second * p.second <= r * r) {
            S.insert(p);
        }
    }

    out(S);
    return 0;
}
