#include "random.h"
#include "toptree.hpp"
#include <iostream>

using namespace std;


const int N_AND_Q_MIN = 1;
const int N_AND_Q_MAX = 200'000;
const int A_AND_X_MIN = 0;
const int A_AND_X_MAX = 1'000'000'000;

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_AND_Q_MIN, N_AND_Q_MAX);
    int q = gen.uniform(N_AND_Q_MIN, N_AND_Q_MAX);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(A_AND_X_MIN, A_AND_X_MAX);
        if (i != n - 1) cout << " ";
    }
    cout << "\n";

    vector<int> u(n - 1), v(n - 1);
    for (int i = 0; i < n - 1; i++) {
        u[i] = gen.uniform(0, i);
        v[i] = i + 1;
    }

    {
        auto perm = gen.perm<int>(n);
        for (int i = 0; i < n - 1; i++) {
            u[i] = perm[u[i]];
            v[i] = perm[v[i]];
        }
    }

    dynamic_tree tree(n);

    for (int i = 0; i < n - 1; i++) {
        cout << u[i] << " " << v[i] << "\n";
        tree.link(u[i], v[i]);
    }

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        cout << t << " ";
        if(t == 0) {
          int eidx = gen.uniform(0, n - 2);
          auto p = tree.cut(eidx);
          int u = p.first;
          int v = p.second;
          int w = tree.random_vertex(gen, u);
          tree.link(v, w);
          cout << u << " " << v << " " << w << "\n";
        }
        else if (t == 1) {
            int p = gen.uniform(0, n - 1);
            int x = gen.uniform(A_AND_X_MIN, A_AND_X_MAX);
            cout << p << " " << x << "\n";
        } else {
            auto u = gen.uniform(0, n - 1);
            auto v = gen.uniform(0, n - 1);
            cout << u << " " << v << "\n";
        }
    }
    return 0;
}
