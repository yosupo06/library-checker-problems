#include "random.h"
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int Q_MAX = 500'000;

int main(int, char* argv[]) {
    constexpr char endl = '\n';

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = Q_MAX;
    cout << q << endl;

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        if (length <= Q_MAX / 2) {
            t = 0;
        }
        cout << t;
        if (t == 0) {
            int a = gen.uniform(1, MOD - 1);
            int b = gen.uniform(0, MOD - 1);
            cout << ' ' << a << ' ' << b;
            length++;
        } else if (t == 1) {
            length--;
        } else {
            int x = gen.uniform(0, MOD - 1);
            cout << ' ' << x;
        }
        printf("\n");
    }
    return 0;
}
