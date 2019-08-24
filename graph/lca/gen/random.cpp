#include <iostream>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, 500'000);
    int q = gen.uniform(1, 500'000);
    cout << n << " " << q << "\n";
    for (int i = 1; i < n; i++) {
        cout << gen.uniform(0, i - 1);
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < q; i++) {
        int u, v;
        do {
            u = gen.uniform(0, n - 1);
            v = gen.uniform(0, n - 1);
        } while (!(u < v));
        cout << u << " " << v << endl;
    }
    return 0;
}