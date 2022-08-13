#include <array>
#include <cassert>
#include <cstdint>
#include <deque>
#include <map>
#include <queue>
#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>

template <typename T, T(*op)(T, T), T(*e)()>
struct SegmentTree {
    using value_type = T;

    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : _n(n), _seg(2 * n, e()) {}
    SegmentTree(const std::vector<value_type> &a) : _n(a.size()), _seg(2 * _n) {
        std::copy(a.begin(), a.end(), _seg.begin() + _n);
        for (int i = _n - 1; i > 0; --i) {
            _seg[i] = op(_seg[2 * i + 0], _seg[2 * i + 1]);
        }
    }
    value_type get(int i) const {
        assert(0 <= i and i < _n);
        return _seg[_n + i];
    }
    void set(int i, const value_type &new_val) {
        assert(0 <= i and i < _n);
        for (_seg[i += _n] = new_val; i >>= 1;) _seg[i] = op(_seg[2 * i + 0], _seg[2 * i + 1]);
    }
    value_type prod(int l, int r) const {
        assert(0 <= l and l <= r and r <= _n);
        value_type sl = e(), sr = e();
        for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sl = op(sl, _seg[l++]);
            if (r & 1) sr = op(_seg[--r], sr);
        }
        return op(sl, sr);
    }
private:
    int _n;
    std::vector<value_type> _seg;
};

template <typename T, T(*op)(T, T), T(*e)()>
struct PointSetRangeContourSumOnTree {
    PointSetRangeContourSumOnTree() {}
    PointSetRangeContourSumOnTree(int n, const T& fill_value) : PointSetRangeContourSumOnTree(std::vector<T>(n, fill_value)) {}
    PointSetRangeContourSumOnTree(const std::vector<T>& dat) : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _info(_n), _nodes(_n), _dat(dat) {
        _par.reserve(2 * _n);
        for (int i = 0; i < _n; ++i) _info[i].reserve(30);
    }

    using segtree_type = SegmentTree<T, op, e>;

    struct AuxData {
        int segtree_index;
        int8_t child_index;
        int dist;
    };

    struct Node {
        std::vector<int> _sep;
        segtree_type _seq;

        Node() {}
        Node(const std::vector<std::vector<int>>& g, const std::vector<int8_t>& removed, const std::vector<int>& roots, const bool child_index, std::vector<std::vector<AuxData>>& info, const std::vector<T>& dat, int siz) {
            std::vector<T> reordered_dat(siz);
            _sep.push_back(0);
            std::deque<std::tuple<int, int, int>> dq;
            for (int r : roots) dq.emplace_back(r, -1, 0);
            int pre_dist = 0, cnt = 0;
            while (dq.size()) {
                const auto [u, pu, du] = dq.front();
                dq.pop_front();
                if (du == pre_dist + 1) _sep.push_back(cnt), pre_dist = du;
                info[u].push_back({ cnt, child_index, du });
                reordered_dat[cnt++] = dat[u];
                for (int v : g[u]) if (v != pu and not removed[v]) dq.emplace_back(v, u, du + 1);
            }
            _sep.push_back(cnt);
            _seq = segtree_type(reordered_dat);
        }

        void set(int i, const T& val) {
            _seq.set(i, val);
        }
        T prod(int dl, int dr) const {
            dl = std::max(dl, 0);
            dr = std::min(dr, int(_sep.size()) - 1);
            return dl < dr ? _seq.prod(_sep[dl], _sep[dr]) : e();
        }
    };

    void add_edge(int u, int v) {
        _g[u].push_back(v);
        _g[v].push_back(u);
    }

    void build() {
        std::vector<int> sub_size(_n, 0);
        std::vector<int> ctr(_n, -1);
        sub_size.reserve(2 * _n);
        ctr.reserve(2 * _n);
        std::vector<std::vector<int>> ch(_n);
        ch.reserve(2 * _n);

        auto merge = [&](std::vector<int>&& l, std::vector<int>&& r) -> std::vector<int>&& {
            if (l.size() > r.size()) std::swap(l, r);
            for (int v : l) r.push_back(v);
            return std::move(r);
        };

        auto rec = [&](auto rec, int r, int siz) -> int {
            int c = -1;
            auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                sub_size[u] = 1;
                for (int v : _g[u]) {
                    if (v == p or _removed[v]) continue;
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

            _removed[c] = true;
            for (int v : _g[c]) {
                if (_removed[v]) continue;
                const int comp_size = sub_size[v];
                ctr[v] = rec(rec, v, comp_size);
                sub_size[v] = comp_size;
            }

            auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };
            std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp };

            for (int v : _g[c]) {
                if (_removed[v]) continue;
                ch[v] = { v };
                pq.push(v);
            }

            while (pq.size() >= 2) {
                const int u = pq.top(); pq.pop();
                const int v = pq.top(); pq.pop();
                if (pq.empty()) {
                    _par[ctr[u]] = _par[ctr[v]] = c;
                    _nodes[c][0] = Node{ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };
                    _nodes[c][1] = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };
                    break;
                }
                const int new_node = sub_size.size();
                sub_size.push_back(sub_size[u] + sub_size[v]);
                ctr.push_back(new_node);
                _par.push_back(-1);
                _par[ctr[u]] = _par[ctr[v]] = new_node;
                _nodes.emplace_back();
                _nodes[new_node][0] = Node{ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };
                _nodes[new_node][1] = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };
                ch.push_back(merge(std::move(ch[u]), std::move(ch[v])));
                ch[u].clear(), ch[u].shrink_to_fit();
                ch[v].clear(), ch[v].shrink_to_fit();
                pq.push(new_node);
            }
            if (pq.size()) {
                int u = pq.top(); pq.pop();
                _par[ctr[u]] = c;
                _nodes[c][0] = Node{ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };
            }
            _removed[c] = false;
            return c;
        };
        rec(rec, 0, _n);
    }

    T get(int u) const {
        return _dat[u];
    }
    void set(int u, const T& val) {
        _dat[u] = val;
        int v = _par[u];
        for (const auto& info : _info[u]) {
            _nodes[std::exchange(v, _par[v])][info.child_index].set(info.segtree_index, val);
        }
    }
    T prod(int u, int dl, int dr) const {
        T res = dl <= 0 and 0 < dr ? _dat[u] : e();
        res = op(res, _nodes[u][0].prod(dl - 1, dr - 1));
        res = op(res, _nodes[u][1].prod(dl - 1, dr - 1));
        int v = _par[u];
        for (const auto& info : _info[u]) {
            int ql = dl - info.dist - 2, qr = dr - info.dist - 2;
            if (v < _n and ql <= -1 and -1 < qr) res = op(res, _dat[v]);
            res = op(res, _nodes[std::exchange(v, _par[v])][info.child_index ^ 1].prod(ql, qr));
        }
        return res;
    }

private:
    int _n;
    std::vector<std::vector<int>> _g;
    std::vector<int> _par;
    std::vector<int8_t> _removed;
    std::vector<std::vector<AuxData>> _info;
    std::vector<std::array<Node, 2>> _nodes;
    std::vector<T> _dat;
};

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0LL;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<long long> a(n);
    for (auto &e : a) scanf("%lld", &e);

    PointSetRangeContourSumOnTree<long long, op, e> g(a);
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
            long long ans = g.prod(p, l, r);
            printf("%lld\n", ans);
        }
    }

    return 0;
}