#include <iostream>
#include <vector>
using namespace std;

constexpr long long MOD = 998244353;
int main() {
    long long n, k, m;
    cin >> n >> k >> m;
    if (n > 1000) exit(1);
    if (k > 1000) exit(1);
    if (m > 1000) exit(1);
    vector<long long> a(max(n + 1, k + m)), c(n + 1);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = n; i < k + m; i++) {
        long long buf = 0;
        for (int j = 1; j <= n; j++) buf += c[j] * a[i - j] % MOD;
        a[i] = buf % MOD;
    }
    for (int i = k; i < k + m; i++) {
        cout << a[i];
        if (i + 1 < k + m) cout << ' ';
    }
    cout << endl;
    return 0;
}