#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500000);
    int q = gen.uniform(1, 500000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(0, 1'000'000'000);
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < q; i++) {
        auto p = gen.uniform_pair(0, n - 1); p.second++;
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}