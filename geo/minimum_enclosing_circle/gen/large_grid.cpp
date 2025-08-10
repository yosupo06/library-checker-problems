#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

void out(vector<P> S, bool shuffle) {
    int n = S.size();
    printf("%d\n", n);
    if (shuffle) {
        std::random_shuffle(S.begin(), S.end());
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
