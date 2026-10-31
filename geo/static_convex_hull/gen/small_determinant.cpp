#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;
using P = pair<long long, long long>;

int main(int, char* argv[]) {
    Random gen(atoll(argv[1]));
    const long long lim = X_AND_Y_ABS_MAX;
    const int cases = 1000;
    printf("%d\n", cases);
    for (int t = 0; t < cases; ++t) {
        int type = t % 3;
        long long max_m = type == 0 ? lim : lim / 2;
        long long m = gen.uniform(2LL, t % 5 == 0 ? 100LL : max_m);
        P a = {m, m - 1}, b = {m - 1, m - 2};
        // cross(a, b) = -1, including when floating-point products cancel.
        vector<P> points = {{0, 0}, a, b};
        if (type == 1) {
            // Thin parallelogram: all four points are extreme.
            points.emplace_back(2 * m - 1, 2 * m - 3);
        } else {
            points.emplace_back(-m, m);
            if (type == 2) {
                // a is on an edge; b lies just outside that edge.
                points.emplace_back(2 * m, 2 * m - 2);
            }
        }
        bool flip_x = gen.uniform_bool(), flip_y = gen.uniform_bool();
        bool swap_xy = gen.uniform_bool();
        long long min_x = lim, max_x = -lim, min_y = lim, max_y = -lim;
        for (auto& [x, y] : points) {
            if (flip_x) x = -x;
            if (flip_y) y = -y;
            if (swap_xy) swap(x, y);
            min_x = min(min_x, x);
            max_x = max(max_x, x);
            min_y = min(min_y, y);
            max_y = max(max_y, y);
        }
        long long dx = gen.uniform(-lim - min_x, lim - max_x);
        long long dy = gen.uniform(-lim - min_y, lim - max_y);
        gen.shuffle(points.begin(), points.end());
        printf("%zu\n", points.size());
        for (auto [x, y] : points) printf("%lld %lld\n", x + dx, y + dy);
    }
}
