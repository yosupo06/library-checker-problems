#ifndef INCLUDE_TEST_CASE
#define INCLUDE_TEST_CASE

#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

struct TestCase {
    TestCase() : TestCase(0, 0, std::vector<int>{}) {}
    template <typename T, std::enable_if_t<std::is_constructible_v<int, T>, std::nullptr_t> = nullptr>
    TestCase(int n, int q, const std::vector<T>& init_a) : n(n), q(q), a(n) {
        assert(int(init_a.size()) == n);
        std::copy(init_a.begin(), init_a.end(), a.begin());
    }

    void add_edge(int u, int v) {
        edges.emplace_back(u, v);
    }

    void add_addquery(int p, int x) {
        qs.emplace_back(ADD_QUERY, p, x, -1);
    }
    void add_sumquery(int p, int l, int r) {
        qs.emplace_back(SUM_QUERY, p, l, r);
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