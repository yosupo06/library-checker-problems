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

const long double PI = acosl(-1.0L);

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    set<P> S;

    int n = N_MAX;
    int r = X_AND_Y_ABS_MAX;
    for (int i = 0; i < n; i++) {
        long double theta = (long double)(i) * 2 * PI / (long double)(n);
        long double ldx = r * cos(theta);
        long double ldy = r * sin(theta);
        int x = (int)(ldx);
        int y = (int)(ldy);
        while (y > 0 && x*x + (y+1)*(y+1) <= r*r) y++;
        while (y < 0 && x*x + (y-1)*(y-1) <= r*r) y--;
        if (abs(x) > X_AND_Y_ABS_MAX) x = (x < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
        if (abs(y) > X_AND_Y_ABS_MAX) y = (y < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
        S.insert({x, y});
    }

    int LIM = X_AND_Y_ABS_MAX*7/10;
    while (int(S.size()) < n) {
        P p = random_point(gen, LIM);
        S.insert(p);
    }

    out(S);
    return 0;
}
