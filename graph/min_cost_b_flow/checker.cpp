#include <vector>
#include <utility>
#include <exception>

#include "testlib.h"
#include "params.h"

using Flow = long long int;
using Cost = long long int;

struct Edge {
    size_t s, t;
    Flow lower, upper;
    Cost cost;
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

__int128_t read_optimal_value(const std::string s) {
    quitif(s.empty(), _pe,
           "Optimal value shouldn't be the empty string");
    // The length is capped by the length of M_MAX * U_MAX * C_MAX plus one (for '-')
    quitif(s.size() > 32, _pe,
           "The given optimal value %s is too long as a string", s.c_str());
    quitif(s == "-", _pe,
           "The given optimal value %s is invalid", s.c_str());

    if (s == "0") {
        return 0;
    }
    bool negative = s[0] == '-';
    size_t pos = negative ? 1 : 0;
    quitif(s[pos] == '0', _pe,
           "The given optimal value %s has leading zeros", s.c_str());

    __int128_t ret{0};
    for (; pos < s.size(); ++pos) {
        const char c = s[pos];
        quitif((c < '0') || (c > '9'), _pe,
               "The given optimal value %s contains an invalid charactor %c", s.c_str(), c);
        ret = (ret * 10) + (c - '0');
    }
    return negative ? -ret : ret;
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

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    const auto instance = readInstance(inf);
    const auto &bs = instance.first;
    const auto &es = instance.second;
    const size_t n = bs.size();
    const size_t m = es.size();

    const std::string first_line_of_ans = ans.readLine();
    const std::string first_line_of_ouf = ouf.readLine();
    if (first_line_of_ouf == "infeasible") {
        quitif(first_line_of_ans != first_line_of_ouf, _wa,
               "The problem is feasible but the first line of the output was infeasible");
        ouf.readEof();
        quitf(_ok, "OK");
    }
    // Now the user's output is not infeasible. We verify the optimal value (the first line) at the end of the checker
    // to tolerate bug of the model solution as much as possible.

    std::vector<Cost> potentials(n);
    std::vector<Flow> flows(m);
    for (auto &pot : potentials) {
        pot = (Cost) ouf.readLong(-P_MAX, P_MAX, "p");
        ouf.skipBlanks();
    }
    for (auto &flow : flows) {
        flow = (Flow) ouf.readLong(-U_MAX, U_MAX, "f");
        ouf.skipBlanks();
    }
    ouf.readEof();

    __int128_t reconstructed_ans = 0;
    std::vector<Flow> b_from_flow(n);
    for (size_t i = 0; i < m; ++i) {
        const auto &e = es[i];
        const auto f = flows[i];
        const auto reduced_cost = e.cost + potentials[e.s] - potentials[e.t];
        b_from_flow[e.s] += f;
        b_from_flow[e.t] -= f;
        reconstructed_ans += ((__int128_t) f) * ((__int128_t) e.cost);

        // Capacity constraints
        quitif(f < e.lower, _wa, "Capacity constraint:"
               "The given flow on " U64 "-th edge (" I64 ") is lower than the lower bound of the edge (" I64 ")",
               (unsigned long long int) i, f, e.lower);
        quitif(f > e.upper, _wa, "Capacity constraint: "
               "The given flow on " U64 "-th edge (" I64 ") is greater than the upper bound of the edge (" I64 ")",
               (unsigned long long int) i, f, e.upper);
        // Complementary slackness constraints
        quitif((f > e.lower) && (reduced_cost > 0), _wa, "Complementary slackness condition: "
              "Flow on " U64 "-th edge (" I64 ") is greater than the lower bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is positive",
              (unsigned long long int) i, f, e.lower, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
        quitif((f < e.upper) && (reduced_cost < 0), _wa, "Complementary slackness condition: "
              "Flow on " U64 "-th edge (" I64 ") is less than the upper bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is negative",
              (unsigned long long int) i, f, e.upper, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
    }
    for (size_t v = 0; v < n; ++v) {
        quitif(bs[v] != b_from_flow[v], _wa, "Flow conservation constraint: "
              U64 "-th vertex should supply " I64 " flow but was " I64 "",
              (unsigned long long int) v, bs[v], b_from_flow[v]);
    }

    // Now we've validated that the user's solution was a feasible solution.
    // We're going to validate the first line of the user's solution and the judge solution.
    ensuref(first_line_of_ans != "infeasible", "The expected output was `infeasible`, but the submitted answer was a feasible solution.");

    const __int128_t optimal_value_ouf = read_optimal_value(first_line_of_ouf);
    quitif(reconstructed_ans != optimal_value_ouf, _wa,
           "The given minimum value %s didn't match the value reconstructed from flows %s",
           first_line_of_ouf.c_str(), i2s(reconstructed_ans).c_str());

    // By the strong duality, `optimal_value_ouf` should be correct.
    // So this disagreement means that we have an error in either logic somewhere above or in the judge solution.
    ensuref(first_line_of_ans == first_line_of_ouf,
            "The submitted answer %s should be correct but did't match with the expected output %s",
            first_line_of_ouf.c_str(), first_line_of_ans.c_str());

    quitf(_ok, "OK");
}
