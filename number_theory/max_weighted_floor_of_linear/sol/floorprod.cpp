#include <cassert>  // assert
#include <limits>   // numeric_limits
#include <utility>  // swap, pair
#include <cstdio>   // scanf, printf
#include <algorithm> // min, max

using ll = long long;

template <typename S, typename T>
T floor_prod(S n, S m, S a, S b, T e, T x, T y) {
    assert(0 <= n && 0 < m && 0 <= a && 0 <= b);
    S c = (a * n + b) / m;
    T pre = e, suf = e;
    for(;;) {
        const S p = a / m;
        a %= m;
        x = x * y.pow(p);
        const S q = b / m;
        b %= m;
        pre = pre * y.pow(q);
        c -= (p * n + q);
        if (c == 0) {
            return pre * x.pow(n) * suf;
        }
        const S d = (m * c - b - 1) / a + 1;
        suf = y * x.pow(n - d) * suf;
        b = m - b - 1 + a;
        std::swap(m, a);
        n = c - 1;
        c = d;
        std::swap(x, y);
    }
}

template <typename S>
struct MwfData {
    S sum, best, dx, arg;
    MwfData(S s) : sum(s), best(std::numeric_limits<S>::min()), dx(0), arg(0) {}
    MwfData(S s, S m, S x, S a) : sum(s), best(m), dx(x), arg(a) {}
    friend MwfData<S> operator*(const MwfData& lhs, const MwfData& rhs) {
        const S S_MIN = std::numeric_limits<S>::min();
        S sum = lhs.sum + rhs.sum;
        S dx = lhs.dx + rhs.dx;
        S cand_l = lhs.best;
        S cand_r = rhs.best == S_MIN ? S_MIN : (lhs.sum + rhs.best);
        if (cand_l > cand_r) {
            return MwfData<S>(sum, cand_l, dx, lhs.arg);
        }
        if (cand_l < cand_r) {
            S arg = lhs.dx + rhs.arg;
            return MwfData<S>(sum, cand_r, dx, arg);
        }
        if (cand_l == S_MIN) {
            return MwfData<S>(sum, S_MIN, dx, 0);
        }
        S arg_l = lhs.arg;
        S arg_r = lhs.dx + rhs.arg;
        S arg = std::min(arg_l, arg_r);
        return MwfData<S>(sum, cand_l, dx, arg);
    }
    MwfData<S> pow(S k) const {
        const S S_MIN = std::numeric_limits<S>::min();
        assert(0 <= k);
        if (k == 0) {
            return MwfData<S>(0);
        }
        S ssum = sum * k;
        S sdx = dx * k;
        if (best == S_MIN) {
            return MwfData<S>(ssum, S_MIN, sdx, 0);
        }
        if (0 < sum) {
            S sbest = (k - 1) * sum + best;
            S sarg = (k - 1) * dx + arg;
            return MwfData<S>(ssum, sbest, sdx, sarg);
        }
        return MwfData<S>(ssum, best, sdx, arg);
    }
};

template <typename S>
std::pair<S, S> argmax_weighted_floor_of_linear(S n, S m, S a, S b, S c, S d) {
    // argmwf(n,m,a,b,c,d) = (
    //   max{ floor((a i + b) / m) + floor((c i + d) / m) | 0 <= i < n },
    //   argmax{ floor((a i + b) / m) + floor((c i + d) / m) | 0 <= i < n }
    // )
    assert(0 < n && 0 < m && std::numeric_limits<S>::min() < 0);
    MwfData<S> res = floor_prod<S, MwfData<S>>(n, m, c, d, MwfData<S>(0), MwfData<S>(a, 0, 1, 0), MwfData<S>(b));
    return {res.best, res.arg};
}

template <typename S>
S max_weighted_floor_of_linear(S n, S m, S a, S b, S c, S d) {
    // mwf(n,m,a,b,c,d) = max{ floor((a i + b) / m) + floor((c i + d) / m) | 0 <= i < n }
    return argmax_weighted_floor_of_linear<S>(n, m, a, b, c, d).first;
}

// f(x) = a*x + b*floor((c*x + d)/m)
template <typename S>
S mwf_f(S x, S m, S a, S b, S c, S d) {
    return a * x + b * ((c * x + d) / m);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int i = 0; i < t; i++) {
        ll n, m, a, b, c, d;
        scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &a, &b, &c, &d);
        assert(0 < n && 0 < m);
        auto [max_val, argmax] = argmax_weighted_floor_of_linear<ll>(n, m, a, b, c, d);
        assert(0 <= argmax && argmax < n);
        assert(mwf_f(argmax, m, a, b, c, d) == max_val);
        assert(argmax == 0 || max_weighted_floor_of_linear<ll>(argmax, m, a, b, c, d) < max_val);
        printf("%lld\n", max_val);
    }
    return 0;
}
