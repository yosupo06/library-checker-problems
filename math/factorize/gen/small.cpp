#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);

    int q = 100;
    vector<long long> a(q);
    for (int i = 0; i < q; i++) {
        a[i] = seed * 100 + 1 + i;
    }

    cout << q << endl;
    for (auto x: a) {
        cout << x << endl;
    }
    return 0;
}
