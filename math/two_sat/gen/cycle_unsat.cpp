#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000 - 2;
    int m = 500'000;

    cout << "p cnf " << n << " " << m << "\n";

    // all same
    for (int i = 1; i < n; i++) {
        cout << i << " " << - (i + 1) << " 0\n";
    }
    cout << n << " " << - 1 << " 0\n";

    // some pair, both true(= all true)
    cout << gen.uniform(1, n) << " " << gen.uniform(1, n) << " 0\n";
    // some pair, both false(= all false)
    cout << gen.uniform(-n, -1) << " " << gen.uniform(-n, -1) << " 0\n";
    return 0;
}
