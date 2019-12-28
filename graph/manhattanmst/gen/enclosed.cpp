#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const int D = 1'000'000'000;
    const int S = 1'000'000;
    int n = gen.uniform(200000 - 1000, 200000);
    using P = pair<int, int>;
    vector<P> ps(n);
    ps[0].first = gen.uniform(D / 2 - S, D / 2 + S);
    ps[0].second = gen.uniform(D / 2 - S, D / 2 + S);
    ps[1].first = gen.uniform(D / 2 - S, D / 2 + S);
    ps[1].second = gen.uniform(D / 2 - S, D / 2 + S);
    for (int i = 2; i < n; i++) {
        int x = gen.uniform(0, D);
        int y = gen.uniform(0, D);
        if (gen.uniform_bool()) {
            if (gen.uniform_bool()) {
                x = 0;
            } else {
                x = D;
            }
        } else {
            if (gen.uniform_bool()) {
                y = 0;
            } else {
                y = D;
            }
        }
        ps[i] = P(x, y);
    }
    gen.shuffle(ps.begin(), ps.end());

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", ps[i].first, ps[i].second);
    }
    return 0;
}
