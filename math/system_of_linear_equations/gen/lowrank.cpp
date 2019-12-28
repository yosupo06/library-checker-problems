#include <iostream>
#include "random.h"

using namespace std;

using ll = long long;
const ll Mod = 998244353;

vector<vector<ll>> gen_matrix(int n, int m, int r, Random& gen) {
    vector<vector<ll>> a(n, vector<ll>(m));
    for (int i = 0; i < r; i++) {
        a[i][i] = gen.uniform(1LL, Mod - 1);
        for (int j = i + 1; j < m; j++) {
            a[i][j] = gen.uniform(0LL, Mod - 1);
        }
    }
    for (int ph = 0; ph < 10000; ph++) {
        if (gen.uniform_bool()) {
            // column add
            int x = gen.uniform(0, n - 1);
            int y = gen.uniform(0, n - 1);
            ll freq = gen.uniform(1LL, Mod - 1);
            if (x == y) continue;
            for (int i = 0; i < m; i++) {
                a[x][i] += freq * a[y][i];
                a[x][i] %= Mod;
            }
        } else {
            // row add
            int x = gen.uniform(0, m - 1);
            int y = gen.uniform(0, m - 1);
            ll freq = gen.uniform(1LL, Mod - 1);
            if (x == y) continue;
            for (int i = 0; i < n; i++) {
                a[i][x] += freq * a[i][y];
                a[i][x] %= Mod;
            }
        }
    }

    // column shuffle
    gen.shuffle(a.begin(), a.end());
    // row shuffle
    for (int i = 0; i < m; i++) {
        int j = gen.uniform(0, i);
        for (int k = 0; k < n; k++) {
            swap(a[k][j], a[k][i]);
        }
    }

    return a;
}

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(400, 500);
    int m = gen.uniform(400, 500);
    int rank = gen.uniform(1, min(n, m));

    auto a = gen_matrix(n, m, rank, gen);

    auto b = vector<ll>(n);

    if (seed % 2 == 0) {
        // random gen b
        for (int i = 0; i < n; i++) {
            b[i] = gen.uniform(0LL, Mod - 1);
        }
    } else {
        // random gen x -> generate b
        auto x = vector<ll>(m);
        for (int i = 0; i < m; i++) {
            x[i] = gen.uniform(0LL, Mod - 1);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                b[i] += a[i][j] * x[j];
                b[i] %= Mod;
            }
        }
    }

    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
            if (j != m - 1) cout << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; i++) {
        cout << b[i];
        if (i != n - 1) cout << " ";
    }
    cout << "\n";
    return 0;
}
