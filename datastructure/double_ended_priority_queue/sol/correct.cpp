#include <cassert>
#include <cstdio>
#include <vector>
#include <functional>
#include <type_traits>
#include <utility>

template <
    typename T, typename Comp = std::less<T>,
    std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t> = nullptr
>
struct IntervalHeap {
    using value_type = T;

    IntervalHeap() {}
    IntervalHeap(const Comp& comp) : _comp(comp) {}

    void reserve(int capacity) { _dat.reserve(capacity); }

    bool empty() const { return _dat.empty(); }
    int size() const { return _dat.size(); }

    void push(const value_type& v) {
        _dat.push_back(v);
        fix_up(_dat.size() - 1);
    }

    value_type pop_max() {
        assert(_dat.size());
        const int idx = max_heap_top_index();
        std::swap(_dat[idx], _dat.back());
        value_type res = std::move(_dat.back());
        _dat.pop_back();
        fix_max_heap_down(idx);
        return res;
    }
    value_type pop_min() {
        assert(_dat.size());
        const int idx = min_heap_top_index();
        std::swap(_dat[idx], _dat.back());
        value_type res = std::move(_dat.back());
        _dat.pop_back();
        fix_min_heap_down(idx);
        return res;
    }
private:
    // even : min_heap, odd : max_heap
    std::vector<value_type> _dat;
    Comp _comp;

    int min_heap_top_index() const { return 0; }
    int max_heap_top_index() const { return _dat.size() >= 2; }

    void fix_up(int idx) {
        if (const int l = idx & ~0b1, r = l | 1; r < int(_dat.size())) {
            if (_comp(_dat[r], _dat[l])) std::swap(_dat[l], _dat[r]), idx ^= 1;
            fix_min_heap_up(l), fix_max_heap_up(r);
        } else {
            fix_min_heap_up(l), fix_max_heap_up(l);
        }
    }
    void fix_min_heap_up(int idx) {
        while (idx >= 2) {
            if (int par = min_heap_parent(idx); _comp(_dat[idx], _dat[par])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);
            else return;
        }
    }
    void fix_max_heap_up(int idx) {
        while (idx >= 2) {
            if (int par = max_heap_parent(idx); _comp(_dat[par], _dat[idx])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);
            else return;
        }
    }
    void fix_min_heap_down(int idx) {
        const int siz = _dat.size();
        while (true) {
            int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);
            if (lch >= siz) {
                fix_up(idx);
                break;
            }
            int ch = rch < siz and _comp(_dat[rch], _dat[lch]) ? rch : lch;
            if (_comp(_dat[ch], _dat[idx])) std::swap(_dat[std::exchange(idx, ch)], _dat[ch]);
            else break;
        }
    }
    void fix_max_heap_down(int idx) {
        const int siz = _dat.size();
        while (true) {
            int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);
            lch -= lch >= siz, rch -= rch >= siz;
            if (lch >= siz) {
                fix_up(idx);
                break;
            }
            int ch = rch < siz and _comp(_dat[lch], _dat[rch]) ? rch : lch;
            if (_comp(_dat[idx], _dat[ch])) std::swap(_dat[std::exchange(idx, ch)], _dat[ch]);
            else break;
        }
    }

    static constexpr int min_heap_parent(int idx) { return (idx - 2) >> 2 << 1; }
    static constexpr int max_heap_parent(int idx) { return min_heap_parent(idx) | 1; }
    static constexpr int min_heap_child_l(int idx) { return (idx + 1) << 1; }
    static constexpr int min_heap_child_r(int idx) { return (idx + 2) << 1; }
    static constexpr int max_heap_child_l(int idx) { return min_heap_child_l(idx - 1) | 1; }
    static constexpr int max_heap_child_r(int idx) { return min_heap_child_r(idx - 1) | 1; }
};

int main() {
    int n, q;
    ::scanf("%d %d", &n, &q);

    IntervalHeap<int> pq;
    for (int i = 0, val; i < n; ++i) {
        ::scanf("%d", &val);
        pq.push(val);
    }

    for (int i = 0, query_type, x; i < q; ++i) {
        ::scanf("%d", &query_type);
        if (query_type == 0) {
            ::scanf("%d", &x);
            pq.push(x);
        } else if (query_type == 1) {
            ::printf("%d\n", pq.pop_min());
        } else if (query_type == 2) {
            ::printf("%d\n", pq.pop_max());
        } else {
            assert(false);
        }
    }

    return 0;
}