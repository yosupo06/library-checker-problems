#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    int k = gen.uniform(0, (n - 1) / 2) * 2;
    k += seed % 2;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << (i == k ? 1 : 0);
        if (i != n - 1) cout << " ";
    }
    printf("\n");
    return 0;
}
