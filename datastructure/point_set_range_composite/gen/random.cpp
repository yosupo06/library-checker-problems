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
        int a = gen.uniform(1, 998244353);
        int b = gen.uniform(0, 998244353);
        cout << a << " " << b << "\n";
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        cout << t << " ";
        if (t == 0) {
            int p = gen.uniform(0, n - 1);
            int c = gen.uniform(1, 998244353);
            int d = gen.uniform(0, 998244353);
            cout << p << " " << c << " " << d << "\n";
        } else {
            auto p = gen.uniform_pair(0, n - 1);
            int x = gen.uniform(0, 998244353);
            p.second++;
            cout << p.first << " " << p.second << " " << x << "\n";
        }
    }
    return 0;
}
