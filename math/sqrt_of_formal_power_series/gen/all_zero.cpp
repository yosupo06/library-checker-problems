#include <iostream>
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);
    
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << 0;
        if (i != n - 1) cout << " ";
    }
    printf("\n");
    return 0;
}
