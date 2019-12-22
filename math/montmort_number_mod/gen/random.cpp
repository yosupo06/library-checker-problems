#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll n = gen.uniform(1LL, 1'000'000LL);
    ll m = gen.uniform(1LL, 1'000'000'000LL);
    cout << n << " " << m << endl;
    return 0;
}
