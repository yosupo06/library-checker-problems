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

int round_sqrt(int n) {
    int r = 0;
    while ((long long)(r + 1) * (r + 1) <= n) {
        r += 1;
    }
    if ((long long)r * r + r < n) {
        r += 1;
    }
    return r;
}

size_t random_component_limit(
        Random &gen,
        long long seed,
        int &call_index,
        const vector<pair<size_t, size_t>> &fixed_limits,
        size_t upper) {
    gen.uniform01();
    if (0 <= seed && seed < (long long)fixed_limits.size()) {
        const auto [first, second] = fixed_limits[seed];
        call_index += 1;
        return call_index == 1 ? first : second;
    }
    size_t res = upper;
    while (res > 1 && gen.uniform<int>(0, 9) < 7) {
        res = gen.uniform<size_t>(1, res);
    }
    call_index += 1;
    return res;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    const vector<pair<size_t, size_t>> fixed_limits = {
        {2, 1}, {6, 1}, {17, 8}, {14, 11}, {3, 1},
    };
    int component_limit_call_index = 0;

    const auto select = [&](auto &v) -> decltype(auto) {
        return v[gen.uniform<int>(0, v.size() - 1)];
    };

    const auto pop = [&](auto &v) {
        swap(v.back(), v[gen.uniform<int>(0, v.size() - 1)]);
        auto res = std::move(v.back());
        v.pop_back();
        return res;
    };

    vector<pair<int, int>> edges;
    vector<pair<int, int>> edge_buf;

    const auto add_edge = [&](int x, int y) {
        edge_buf.emplace_back(x, y);
    };

    const int n = gen.uniform(N_MIN, N_MAX / 5);
    const int size = gen.uniform<int>(1, round_sqrt(n));

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

    const size_t c2_lim = random_component_limit(
            gen, seed, component_limit_call_index, fixed_limits, c.size());
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
        c.push_back(std::move(sum));
    }

    const size_t c_lim = random_component_limit(
            gen, seed, component_limit_call_index, fixed_limits, c.size());
    while (c.size() != c_lim) {
        vector<int> bridge;
        vector<int> sum;
        for (int i = 0; i != 2; i += 1) {
            vector<int> top = pop(c);
            bridge.push_back(select(top));
            cat(sum, top);
        }
        add_bb(bridge[0], bridge[1]);
        c.push_back(std::move(sum));
    }

    edges = std::move(edge_buf);
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
