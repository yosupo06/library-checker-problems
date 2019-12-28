#include <iostream>
#include "random.h"

using namespace std;

int main(int, char *argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2800, 3000);
    int k = gen.uniform(9900, 10000);

    set<pair<int, int>> st;
    vector<int> a = gen.perm<int>(n);
    vector<int> b = gen.perm<int>(n);
    a.resize(k);
    b.resize(k);
    vector<int> c(k);
    for (int i = 0; i < n; i++) {
        st.insert({a[i], b[i]});
        c[i] = gen.uniform(1, 998244353 - 1);
    }
    for (int i = n; i < k; i++) {
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
