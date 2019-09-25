#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = gen.uniform(1, 100);
    vector<long long> a(q);
    for (int i = 0; i < q; i++) {
        a[i] = gen.uniform(1LL, 1'000'000'000'000'000'000LL);
    }

    cout << q << endl;
    for (auto x: a) {
        cout << x << endl;
    }
    return 0;
}
