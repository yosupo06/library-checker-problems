#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

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
    int a = gen.uniform(1, n);
    int b = gen.uniform(1, n);
    cout << a << " " << b << " 0\n";
    // some pair, both false(= all false)
    a = gen.uniform(-n, -1);
    b = gen.uniform(-n, -1);
    cout << a << " " << b << " 0\n";
    return 0;
}
