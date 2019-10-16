#include "random.h"
#include <iostream>
#include <tuple>

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 200'000;
    int q = 200'000;
    cout << n << " " << q << "\n";
    vector<int> xs(1000), ys(1000);
    for (int i = 0; i < 1000; i++) {
        xs[i] = gen.uniform(0, 1'000'000'000);
        ys[i] = gen.uniform(0, 1'000'000'000);
    }
    for (int i = 0; i < n; i++) {
        int x, y;
        if (gen.uniform_bool()) {
            x = gen.uniform(0, 1'000'000'000);
            y = gen.uniform(0, 1'000'000'000);
        } else {
            x = xs[gen.uniform(0, 999)];
            y = ys[gen.uniform(0, 999)];
        }
        int w = gen.uniform(0, 1'000'000'000);
        cout << x << " " << y << " " << w << "\n";
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        if (gen.uniform_bool()) {
            tie(l, r) = gen.uniform_pair(0, 1'000'000'000);
            tie(d, u) = gen.uniform_pair(0, 1'000'000'000);
        } else {
            do {
                l = xs[gen.uniform(0, 999)];
                d = ys[gen.uniform(0, 999)];
                r = xs[gen.uniform(0, 999)];
                u = ys[gen.uniform(0, 999)];
            } while (r <= l || u <= d);
        }
        cout << l << " " << d << " " << r << " " << u << "\n";
    }
    return 0;
}
