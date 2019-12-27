#include "random.h"
#include "../params.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_AND_Q_MIN, 20ll);
    int q = gen.uniform(N_AND_Q_MIN, 20ll);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
        ll b = gen.uniform(-B_ABS_MAX, B_ABS_MAX);
        cout << a << " " << b << "\n";
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        cout << t << " ";
        if (t == 0) {
            int a = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
            ll b = gen.uniform(-B_ABS_MAX, B_ABS_MAX);
            cout << a << " " << b << "\n";
        } else {
            int p = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
            cout << p << "\n";
        }
    }
    return 0;
}
