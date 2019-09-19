#include "random.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);
    int m = gen.uniform(1, 500'000);
    cout << "p cnf " << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int a = 0, b = 0;
        while (!a) a = gen.uniform(-n, n);
        while (!b) b = gen.uniform(-n, n);
        cout << a << " " << b << " 0\n";
    }
    return 0;
}
