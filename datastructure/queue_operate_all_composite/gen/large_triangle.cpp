#include "random.h"
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int Q_MAX = 200000;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    constexpr char endl = '\n';

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = Q_MAX;
    cout << q << endl;

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        if ((i / 50000) % 2 == 0) {
            if (t == 1) {
                t = 0;
            }
        } else {
            if (t == 0) {
                t = 1;
            }
        }
        if (length == 0 and t == 1) {
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
        cout << endl;
    }
    return 0;
}
