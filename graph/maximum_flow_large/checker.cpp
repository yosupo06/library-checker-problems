#include <string>
#include <vector>

#include "testlib.h"

struct Edge {
    int u, v;
    long long capacity;
};

long long check_certificate(InStream& stream, int n, int s, int t,
                            const std::vector<Edge>& edges) {
    long long bound = 0;
    for (const auto& e : edges) bound += e.capacity;
    const long long value = stream.readLong(0, bound, "F");
    std::vector<long long> balance(n, 0);
    for (int i = 0; i < int(edges.size()); ++i) {
        const auto& e = edges[i];
        const long long flow = stream.readLong(0, e.capacity, format("f_%d", i));
        balance[e.u] += flow;
        balance[e.v] -= flow;
    }
    for (int v = 0; v < n; ++v) {
        const long long expected = v == s ? value : (v == t ? -value : 0);
        if (balance[v] != expected) {
            stream.quitf(_wa, "Flow conservation constraint: %d-th vertex should supply " I64 " flow but was " I64,
                         v, expected, balance[v]);
        }
    }
    const std::string cut = stream.readToken(format("[01]{%d}", n), "x");
    if (cut[s] != '0') stream.quitf(_wa, "x_%d(source) must be 0, found: %c", s, cut[s]);
    if (cut[t] != '1') stream.quitf(_wa, "x_%d(sink) must be 1, found: %c", t, cut[t]);
    long long capacity = 0;
    for (const auto& e : edges) {
        if (cut[e.u] == '0' && cut[e.v] == '1') capacity += e.capacity;
    }
    if (capacity != value) {
        stream.quitf(_wa, "cut capacity differs - expected: " I64 ", found: " I64, value, capacity);
    }
    if (!stream.seekEof()) stream.quitf(_wa, "extra tokens");
    return value;
}

int main(int argc, char* argv[]) {
    setName("compare maximum flows");
    registerTestlibCmd(argc, argv);
    const int n = inf.readInt();
    const int m = inf.readInt();
    const int s = inf.readInt();
    const int t = inf.readInt();
    std::vector<Edge> edges(m);
    for (auto& e : edges) {
        e.u = inf.readInt();
        e.v = inf.readInt();
        e.capacity = inf.readLong();
    }
    // Feasible flow + a cut of equal capacity prove optimality independently
    // of the reference output. Validate the reference certificate as well;
    // testlib maps errors in ans to FAIL, rather than blaming the contestant.
    const long long reference = check_certificate(ans, n, s, t, edges);
    const long long actual = check_certificate(ouf, n, s, t, edges);
    ensuref(reference == actual, "maximum flow differs - expected: " I64 ", found: " I64,
            reference, actual);
    quitf(_ok, "OK");
}
