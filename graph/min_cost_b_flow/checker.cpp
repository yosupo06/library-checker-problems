#include <vector>
#include <utility>
#include <exception>

#include "testlib.h"
#include "params.h"

using Flow = long long int;
using Cost = long long int;
using BigCost = __int128_t;

struct Edge {
    size_t s, t;
    Flow lower, upper;
    Cost cost;
};

struct Result {
    bool is_feasible;
    BigCost value;

    static Result infeasible() {
        return Result{false, 0};
    }
    static Result optimal(const BigCost value) {
        return Result{true, value};
    }
};

std::pair<std::vector<Flow>, std::vector<Edge>> readInstance(InStream &is) {
    const size_t n = is.readInt();
    const size_t m = is.readInt();
    std::vector<Flow> bs(n);
    std::vector<Edge> es(m);
    for (auto &b : bs) {
        b = (Flow) is.readLong();
    }
    for (auto &e : es) {
        e.s = (size_t) is.readInt();
        e.t = (size_t) is.readInt();
        e.lower = (Flow) is.readLong();
        e.upper = (Flow) is.readLong();
        e.cost = (Cost) is.readLong();
    }
    return {std::move(bs), std::move(es)};
}

Result readObjectiveValue(InStream &stream) {
    const std::string s = stream.readLine();
    if (s == "infeasible") return Result::infeasible();

    if (s.empty()) {
    stream.quitf(_pe,
           "Objective value shouldn't be the empty string");
    }
    // The length is capped by the length of M_MAX * U_MAX * C_MAX plus one (for '-')
    if (s.size() > 32) {
    stream.quitf(_pe,
           "The given objective value %s is too long", s.c_str());
    }
    if (s == "-") {
    stream.quitf(_pe,
           "The given objective value %s is invalid", s.c_str());
    }

    if (s == "0") {
        return Result::optimal(0);
    }
    bool negative = s[0] == '-';
    size_t pos = negative ? 1 : 0;
    if (s[pos] == '0') {
    stream.quitf(_pe,
           "The given objective value %s has leading zeros", s.c_str());
    }

    BigCost ret{0};
    for (; pos < s.size(); ++pos) {
        const char c = s[pos];
        if ((c < '0') || (c > '9')) {
        stream.quitf(_pe,
               "The given objective value %s contains an invalid charactor %c", s.c_str(), c);
        }
        ret = (ret * 10) + (c - '0');
    }
    return Result::optimal(negative ? -ret : ret);
}

template<class T>
std::string i2s(T value) {
    if (value < 0) return "-" + i2s(-value);
    if (value == 0) return "0";
    std::string s;
    while (value) {
        s += '0' + (value % 10);
        value /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

Result readAndVerifyRationality(const std::vector<Flow> &bs, const std::vector<Edge> &es, InStream &stream) {
    const Result objective_value = readObjectiveValue(stream);
    if (!objective_value.is_feasible) {
        stream.readEof();
        return objective_value;
    }

    const size_t n = bs.size();
    const size_t m = es.size();
    std::vector<Cost> potentials(n);
    std::vector<Flow> flows(m);
    for (auto &pot : potentials) {
        pot = (Cost) stream.readLong(-P_MAX, P_MAX, "p");
        stream.skipBlanks();
    }
    for (auto &flow : flows) {
        flow = (Flow) stream.readLong(-U_MAX, U_MAX, "f");
        stream.skipBlanks();
    }
    stream.readEof();

    BigCost reconstructed_ans = 0;
    std::vector<Flow> b_from_flow(n);
    for (size_t i = 0; i < m; ++i) {
        const auto &e = es[i];
        const auto f = flows[i];
        const auto reduced_cost = e.cost + potentials[e.s] - potentials[e.t];
        b_from_flow[e.s] += f;
        b_from_flow[e.t] -= f;
        reconstructed_ans += ((BigCost) f) * ((BigCost) e.cost);

        // Capacity constraints
        if (f < e.lower) {
            stream.quitf(_wa, "Capacity constraint:"
                         "The given flow on " U64 "-th edge (" I64 ") is lower than the lower bound of the edge (" I64 ")",
                         (unsigned long long int) i, f, e.lower);
        }
        if (f > e.upper) {
            stream.quitf(_wa, "Capacity constraint: "
                         "The given flow on " U64 "-th edge (" I64 ") is greater than the upper bound of the edge (" I64 ")",
                         (unsigned long long int) i, f, e.upper);
        }
        // Complementary slackness constraints
        if ((f > e.lower) && (reduced_cost > 0)) {
            stream.quitf(_wa, "Complementary slackness condition: "
                         "Flow on " U64 "-th edge (" I64 ") is greater than the lower bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is positive",
                         (unsigned long long int) i, f, e.lower, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
        }
        if ((f < e.upper) && (reduced_cost < 0)) {
            stream.quitf(_wa, "Complementary slackness condition: "
                         "Flow on " U64 "-th edge (" I64 ") is less than the upper bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is negative",
                         (unsigned long long int) i, f, e.upper, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
        }
    }
    for (size_t v = 0; v < n; ++v) {
        if (bs[v] != b_from_flow[v]) {
            stream.quitf(_wa, "Flow conservation constraint: "
                         U64 "-th vertex should supply " I64 " flow but was " I64 "",
                         (unsigned long long int) v, bs[v], b_from_flow[v]);
        }
    }
    if (reconstructed_ans != objective_value.value) {
        stream.quitf(_wa,
                     "The given objective value %s didn't match with the value reconstructed from flows %s",
                     i2s(objective_value.value).c_str(), i2s(reconstructed_ans).c_str());
    }

    return objective_value;
}


int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    const auto instance = readInstance(inf);
    const auto &bs = instance.first;
    const auto &es = instance.second;

    const Result judge_solution = readAndVerifyRationality(bs, es, ans);
    const Result user_solution = readAndVerifyRationality(bs, es, ouf);

    if (judge_solution.is_feasible xor user_solution.is_feasible) {
        // Cases the feasibility disagreed

        if (judge_solution.is_feasible) {
            quitf(_wa,
                  "The problem is feasible but the first line of the output was infeasible");
        } else {
            quitf(_fail,
                  "The expected output was `infeasible`, but the submitted answer was a feasible solution");
        }
    } else if (judge_solution.is_feasible) {
        // Not only > case but also < case is a judge failure
        // since they should match by the strong duality.
        ensuref(judge_solution.value == user_solution.value,
                "The submitted answer %s should be correct but did't match with the expected output %s, which indicates a bug in the checker",
                i2s(user_solution.value).c_str(), i2s(judge_solution.value).c_str()
                );

        // Both feasible and the value matched.
        quitf(_ok, "OK");
    } else {
        // Both infeasible.
        quitf(_ok, "OK");
    }
    return 0;
}
