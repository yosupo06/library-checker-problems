#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    int q = 500'000;
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(0, 1'000'000'000);
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < q; i++) {
        auto p = gen.uniform_pair(0, n - 1); p.second++;
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}