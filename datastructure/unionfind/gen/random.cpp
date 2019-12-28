#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int q = gen.uniform(1, 200000);
    cout << n << " " << q << "\n";
    for (int i = 0; i < q; i++) {
        int ty = gen.uniform_bool();
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        cout << ty << " " << a << " " << b << "\n";
    }
    return 0;
}