#include <utility>
#include <vector>
#include "testlib.h"

int read_set(InStream& stream, int n, const std::vector<std::pair<int, int>>& edges) {
    int k = stream.readInt(0, n, "K");
    std::vector<bool> selected(n);
    for (int i = 0; i < k; ++i) {
        int v = stream.readInt(0, n - 1, "vertex");
        if (selected[v]) stream.quitf(_wa, "vertex %d occurs twice", v);
        selected[v] = true;
    }
    if (!stream.seekEof()) stream.quitf(_wa, "extra output after %d vertices", k);
    for (auto [a, b] : edges) {
        if (selected[a] && selected[b]) stream.quitf(_wa, "vertices %d and %d are adjacent", a, b);
    }
    return k;
}

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int left = inf.readInt();
    int right = inf.readInt();
    int m = inf.readInt();
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.emplace_back(a, left + b);
    }
    int expected = read_set(ans, left + right, edges);
    int actual = read_set(ouf, left + right, edges);
    if (actual < expected) quitf(_wa, "expected %d vertices, got %d", expected, actual);
    if (actual > expected) quitf(_fail, "valid set of size %d exceeds jury size %d", actual, expected);
    quitf(_ok, "maximum independent set of size %d", actual);
}
