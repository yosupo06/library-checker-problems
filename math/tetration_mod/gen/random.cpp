#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        ll m = gen.uniform(1LL, 1'000'000'000);
        ll b = gen.uniform(0LL, 1'000'000'000);
        ll a = gen.uniform(0LL, m - 1);
        cout << a << " " << b << " " << p << endl;
    }
    return 0;
}
