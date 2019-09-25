#include <iostream>
#include "random.h"

using namespace std;

int main(int, char *argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 3000);
    int k = gen.uniform(1, 10000);
    vector<int> a(k);
    vector<int> b(k);
    vector<int> c(k);
    set<pair<int, int>> st;
    for (int i = 0; i < k; i++) {
        do {
            a[i] = gen.uniform(0, n - 1);
            b[i] = gen.uniform(0, n - 1);
        } while (st.count({a[i], b[i]}));
        st.insert({a[i], b[i]});
        c[i] = gen.uniform(1, 998244353 - 1);
    }

    cout << n << " " << k << endl;
    for (int i = 0; i < k; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << endl;
    }
    return 0;
}
