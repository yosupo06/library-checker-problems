#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        ll a = gen.uniform(0LL, 1'000'000'000LL);
        ll b = gen.uniform(0LL, 1'000'000'000LL);
        ll m = 998244353;
        cout << a << " " << b << " " << m << endl;
    }
    return 0;
}
