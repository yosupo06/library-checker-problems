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

static inline uint64_t xs64(uint64_t& st) { st ^= st << 7; st ^= st >> 9; return st; }
template <class T>
static void deterministic_shuffle(std::vector<T>& a, uint64_t seed = 0x9E3779B97F4A7C15ULL) {
    if (a.size() <= 1) return;
    uint64_t s = seed;
    for (int i = (int)a.size() - 1; i >= 1; --i) {
        uint64_t r = xs64(s);
        int j = (int)(r % (uint64_t)(i + 1));
        if (i != j) { T tmp = a[i]; a[i] = a[j]; a[j] = tmp; }
    }
}


void out(set<P> S, bool shuffle) {
    int n = S.size();
    printf("%d\n", n);
    vector<P> V(S.begin(), S.end());
    if (shuffle) {
        deterministic_shuffle(V, 0x9E3779B97F4A7C15ULL);
    }
    for (auto& [x, y]: V) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int lims[] = {X_AND_Y_ABS_MAX, 40};

    int LIM = lims[seed % 2];

    set<P> S;

    int rx = gen.uniform<int>(LIM*5/9, LIM*2/3);
    int ry = gen.uniform<int>(LIM*5/9, LIM*2/3);
    int r_sq = rx*rx + ry*ry;
    int r = (int)sqrt(r_sq);
    int cx = gen.uniform<int>(-X_AND_Y_ABS_MAX + r*11/10, X_AND_Y_ABS_MAX - r*11/10);
    int cy = gen.uniform<int>(-X_AND_Y_ABS_MAX + r*11/10, X_AND_Y_ABS_MAX - r*11/10);
    int x = 0, y = r;
    S.insert({x + cx, y + cy});
    S.insert({x + cx, -y + cy});
    const int dy[] = {-1, 0, 1};
    while (x < r) {
        x++;
        while (y > 0 && x*x + y*y > r_sq) y--;
        int px = x;
        int py = y;
        for (int d = 0; d < 3; d++) {
            int nx = px;
            int ny = py + dy[d];
            if (abs(nx) > X_AND_Y_ABS_MAX) nx = (nx < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
            if (abs(ny) > X_AND_Y_ABS_MAX) ny = (ny < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
            int insert_flag = gen.uniform(0, 15);
            if (insert_flag & 1) S.insert({nx + cx, ny + cy});
            if (insert_flag & 2) S.insert({-nx + cx, ny + cy});
            if (insert_flag & 4) S.insert({nx + cx, -ny + cy});
            if (insert_flag & 8) S.insert({-nx + cx, -ny + cy});
        }
    }
    while (int(S.size()) > N_MAX) {
        auto it = S.begin();
        S.erase(it);
    }
    bool shuffle = gen.uniform_bool();
    out(S, shuffle);
    return 0;
}
