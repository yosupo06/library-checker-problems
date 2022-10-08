#ifndef INCLUDE_TEST_CASE_DEPQ
#define INCLUDE_TEST_CASE_DEPQ

#include <iostream>
#include <variant>
#include <vector>

#include "random.h"
#include "generator_params.hpp"

struct AddQuery {
    static constexpr int query_type = 0;
    int x;
};
struct PopMinQuery {
    static constexpr int query_type = 1;
};
struct PopMaxQuery {
    static constexpr int query_type = 2;
};
constexpr int query_type_num = 3;

using Query = std::variant<AddQuery, PopMinQuery, PopMaxQuery>;

struct TestCase {
    int n, q;
    std::vector<int> init_values;
    std::vector<Query> queries;

    TestCase(int n, int q) : n(n), q(q), init_values(n) {}

    void add_add_query(int x) {
        queries.push_back(AddQuery{x});
    }
    void add_min_query() {
        queries.push_back(PopMinQuery{});
    }
    void add_max_query() {
        queries.push_back(PopMaxQuery{});
    }

    void writeln(std::ostream& out) {
        out << n << ' ' << q << '\n';
        for (int i = 0; i < n; ++i) {
            out << init_values[i];
            if (i + 1 != n) out << ' ';
        }
        out << '\n';
        for (const auto &query : queries) {
            if (std::holds_alternative<AddQuery>(query)) {
                out << AddQuery::query_type << ' ' << std::get<AddQuery>(query).x;
            } else if (std::holds_alternative<PopMinQuery>(query)) {
                out << PopMinQuery::query_type;
            } else {
                out << PopMaxQuery::query_type;
            }
            out << '\n';
        }
    }
};

TestCase random_case(Random& gen, const GeneratorParams& params) {
    TestCase tc(params.n, params.q);
    std::generate(tc.init_values.begin(), tc.init_values.end(), [&]{ return gen.uniform(params.min_val, params.max_val); });

    int size_of_multiset = params.n;
    for (int i = 0; i < params.q; ++i) {
        const int r = gen.uniform(0, 99);
        if (size_of_multiset == 0 or r < params.add_query_percent) {
            ++size_of_multiset;
            const int val = gen.uniform(params.min_val, params.max_val);
            tc.add_add_query(val);
        } else if (r < params.add_query_percent + params.min_query_percent) {
            --size_of_multiset;
            tc.add_min_query();
        } else {
            --size_of_multiset;
            tc.add_max_query();
        }
    }

    return tc;
}

#endif // INCLUDE_TEST_CASE_DEPQ
