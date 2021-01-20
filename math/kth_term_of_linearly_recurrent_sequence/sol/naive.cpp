#include <iostream>
#include <vector>
using namespace std;

constexpr long long MOD = 998244353;
int main() {
    long long n, k;
    cin >> n >> k;
    if(n > 1000) exit(1);
    if(k > 1000) exit(1);
    vector<long long> a(max(n, k) + 1), c(n + 1);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = n; i <= k; i++) {
        long long buf = 0;
        for(int j = 1; j <= n; j++) buf += c[j] * a[i - j] % MOD;
        a[i] = buf % MOD;
    }
    cout << a[k] << endl;
    return 0;
}