#ifndef INCLUDE_TEST_CASE
#define INCLUDE_TEST_CASE

#include <cassert>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

#include "../params.h"
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

    void add_addquery(int p, int l, int r, int x) {
        qs.emplace_back(ADD_QUERY, p, l, r, x);
    }
    void add_getquery(int p) {
        qs.emplace_back(GET_QUERY, p, -1, -1, -1);
    }

    void add_random_queries(Random& gen, double get_query_ratio = 0.5, const std::vector<int>& h = {}) {
        for (int i = 0; i < q; ++i) {
            int query_type = gen.uniform01() < get_query_ratio;
            int p = gen.uniform(0, n - 1);
            if (query_type == ADD_QUERY) {
                auto dist_range = gen.uniform_pair(0, h.empty() ? n : h[p] + 1);
                int x = gen.uniform(X_MIN, X_MAX);
                add_addquery(p, dist_range.first, dist_range.second, x);
            } else {
                add_getquery(p);
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
            int query_type, p, l, r, x;
            std::tie(query_type, p, l, r, x) = tc.qs[i];
            if (query_type == ADD_QUERY) {
                out << query_type << ' ' << p << ' ' << l << ' ' << r << ' ' << x;
            } else {
                out << query_type << ' ' << p;
            }
            out << '\n';
        }
        return out;
    }
private:
    static constexpr int ADD_QUERY = 0;
    static constexpr int GET_QUERY = 1;

    int n, q;
    std::vector<int> a;
    std::vector<std::pair<int, int>> edges;
    std::vector<std::tuple<int, int, int, int, int>> qs;
};

#endif // INCLUDE_TEST_CASE