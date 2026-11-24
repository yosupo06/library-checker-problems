#include <cstdio>
#include <numeric>
#include <utility>
#include <vector>

using Permutation = std::vector<int>;

Permutation compose(const Permutation& a, const Permutation& b) {
    Permutation c(b.size());
    for (int i = 0; i < int(b.size()); ++i) c[i] = a[b[i]];
    return c;
}

Permutation inverse(const Permutation& p) {
    Permutation q(p.size());
    for (int i = 0; i < int(p.size()); ++i) q[p[i]] = i;
    return q;
}

// Sims filtering preserves the generated group. Unlike a probabilistic
// stopping rule, every candidate is sifted, including dependent candidates.
struct Filter {
    int n;
    std::vector<std::vector<Permutation>> inverse_basis;
    std::vector<Permutation> generators;
    explicit Filter(int degree)
        : n(degree), inverse_basis(n, std::vector<Permutation>(n)) {}

    void insert(Permutation p, int first) {
        for (int i = first; i < n; ++i) {
            if (p[i] == i) continue;
            auto& q = inverse_basis[i][p[i]];
            if (q.empty()) {
                q = inverse(p);
                generators.push_back(std::move(p));
                return;
            }
            p = compose(q, p);
        }
    }
};

int main() {
    int n, k;
    std::scanf("%d%d", &n, &k);
    Filter initial(n);
    for (int j = 0; j < k; ++j) {
        Permutation p(n);
        for (int& x : p) std::scanf("%d", &x);
        initial.insert(std::move(p), 0);
    }
    auto generators = std::move(initial.generators);
    Permutation id(n);
    std::iota(id.begin(), id.end(), 0);
    long long answer = 1;
    for (int base = 0; base < n && !generators.empty(); ++base) {
        std::vector<Permutation> representative(n), inv(n);
        std::vector<int> orbit{base};
        representative[base] = id;
        for (int pos = 0; pos < int(orbit.size()); ++pos) {
            int u = orbit[pos];
            for (const auto& g : generators) {
                int v = g[u];
                if (representative[v].empty()) {
                    representative[v] = compose(g, representative[u]);
                    orbit.push_back(v);
                }
            }
        }
        answer = answer * int(orbit.size()) % 998244353;
        for (int u : orbit) inv[u] = inverse(representative[u]);
        Filter stabilizer(n);
        // Schreier's lemma: these elements generate the stabilizer of base.
        for (int u : orbit) {
            for (const auto& g : generators) {
                stabilizer.insert(compose(inv[g[u]], compose(g, representative[u])), base + 1);
            }
        }
        generators = std::move(stabilizer.generators);
    }
    std::printf("%lld\n", answer);
}
