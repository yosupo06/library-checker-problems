// Incorrect: different orbits need not admit independent actions.
#include <cstdio>
#include <vector>

int main() {
    int n, k;
    std::scanf("%d%d", &n, &k);
    std::vector<std::vector<int>> p(k, std::vector<int>(n));
    for (auto& g : p) for (int& x : g) std::scanf("%d", &x);
    std::vector<bool> seen(n);
    long long answer = 1;
    for (int i = 0; i < n; ++i) {
        if (seen[i]) continue;
        seen[i] = true;
        std::vector<int> orbit{i};
        for (int j = 0; j < int(orbit.size()); ++j) {
            for (const auto& g : p) {
                int v = g[orbit[j]];
                if (!seen[v]) {
                    seen[v] = true;
                    orbit.push_back(v);
                }
            }
        }
        for (int j = 2; j <= int(orbit.size()); ++j) answer = answer * j % 998244353;
    }
    std::printf("%lld\n", answer);
}
