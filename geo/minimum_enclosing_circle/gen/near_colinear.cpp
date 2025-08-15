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

    int LIM = X_AND_Y_ABS_MAX;
    int dx = gen.uniform<int>(-23, 23);
    int dy = gen.uniform<int>(0, 23);
    bool is_colinear = (seed % 2 == 0);
    set<P> S;
    for (int t = 1;; t++) {
        int x = dx * t;
        int y = dy * t;
        if (abs(x) > LIM || abs(y) > LIM) break;
        if (is_colinear) {
            S.insert({x, y});
        }
        else {
            if (gen.uniform_bool()) {
                x += gen.uniform<int>(-1, 1);
                y += gen.uniform<int>(-1, 1);
                if (abs(x) <= LIM && abs(y) <= LIM) {
                    S.insert({x, y});
                }
            }
            else {
                S.insert({x, y});
            }
        }
    }
    for (int t = 0;; t--) {
        int x = dx * t;
        int y = dy * t;
        if (abs(x) > LIM || abs(y) > LIM) break;
        S.insert({x, y});
    }
    bool shuffle = gen.uniform_bool();
    out(S, shuffle);
    return 0;
}
