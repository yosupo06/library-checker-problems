#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

constexpr int MOD = 998244353;

int power(int a, int n) {
    int result = 1;
    for (; n; n >>= 1, a = static_cast<long long>(a) * a % MOD) {
        if (n & 1) result = static_cast<long long>(result) * a % MOD;
    }
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    std::vector<std::pair<int, int>> queries(t);
    int max_n = 0;
    for (auto& [n, k] : queries) {
        scanf("%d%d", &n, &k);
        max_n = std::max(max_n, n);
    }
    std::vector<int> fact(max_n + 1, 1), invfact(max_n + 1, 1);
    for (int n = 1; n <= max_n; ++n) fact[n] = static_cast<long long>(fact[n - 1]) * n % MOD;
    invfact[max_n] = power(fact[max_n], MOD - 2);
    for (int n = max_n; n > 0; --n) invfact[n - 1] = static_cast<long long>(invfact[n]) * n % MOD;
    for (auto [n, k] : queries) {
        int answer = 0;
        for (int i = 0; i <= k; ++i) {
            int term = static_cast<long long>(fact[n]) * invfact[i] % MOD * invfact[n - i] % MOD;
            answer += term;
            if (answer >= MOD) answer -= MOD;
        }
        printf("%d\n", answer);
    }
}
