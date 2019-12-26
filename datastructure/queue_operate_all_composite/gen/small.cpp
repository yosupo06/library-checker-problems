#include "random.h"
#include <iostream>

using namespace std;

const int MOD = 998244353;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    constexpr char endl = '\n';

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = gen.uniform(1, 5);
    cout << 2 * q << endl;

    int length = 0;
    for (int i = 0; i < q; i++) {
        const int table[4] = { 0, 0, 1 };
        int t = table[gen.uniform(0, 3 - 1)];
        if (length == 0 and t == 1) {
            t = 0;
        }
        cout << t;
        if (t == 0) {
            int a = gen.uniform(1, 10);
            int b = gen.uniform(0, 10);
            cout << ' ' << a << ' ' << b;
            length++;
        } else if (t == 1) {
            length--;
        } else {
            int x = gen.uniform(0, MOD - 1);
            cout << ' ' << x;
        }
        cout << endl;
        int x = gen.uniform(0, 10);
        cout << 2 << ' ' << x << endl;
    }
    return 0;
}
