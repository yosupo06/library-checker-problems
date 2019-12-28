#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 200000;

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int x = gen.uniform(0, 1'000'000'000);
        int y = gen.uniform(0, 1'000'000'000);
        cout << x << " " << y << "\n";
    }
    return 0;
}
