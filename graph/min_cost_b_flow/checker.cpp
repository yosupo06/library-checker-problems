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

template<class T>
T s2i_unchecked(std::string s, const size_t max_len) {
    if (s.empty()) {
        throw std::runtime_error("Got an empty string");
    }
    if (s.size() > max_len) {
        throw std::runtime_error("Given string was too long: " + s);
    }
    bool negative = s[0] == '-';
    if (negative) s = s.substr(1);
    T ret{0};
    for (const auto &c : s) {
        if ((c < '0') || (c > '9')) {
            throw std::runtime_error("Given string contained non-digital charactor" + s);
        }
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
    if (first_line_of_ans == "infeasible") {
        ouf.readEof();
        if (first_line_of_ans != first_line_of_ouf) {
            quitf(_wa, "The problem was infeasible but the first line of the output was %s", first_line_of_ouf.c_str());
        }
        quitf(_ok, "OK");
    } else {
        if (first_line_of_ans != first_line_of_ouf) {
            quitf(_wa, "The minimum value is %s but the output was %s", first_line_of_ouf.c_str(), first_line_of_ans.c_str());
        }
    }
    const __int128_t optimal_value = s2i_unchecked<__int128_t>(first_line_of_ouf, 32);

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
        if (f < e.lower) {
            quitf(_wa, "Capacity constraint:"
                   "The given flow on %ld-th edge (" I64 ") is lower than the lower bound of the edge (" I64 ")",
                   i, f, e.lower);
        }
        if (f > e.upper) {
            quitf(_wa, "Capacity constraint: "
                   "The given flow on %ld-th edge (" I64 ") is greater than the upper bound of the edge (" I64 ")",
                   i, f, e.upper);
        }
        // Complementary slackness constraints
        if ((f > e.lower) && (reduced_cost > 0)) {
            quitf(_wa, "Complementary slackness condition: "
                   "Flow on %ld-th edge (" I64 ") is greater than the lower bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is positive",
                   i, f, e.lower, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
        }
        if ((f < e.upper) && (reduced_cost < 0)) {
            quitf(_wa, "Complementary slackness condition: "
                   "Flow on %ld-th edge (" I64 ") is less than the upper bound (" I64 "), but the reduced cost (" I64 " = " I64 " + " I64 " - " I64 ") is negative",
                   i, f, e.upper, reduced_cost, e.cost, potentials[e.s], potentials[e.t]);
        }
    }
    for (size_t v = 0; v < n; ++v) {
        if (bs[v] != b_from_flow[v]) {
            quitf(_wa, "Flow conservation constraint: "
                   "%ld-th vertex should supply " I64 " flow but was " I64 "",
                   v, bs[v], b_from_flow[v]);
        }
    }
    if (reconstructed_ans != optimal_value) {
        // Since we already ensured that optimal_value is correct and the given primal/dual pair satisfisfy the constraints,
        // these values should match or otherwise we have an error in either logic somewhere above or both in the answer and users' solution.
        quitf(_fail, "The given minimum value %s didn't match the value reconstructed from flows %s",
              first_line_of_ouf.c_str(), i2s(reconstructed_ans).c_str()
              );
    }
    quitf(_ok, "OK");
}
