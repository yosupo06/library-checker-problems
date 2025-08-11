#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

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


void out(vector<P> S, bool shuffle) {
    int n = S.size();
    printf("%d\n", n);
    if (shuffle) {
        deterministic_shuffle(S, 0x9E3779B97F4A7C15ULL);
    }
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(N_MAX*49/50, N_MAX);
    int h = gen.uniform<int>(100, min(X_AND_Y_ABS_MAX, static_cast<long long>(n)));
    int w = n / h;
    vector<P> pts;
    pts.reserve(static_cast<size_t>(n));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pts.push_back({i, j});
        }
    }
    bool shuffle = gen.uniform_bool();
    out(pts, shuffle);
    return 0;
}
