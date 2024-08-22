#include <cstdio>

using namespace std;

constexpr int mod = 998244353;

void solve() {
    int N;
    scanf("%d", &N);
    if (N < mod / 2) {
        long long x = 1;
        for (int n = 1; n <= N; ++n) x = x * n % mod;
        printf("%lld\n", x);
    } else {
        long long x = mod - 1; // (mod-1)!
        long long y = 1;
        for (int n = N + 1; n <= mod - 1; ++n) { y = y * n % mod; }
        // x / y
        // xy^{mod-2}
        long long n = mod - 2;
        while (n) {
            if (n & 1) x = x * y % mod;
            y = y * y % mod;
            n /= 2;
        }
        printf("%lld\n", x);
    }
}

signed main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; ++t) solve();
    return 0;
}
