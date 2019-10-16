#include <iostream>
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100'000;
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        ll p = 998244353;
        ll y = gen.uniform(0LL, p - 1);

        cout << y << " " << p << endl;
    }
    return 0;
}
