#include <algorithm>
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

template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
struct PointGetRangeContourOperate {
    using value_type = T;
    using operator_type = F;
private:
    struct CommutativeDualSegmentTree {
        CommutativeDualSegmentTree(int n = 0): _n(n), _laz(2 * _n, id()) {}
        void apply(int l, int r, const operator_type& f) {
            l = std::max(l, 0), r = std::min(r, _n);
            for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) _laz[l] = composition(f, _laz[l]), ++l;
                if (r & 1) --r, _laz[r] = composition(f, _laz[r]);
            }
        }
        operator_type get(int i) const {
            operator_type res = id();
            for (i += _n; i; i >>= 1) res = composition(res, _laz[i]);
            return res;
        }
    private:
        int _n;
        std::vector<operator_type> _laz;
    };

    using sequence_type = CommutativeDualSegmentTree;

    struct AuxInfo {
        int8_t child_index;
        int dep;
    };

    struct TreeNode {
        std::vector<int> adj;
        typename std::array<AuxInfo, 30>::iterator info_it;
    };
public:
    PointGetRangeContourOperate(int n = 0): _n(n), _dat(_n), _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n) {}

    void add_edge(int u, int v) {
        _nodes[u].adj.push_back(v);
        _nodes[v].adj.push_back(u);
    }
    // O(NlogN)
    void build(const std::vector<value_type>& a) {
        for (int i = 0; i < _n; ++i) _dat[i] = a[i], _nodes[i].info_it = _info[i].begin();

        int new_node = _n;
        std::vector<int> sub_size(2 * _n, 0);
        std::vector<int> ctr(2 * _n, -1);

        std::vector<int> head(2 * _n), tail(2 * _n), link(2 * _n);
        for (int i = 0; i < _n; ++i) head[i] = tail[i] = i;

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
                int dep = 0, nxt = -1;
                while (dq.size()) {
                    const auto [u, pu] = dq.front();
                    dq.pop_front();
                    if (u == nxt) ++dep, nxt = -1;
                    auto& node = _nodes[u];
                    *node.info_it++ = { child_index, dep };
                    for (int v : node.adj) if (v != pu) {
                        dq.emplace_back(v, u);
                        if (nxt < 0) nxt = v;
                    }
                }
                return sequence_type(++dep);
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

    // O((logN)^2)
    value_type get(int u) const {
        value_type res = _dat[u];
        int v = _par[u];
        const auto it_end = _nodes[u].info_it;
        for (auto it = _info[u].begin(); it != it_end; ++it) res = mapping(_subtrees[std::exchange(v, _par[v])][it->child_index].get(it->dep), res);
        return res;
    }
    // O(1)
    void apply(int u, const operator_type& f) {
        _dat[u] = mapping(f, _dat[u]);
    }
    // O((logN)^2)
    void apply(int u, int dl, int dr, const operator_type& f) {
        if (dl <= 0 and 0 < dr) _dat[u] = mapping(f, _dat[u]);
        _subtrees[u][0].apply(dl - 1, dr - 1, f);
        _subtrees[u][1].apply(dl - 1, dr - 1, f);
        int v = _par[u];
        const auto it_end = _nodes[u].info_it;
        for (auto it = _info[u].begin(); it != it_end; ++it) {
            int ql = dl - it->dep - 1, qr = dr - it->dep - 1;
            if (v < _n and ql <= 0 and 0 < qr) _dat[v] = mapping(f, _dat[v]);
            _subtrees[std::exchange(v, _par[v])][it->child_index ^ 1].apply(ql - 1, qr - 1, f);
        }
    }

private:
    int _n;
    std::vector<value_type> _dat;
    std::vector<TreeNode> _nodes;
    std::vector<int> _par;
    std::vector<std::array<AuxInfo, 30>> _info;
    std::vector<std::array<sequence_type, 2>> _subtrees;
};

long long mapping(long long f, long long x) {
    return f + x;
}
long long composition(long long f, long long g) {
    return f + g;
}
long long id() {
    return 0LL;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<long long> a(n);
    for (auto& e : a) scanf("%lld", &e);

    PointGetRangeContourOperate<long long, long long, mapping, composition, id> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g.add_edge(u, v);
    }
    g.build(a);

    for (int i = 0; i < q; ++i) {
        int query_type;
        scanf("%d", &query_type);

        if (query_type == 0) {
            int p, l, r, x;
            scanf("%d %d %d %d", &p, &l, &r, &x);
            g.apply(p, l, r, x);
        } else {
            int p;
            scanf("%d", &p);
            long long ans = g.get(p);
            printf("%lld\n", ans);
        }
    }

    return 0;
}