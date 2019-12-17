#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);
    int q = gen.uniform(1, 500'000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(0, 1'000'000'000);
        if (i != n - 1) cout << " ";
    }
    cout << "\n";

    vector<int> u(n - 1), v(n - 1);
    for (int i = 0; i < n - 1; i++) {
        u[i] = gen.uniform(0, i);
        v[i] = i + 1;
    }
    //shuffle u, v
    {
        auto perm = gen.perm<int>(n);
        for (int i = 0; i < n; i++) {
            u[i] = perm[u[i]];
            v[i] = perm[v[i]];
        }
    }

    for (int i = 0; i < n - 1; i++) {
        cout << u[i] << " " << v[i] << "\n";
    }

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        cout << t << " ";
        if (t == 0) {
            int p = gen.uniform(0, n - 1);
            int x = gen.uniform(0, 1'000'000'000);
            cout << p << " " << x << "\n";
        } else {
            auto u = gen.uniform(0, n - 1);
            auto v = gen.uniform(0, n - 1);
            cout << u << " " << v << "\n";
        }
    }
    return 0;
}
