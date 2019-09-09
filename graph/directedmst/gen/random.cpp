#include <iostream>
#include "random.h"

using namespace std;

struct E {
    int from, to, cost;
};

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200'000);
    int m = gen.uniform(n - 1, (int)min(200'000LL, (long long)n * (n - 1)));

    using P = pair<int, int>;
    set<P> used;
    vector<E> edges;
    auto add_edge = [&](int a, int b, int c) {
        if (used.count({a, b})) return false;
        used.insert({a, b});
        edges.push_back({a, b, c});
        return true;
    };
    for (int i = 1; i < n; i++) {
        add_edge(gen.uniform(0, i - 1), i, 1'000'000'000);
    }
    for (int i = n - 1; i < m; i++) {
        int a, b;
        do {
            a = gen.uniform(0, n - 1);
            b = gen.uniform(0, n - 1);
        } while (a == b || used.count({a, b}));
        int c = gen.uniform(0, 1'000'000'000);
        add_edge(a, b, c);
    }

    auto idx = gen.perm<int>(n);
    int s = idx[0];
    cout << n << " " << m << " " << s << "\n";
    for (auto e: edges) {
        cout << idx[e.from] << " " << idx[e.to] << " " << e.cost << "\n";
    }
    return 0;
}