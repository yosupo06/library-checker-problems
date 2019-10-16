#include "random.h"
#include <iostream>
#include <tuple>

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 1'000);
    int q = gen.uniform(1, 1'000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        int x = gen.uniform(0, 1000);
        int y = gen.uniform(0, 1000);
        int w = gen.uniform(0, 1'000'000'000);
        cout << x << " " << y << " " << w << "\n";
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        tie(l, r) = gen.uniform_pair(0, 1000);
        tie(d, u) = gen.uniform_pair(0, 1000);
        cout << l << " " << d << " " << r << " " << u << "\n";
    }
    return 0;
}