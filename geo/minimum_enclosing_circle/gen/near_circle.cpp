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

const long double PI = acosl(-1.0L);

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int lims[] = {X_AND_Y_ABS_MAX, 40};

    int LIM = lims[seed % 2];

    set<P> S;
    
    int n = gen.uniform<int>(100, N_MAX);
    int r = gen.uniform<int>(LIM/2, LIM*3/4);
    long double phi = gen.uniform<double>(0, 2 * PI);
    for (int i = 0; i < n; i++) {
        long double theta = (long double)(i) * 2 * PI / (long double)(n) + phi;
        long double ldx = r * cos(theta);
        long double ldy = r * sin(theta);
        int x = (int)(ldx);
        int y = (int)(ldy);
        while (y > 0 && x*x + (y+1)*(y+1) <= r*r) y++;
        while (y < 0 && x*x + (y-1)*(y-1) <= r*r) y--;
        y += gen.uniform<int>(-1, 1);
        if (abs(x) > X_AND_Y_ABS_MAX) x = (x < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
        if (abs(y) > X_AND_Y_ABS_MAX) y = (y < 0 ? -X_AND_Y_ABS_MAX : X_AND_Y_ABS_MAX);
        S.insert({(int)x, (int)y});
    }
    
    bool shuffle = gen.uniform_bool();
    out(S, shuffle);
    return 0;
}
