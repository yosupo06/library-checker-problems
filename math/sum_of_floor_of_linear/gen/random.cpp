#include <iostream>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100'000);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = gen.uniform(1, 1'000'000'000);
        int m = gen.uniform(1, 1'000'000'000);
        int a = gen.uniform(0, m - 1);
        int b = gen.uniform(0, m - 1);

        cout << n << " " << m << " " << a << " " << b << "\n";
    }
    return 0;
}
