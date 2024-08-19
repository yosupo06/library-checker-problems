#ifndef INCLUDE_TEST_CASE
#define INCLUDE_TEST_CASE

#include <cassert>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

#include "gen_tree.hpp"

struct TestCase {
    TestCase(int n = 0, int q = 0) : n(n), q(q), a(n) {}

    void set_random_init_values(Random &gen) {
        for (auto &e : a) e = gen.uniform(A_MIN, A_MAX);
    }
    template <typename T>
    void set_init_values(const std::vector<T> &init_a) {
        std::copy(std::begin(init_a), std::end(init_a), std::begin(a));
    }

    void add_edge(int u, int v) {
        edges.emplace_back(u, v);
    }
    void add_edges(const std::vector<std::pair<int, int>>& edges) {
        for (const auto& [u, v] : edges) add_edge(u, v);
    }

    void add_addquery(int p, int x) {
        qs.emplace_back(ADD_QUERY, p, x, -1);
    }
    void add_sumquery(int p, int l, int r) {
        qs.emplace_back(SUM_QUERY, p, l, r);
    }

    void add_random_queries(Random& gen, double sum_query_ratio = 0.5, const std::vector<int>& h = {}) {
        for (int i = 0; i < q; ++i) {
            int query_type = gen.uniform01() < sum_query_ratio;
            int p = gen.uniform(0, n - 1);
            if (query_type == 0) {
                int x = gen.uniform(X_MIN, X_MAX);
                add_addquery(p, x);
            } else {
                auto dist_range = gen.uniform_pair(0, h.empty() ? n : h[p] + 1);
                add_sumquery(p, dist_range.first, dist_range.second);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const TestCase& tc) {
        assert(tc.n - 1 == int(tc.edges.size()));
        assert(tc.q == int(tc.qs.size()));

        out << tc.n << ' ' << tc.q << '\n';
        for (int i = 0; i < tc.n; ++i) {
            out << tc.a[i];
            if (i + 1 != tc.n) out << ' ';
        }
        out << '\n';
        for (int i = 0; i < tc.n - 1; ++i) {
            int u, v;
            std::tie(u, v) = tc.edges[i];
            out << u << ' ' << v;
            if (i + 1 != tc.n - 1) {
                out << '\n';
            } else {
                out << '\n';
            }
        }
        for (int i = 0; i < tc.q; ++i) {
            int query_type, p, x, y;
            std::tie(query_type, p, x, y) = tc.qs[i];
            if (query_type == ADD_QUERY) {
                assert(y < 0);
                out << query_type << ' ' << p << ' ' << x;
            } else {
                assert(0 <= x and x <= y and y <= tc.n);
                out << query_type << ' ' << p << ' ' << x << ' ' << y;
            }
            if (i + 1 != tc.q) {
                out << '\n';
            }
        }
        return out;
    }
private:
    static constexpr int ADD_QUERY = 0;
    static constexpr int SUM_QUERY = 1;

    int n, q;
    std::vector<int> a;
    std::vector<std::pair<int, int>> edges;
    std::vector<std::tuple<int, int, int, int>> qs;
};

#endif // INCLUDE_TEST_CASE