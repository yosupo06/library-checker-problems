#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;
const int MA = 1'000'000'000;
const ll MB = 1'000'000'000'000'000'000;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200'000);
    int q = gen.uniform(1, 200'000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(-MA, MA);
        ll b = gen.uniform(-MB, MB);
        cout << a << " " << b << "\n";
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        cout << t << " ";
        if (t == 0) {
            int a = gen.uniform(-MA, MA);
            ll b = gen.uniform(-MB, MB);
            cout << a << " " << b << "\n";
        } else {
            int p = gen.uniform(-MA, MA);
            cout << p << "\n";
        }
    }
    return 0;
}
