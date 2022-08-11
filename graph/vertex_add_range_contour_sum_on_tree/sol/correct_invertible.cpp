#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <queue>
#include <random>
#include <stdio.h>
#include <utility>
#include <vector>

namespace default_group {
    template <typename T>
    T add(T x, T y) { return x + y; }
    template <typename T>
    T zero() { return T{}; }
    template <typename T>
    T neg(T x) { return -x; }
}

template <typename T, T(*_add)(T, T) = default_group::add, T(*_zero)() = default_group::zero, T(*_neg)(T) = default_group::neg>
struct FenwickTree {
    using value_type = T;

    FenwickTree(int n = 0) : _n(n), _dat(n + 1, _zero()) {}
    template <typename InputIterator>
    FenwickTree(InputIterator first, InputIterator last) : _n(last - first), _dat(_n + 1, _zero()) {
        for (int i = 1; i <= _n; ++i) {
            _dat[i] = _add(_dat[i], *first++);
            int p = i + (i & -i);
            if (p <= _n) _dat[p] = _add(_dat[p], _dat[i]);
        }
    }
    void add(int i, const value_type& val) {
        assert(0 <= i and i < _n);
        for (++i; i <= _n; i += i & -i) _dat[i] = _add(_dat[i], val);
    }
    value_type sum(int l, int r) const {
        l = std::max(0, l), r = std::min(r, _n);
        return l < r ? _add(sum(r), _neg(sum(l))) : _zero();
    }
private:
    int _n;
    std::vector<value_type> _dat;

    value_type sum(int r) const {
        value_type res = _zero();
        for (; r; r -= r & -r) res = _add(res, _dat[r]);
        return res;
    }
};

template <typename T, T(*_add)(T, T) = default_group::add, T(*_zero)() = default_group::zero, T(*_neg)(T) = default_group::neg>
struct PointAddRangeContourSumOnTree {
    using value_type = T;
private:
    using sequence_type = FenwickTree<value_type, _add, _zero, _neg>;

    struct AuxData {
        int8_t child_index;
        int dep;
    };

