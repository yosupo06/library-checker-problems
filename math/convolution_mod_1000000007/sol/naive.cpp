#include <cassert>
#include <cstdio>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define ALL(x) std::begin(x), std::end(x)
using namespace std;

constexpr int MOD = 1'000'000'007;
vector<int> solve(int n, int m, const vector<int> & a, const vector<int> & b) {
    vector<long long> c(n + m - 1);
    REP (i, n) {
        REP (j, m) {
            c[i + j] += (long long)a[i] * b[j] % MOD;
        }
    }
    REP (k, c.size()) {
        c[k] %= MOD;
    }
    return vector<int>(ALL(c));
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    assert ((long long)n * m <= 1e8);
    vector<int> a(n);
    REP (i, n) {
        scanf("%d", &a[i]);
    }
    vector<int> b(m);
    REP (j, m) {
        scanf("%d", &b[j]);
    }
    vector<int> c = solve(n, m, a, b);
    REP (k, c.size()) {
        printf("%d%c", c[k], k + 1 < (int)c.size() ? ' ' : '\n');
    }
    return 0;
}
