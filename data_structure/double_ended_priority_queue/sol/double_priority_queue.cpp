#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <functional>
#include <utility>

template <typename T, typename Comp = std::less<T>>
struct DoubleEndedPriorityQueue {
    using value_type = T;
    using compare_type = Comp;

    DoubleEndedPriorityQueue() = default;
    DoubleEndedPriorityQueue(const Comp& comp) : _comp(comp) {}

    template <typename InputIterator>
    DoubleEndedPriorityQueue(InputIterator first, InputIterator last) : _max_heap(first, last) {
        std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);
    }
    template <typename InputIterator>
    DoubleEndedPriorityQueue(InputIterator first, InputIterator last, const Comp& comp) : _comp(comp), _max_heap(first, last) {
        std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);
    }

    template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>
    DoubleEndedPriorityQueue(const Iterable& dat) : DoubleEndedPriorityQueue(dat.begin(), dat.end()) {}
    template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>
    DoubleEndedPriorityQueue(const Iterable& dat, Comp& comp) : DoubleEndedPriorityQueue(dat.begin(), dat.end(), comp) {}

    bool empty() const { return size() == 0; }
    int size() const { return _min_heap.size() + _max_heap.size(); }

    void push(const value_type& v) {
        if (_min_heap.empty() or _comp(pivot, v)) {
            _max_heap.push_back(v);
            std::push_heap(_max_heap.begin(), _max_heap.end(), _comp);
        } else {
            _min_heap.push_back(v);
            std::push_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);
        }
    }

    value_type pop_max() {
        ensure_max_heap_nonempty();
        std::pop_heap(_max_heap.begin(), _max_heap.end(), _comp);
        value_type res = std::move(_max_heap.back());
        _max_heap.pop_back();
        return res;
    }
    value_type pop_min() {
        ensure_min_heap_nonempty();
        std::pop_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);
        value_type res = std::move(_min_heap.back());
        _min_heap.pop_back();
        return res;
    }

private:
    compare_type _comp;
    struct {
        compare_type* comp;
        bool operator()(const value_type& x, const value_type& y) { return (*comp)(y, x); }
    } _rev_comp{ &_comp };

    std::vector<value_type> _max_heap, _min_heap;
    value_type pivot;

    void ensure_min_heap_nonempty() {
        const int siz = size();
        assert(siz);
        if (not _min_heap.empty()) return;
        if (siz == 1) {
            std::swap(_min_heap, _max_heap);
            pivot = _min_heap.front();
        } else {
            const int mid = (siz + 1) >> 1;
            std::nth_element(_max_heap.begin(), _max_heap.begin() + mid - 1, _max_heap.end(), _comp);
            pivot = _max_heap[mid - 1];
            _min_heap.reserve(mid);
            std::move(_max_heap.begin(), _max_heap.begin() + mid, std::back_inserter(_min_heap));
            _max_heap.erase(_max_heap.begin(), _max_heap.begin() + mid);
            std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);
            std::make_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);
        }
    }
    void ensure_max_heap_nonempty() {
        const int siz = size();
        assert(siz);
        if (not _max_heap.empty()) return;
        if (siz == 1) {
            std::swap(_min_heap, _max_heap);
        } else {
            const int mid = siz >> 1;
            std::nth_element(_min_heap.begin(), _min_heap.begin() + mid - 1, _min_heap.end(), _comp);
            pivot = _min_heap[mid - 1];
            _max_heap.reserve(siz - mid);
            std::move(_min_heap.begin() + mid, _min_heap.end(), std::back_inserter(_max_heap));
            _min_heap.erase(_min_heap.begin() + mid, _min_heap.end());
            std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);
            std::make_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);
        }
    }
};

int main() {
    int n, q;
    ::scanf("%d %d", &n, &q);

    DoubleEndedPriorityQueue<int> pq;
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