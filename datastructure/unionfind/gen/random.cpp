#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int q = gen.uniform(1, 200000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < q; i++) {
        cout
        << gen.uniform_bool() << " "
        << gen.uniform(0, n - 1) << " "
        << gen.uniform(0, n - 1) << "\n";
    }
    return 0;
}