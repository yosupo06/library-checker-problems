#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;

struct P { int x, y; };

void out(const std::vector<P>& pts) {
    printf("%d\n", (int)pts.size());
    for (const auto& p : pts) {
        printf("%d %d\n", p.x, p.y);
    }
}

int main() {
    int N = N_MAX;

    const int LIM = X_AND_Y_ABS_MAX;
    const int A = (LIM >= 10) ? (LIM - 5) : LIM;

    int YAMP = (LIM >= 200) ? 100 : (LIM / 2);
    if (YAMP < 1) YAMP = 1;

    const int PER_COL = 2 * YAMP + 1;
    const int PER_PAIR = 2 * PER_COL;
    int pairs = (N + PER_PAIR - 1) / PER_PAIR;

    assert(pairs <= A);

    vector<P> pts;
    pts.reserve(static_cast<size_t>(N));

    int produced = 0;
    for (int t = 0; t < pairs && produced < N; ++t) {
        const int xL = -(A - t);
        const int xR = +(A - t);

        for (int k = -YAMP; k <= YAMP && produced < N; ++k) {
            pts.push_back(P{xL, k});
            ++produced;
            if (produced >= N) break;
            pts.push_back(P{xR, k});
            ++produced;
        }
    }

    assert((int)pts.size() == N);
    for (const auto& p : pts) {
        assert(p.x >= -LIM && p.x <= LIM);
        assert(p.y >= -LIM && p.y <= LIM);
    }

    out(pts);
    return 0;
}
