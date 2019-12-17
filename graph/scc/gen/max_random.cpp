#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    int m = 500'000;
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        cout << a << " " << b << "\n";
    }
    return 0;
}
