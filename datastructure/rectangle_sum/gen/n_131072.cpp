#include "random.h"
#include <iostream>
#include <tuple>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 131072;
    int q = 200000;
    cout << n << " " << q << "\n";
    vector<int> ys = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        int x = 2 * i;
        int y = 2 * ys[i];
        int w = gen.uniform(0, 1'000'000'000);
        cout << x << " " << y << " " << w << "\n";
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        tie(l, r) = gen.uniform_pair(0, 2 * n);
        tie(d, u) = gen.uniform_pair(0, 2 * n);
        if (gen.uniform_bool()) {
            l = 0;
        }
        if (gen.uniform_bool()) {
            d = 0;
        }
        if (gen.uniform_bool()) {
            r = 2 * n;
        }
        if (gen.uniform_bool()) {
            u = 2 * n;
        }
        if (gen.uniform_bool()) {
            r = l + 1;
        }
        if (gen.uniform_bool()) {
            u = d + 1;
        }
        cout << l << " " << d << " " << r << " " << u << "\n";
    }
    return 0;
}