    struct TreeNode {
        std::vector<int> adj;
        typename std::array<AuxData, 30>::iterator info_it;
        value_type dat;
    };
public:
    PointAddRangeContourSumOnTree(int n = 0, const value_type& fill_value = _zero()) : PointAddRangeContourSumOnTree(std::vector<value_type>(n, fill_value)) {}
    PointAddRangeContourSumOnTree(const std::vector<value_type>& dat) : _n(dat.size()), _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n) {
        for (int i = 0; i < _n; ++i) _nodes[i].dat = dat[i], _nodes[i].info_it = _info[i].begin();
    }

    void add_edge(int u, int v) {
        _nodes[u].adj.push_back(v);
        _nodes[v].adj.push_back(u);
    }

    void build() {
        int new_node = _n;
        std::vector<int> sub_size(2 * _n, 0);
        std::vector<int> ctr(2 * _n, -1);

        std::vector<int> head(2 * _n), tail(2 * _n), link(2 * _n);
        for (int i = 0; i < _n; ++i) head[i] = tail[i] = i;

        std::vector<value_type> dat(_n);

        auto rec = [&](auto rec, int r, int siz) -> int {
            int c = -1;
            auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                sub_size[u] = 1;
                for (int v : _nodes[u].adj) if (v != p) {
                    get_centroid(get_centroid, v, u);
                    if (v == c) {
                        sub_size[u] = siz - sub_size[c];
                        break;
                    }
                    sub_size[u] += sub_size[v];
                }
                if (c < 0 and sub_size[u] * 2 > siz) c = u;
            };
            get_centroid(get_centroid, r, -1);

            for (int v : _nodes[c].adj) {
                const int comp_size = sub_size[v];
                _nodes[v].adj.erase(std::find(_nodes[v].adj.begin(), _nodes[v].adj.end(), c));
                ctr[v] = rec(rec, v, comp_size);
                sub_size[v] = comp_size;
            }

            auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };
            std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp };

            for (int v : _nodes[c].adj) {
                link[v] = -1;
                pq.push(v);
            }

            auto build_sequence = [&, this](const int root_head, const bool child_index) {
                std::deque<std::pair<int, int>> dq;
                for (int root = root_head; root >= 0; root = link[root]) dq.emplace_back(root, -1);
                value_type sum = _zero();
                auto dat_it = dat.begin();
                int nxt = -1;
                while (dq.size()) {
                    const auto [u, pu] = dq.front();
                    dq.pop_front();
                    if (u == nxt) *dat_it++ = std::exchange(sum, _zero()), nxt = -1;
                    auto &node = _nodes[u];
                    *node.info_it++ = { child_index, int(dat_it - dat.begin()) };
                    sum = _add(sum, node.dat);
                    for (int v : node.adj) if (v != pu) {
                        dq.emplace_back(v, u);
                        if (nxt < 0) nxt = v;
                    }
                }
                *dat_it++ = sum;
                return sequence_type(dat.begin(), dat_it);
            };

            while (pq.size() >= 2) {
                const int u = pq.top(); pq.pop();
                const int v = pq.top(); pq.pop();
                if (pq.empty()) {
                    _par[ctr[u]] = _par[ctr[v]] = c;
                    _subtrees[c][0] = build_sequence(head[u], 0);
                    _subtrees[c][1] = build_sequence(head[v], 1);
                    break;
                }
                sub_size[new_node] = sub_size[u] + sub_size[v];
                ctr[new_node] = new_node;
                _par[ctr[u]] = _par[ctr[v]] = new_node;
                _subtrees[new_node][0] = build_sequence(head[u], 0);
                _subtrees[new_node][1] = build_sequence(head[v], 1);
                head[new_node] = head[u], tail[new_node] = tail[v], link[tail[u]] = head[v];
                pq.push(new_node);
                ++new_node;
            }
            if (pq.size()) {
                int u = pq.top(); pq.pop();
                _par[ctr[u]] = c;
                _subtrees[c][0] = build_sequence(head[u], 0);
            }
            for (int v : _nodes[c].adj) _nodes[v].adj.push_back(c);
            return c;
        };
        rec(rec, 0, _n);
        _par.resize(new_node), _par.shrink_to_fit();
        _subtrees.resize(new_node), _subtrees.shrink_to_fit();
    }

    value_type get(int u) const {
        return _nodes[u].dat;
    }
    void add(int u, const value_type& val) {
        _nodes[u].dat = _add(_nodes[u].dat, val);
        int v = _par[u];
        const auto it_end = _nodes[u].info_it;
        for (auto it = _info[u].begin(); it != it_end; ++it) _subtrees[std::exchange(v, _par[v])][it->child_index].add(it->dep, val);
    }
    void set(int u, const value_type& new_val) {
        add(u, _add(new_val, _neg(get(u))));
    }
    value_type sum(int u, int dl, int dr) const {
        value_type res = dl <= 0 and 0 < dr ? _nodes[u].dat : _zero();
        res = _add(res, _subtrees[u][0].sum(dl - 1, dr - 1));
        res = _add(res, _subtrees[u][1].sum(dl - 1, dr - 1));
        int v = _par[u];
        const auto it_end = _nodes[u].info_it;
        for (auto it = _info[u].begin(); it != it_end; ++it) {
            const int ql = dl - it->dep - 1, qr = dr - it->dep - 1;
            if (v < _n and ql <= 0 and 0 < qr) res = _add(res, _nodes[v].dat);
            res = _add(res, _subtrees[std::exchange(v, _par[v])][it->child_index ^ 1].sum(ql - 1, qr - 1));
        }
        return res;
    }

private:
    int _n;
    std::vector<TreeNode> _nodes;
    std::vector<int> _par;
    std::vector<std::array<AuxData, 30>> _info;
    std::vector<std::array<sequence_type, 2>> _subtrees;
};

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<long long> a(n);
    for (auto &e : a) scanf("%lld", &e);

    PointAddRangeContourSumOnTree<long long> g(a);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g.add_edge(u, v);
    }
    g.build();

    for (int i = 0; i < q; ++i) {
        int query_type;
        scanf("%d", &query_type);

        if (query_type == 0) {
            int p, x;
            scanf("%d %d", &p, &x);
            g.set(p, g.get(p) + x);
        } else {
            int p, l, r;
            scanf("%d %d %d", &p, &l, &r);
            long long ans = g.sum(p, l, r);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
