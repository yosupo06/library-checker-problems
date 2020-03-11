#include <cmath>
#include <cstddef>
#include <cstdio>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

void cat(vector<int> &l, vector<int> &r) {
    if (l.size() < r.size()) {
        swap(l, r);
    }
    l.insert(l.end(), r.begin(), r.end());
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const auto select = [&](auto &v) -> decltype(auto) {
        return v[gen.uniform<int>(0, v.size() - 1)];
    };

    const auto pop = [&](auto &v) {
        swap(v.back(), v[gen.uniform<int>(0, v.size() - 1)]);
        auto res = move(v.back());
        v.pop_back();
        return res;
    };

    vector<pair<int, int>> edges;
    vector<pair<int, int>> edge_buf;

    const auto add_edge = [&](int x, int y) {
        edge_buf.emplace_back(x, y);
    };

    const int n = gen.uniform<int>(N_MIN, 100);
    int size = gen.uniform<int>(1, sqrt(n) + 0.5);
    if (gen.uniform_bool()) {
        size = n / size;
    }

    vector<vector<int>> b(size);
    for (int i = 0; i != n; i += 1) {
        select(b).push_back(i);
    }
    
    const auto add_bb = [&](int x, int y) {
        int x_, y_;
        do {
            x_ = select(b[x]);
            y_ = select(b[y]);
        } while (x_ == y_);
        add_edge(x_, y_);
    };

    vector<vector<int>> c;
    for (int i = 0; i != size; i += 1) {
        if (!b[i].empty()) {
            c.push_back({i});
        }
    }

    const size_t c2_lim = pow(c.size(), gen.uniform01()) + 0.5;
    while (c.size() != c2_lim) {
        vector<int> cycle;
        vector<int> sum;
        int cn = 2;
        while (c.size() - cn + 1 != c2_lim
            && gen.uniform01() < 0.7) {
            cn += 1;
        }
        for (int i = 0; i != cn; i += 1) {
            vector<int> top = pop(c);
            cycle.push_back(select(top));
            cat(sum, top);
        }
        for (int i = 0; i != cn; i += 1) {
            add_bb(cycle[i], cycle[(i + 1) % cn]);
        }
        c.push_back(move(sum));
    }

    const size_t c_lim = pow(c.size(), gen.uniform01()) + 0.5;
    while (c.size() != c_lim) {
        vector<int> bridge;
        vector<int> sum;
        for (int i = 0; i != 2; i += 1) {
            vector<int> top = pop(c);
            bridge.push_back(select(top));
            cat(sum, top);
        }
        add_bb(bridge[0], bridge[1]);
        c.push_back(move(sum));
    }

    edges = move(edge_buf);
    edge_buf.clear();

    for (int i = 0; i != size; i += 1) {
        const int bs = b[i].size();
        if (bs <= 1) continue;
        const int bm = gen.uniform(bs * 3, bs * 5);
        for (int j = 0; j != bm; j += 1) {
            add_bb(i, i);
        }
    }

    gen.shuffle(edge_buf.begin(),edge_buf.end());
    edges.insert(edges.end(), edge_buf.begin(), edge_buf.end());
    if (edges.size() > M_MAX) {
        edges.resize(M_MAX);
    }

    gen.shuffle(edges.begin(), edges.end());

    if (edges.empty()) {
        edges.emplace_back(0, 0);
    }

    for (auto &e : edges) {
        if (gen.uniform_bool()) {
            swap(e.first, e.second);
        }
    }

    const int m = edges.size();
    printf("%d %d\n", n, m);
    for (const auto &e : edges) {
        printf("%d %d\n", e.first, e.second);
    }
}
