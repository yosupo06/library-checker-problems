#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int x, y, m;
        m = gen.uniform(1, 1'000'000'000);
        x = gen.uniform(0, m - 1);
        y = gen.uniform(0, m - 1);
        cout << x << " " << y << " " << m << "\n";
    }
    return 0;
}
