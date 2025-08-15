#include <cstdio>
#include <vector>
#include <cassert>

namespace datastructure {

namespace internal {

static inline int ceil_pow2(int n) {
    assert(n >= 0);
#if defined(__GNUG__) || defined(__clang__)
    if (n <= 1) return 0;
    // 32 - clz(n-1) for unsigned
    return 32 - __builtin_clz(static_cast<unsigned>(n - 1));
#else
    int x = 0;
    unsigned v = static_cast<unsigned>(n - (n > 0));
    while ((1u << x) < v + 1) ++x;
    return x;
#endif
}

} // namespace internal

// ACL-compatible signature (function-pointer non-type template parameters).
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
public:
    lazy_segtree() : _n(0), size_(1), log_(0) {
        d.assign(2, e());
        lz.assign(1, id());
    }

    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}

    explicit lazy_segtree(const std::vector<S>& v) {
        _n = static_cast<int>(v.size());
        log_ = internal::ceil_pow2(_n);
        size_ = 1 << log_;
        d.assign(2 * size_, e());
        lz.assign(size_, id());
        for (int i = 0; i < _n; i++) d[size_ + i] = v[i];
        for (int i = size_ - 1; i >= 1; i--) update(i);
    }

    int size() const { return _n; }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log_; ++i) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
        l += size_;
        r += size_;

        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size_;
        for (int i = log_; i >= 1; --i) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log_; ++i) update(p >> i);
    }

    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        l += size_;
        r += size_;

        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1; r >>= 1;
        }

        for (int i = 1; i <= log_; ++i) {
            if (((l2 >> i) << i) != l2) update(l2 >> i);
            if (((r2 >> i) << i) != r2) update((r2 - 1) >> i);
        }
    }

private:
    int _n = 0;
    int size_ = 1;
    int log_ = 0;
    std::vector<S> d;
    std::vector<F> lz;

    inline void update(int k) {
        int l = k << 1;
        d[k] = op(d[l], d[l | 1]);
    }

    inline void all_apply(int k, const F& f) {
        d[k] = mapping(f, d[k]);
        if (k < size_) lz[k] = composition(f, lz[k]);
    }

    inline void push(int k) {
        const F& f = lz[k];
        if (!(f == id())) {
            all_apply(k << 1, f);
            all_apply(k << 1 | 1, f);
            lz[k] = id();
        }
    }
};

} // namespace datastructure

using namespace datastructure;
using namespace std;
using ll = long long;

using S = ll;
using F = ll;
const S INF = (1LL << 60);
S op(S a, S b) {
    return min(a, b);
}
S e() {
    return INF;
}
S mapping(F f, S x) {
    return x + f;
}
F composition(F f, F g) {
    return f + g;
}
F id() {
    return 0;
}

int main() {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);
        seg.set(i, x);
    }
    while (q--) {
        ll type;scanf("%lld", &type);
        if (type == 0) {
            ll l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            seg.apply(l, r, x);
        } else {
            ll l, r;scanf("%lld%lld", &l, &r);
            printf("%lld\n", seg.prod(l, r));
        }
    }
    return 0;
}
