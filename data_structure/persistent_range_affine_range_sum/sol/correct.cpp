#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

#include <utility>

#include <cassert>
namespace nachia{

// ax + by = gcd(a,b)
// return ( x, - )
std::pair<long long, long long> ExtGcd(long long a, long long b){
    long long x = 1, y = 0;
    while(b){
        long long u = a / b;
        std::swap(a-=b*u, b);
        std::swap(x-=y*u, y);
    }
    return std::make_pair(x, a);
}

} // namespace nachia

namespace nachia{

template<unsigned int MOD>
struct StaticModint{
private:
    using u64 = unsigned long long;
    unsigned int x;
public:

    using my_type = StaticModint;
    template< class Elem >
    static Elem safe_mod(Elem x){
        if(x < 0){
            if(0 <= x+MOD) return x + MOD;
            return MOD - ((-(x+MOD)-1) % MOD + 1);
        }
        return x % MOD;
    }

    StaticModint() : x(0){}
    StaticModint(const my_type& a) : x(a.x){}
    StaticModint& operator=(const my_type&) = default;
    template< class Elem >
    StaticModint(Elem v) : x(safe_mod(v)){}
    unsigned int operator*() const noexcept { return x; }
    my_type& operator+=(const my_type& r) noexcept { auto t = x + r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator+(const my_type& r) const noexcept { my_type res = *this; return res += r; }
    my_type& operator-=(const my_type& r) noexcept { auto t = x + MOD - r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator-(const my_type& r) const noexcept { my_type res = *this; return res -= r; }
    my_type operator-() const noexcept { my_type res = *this; res.x = ((res.x == 0) ? 0 : (MOD - res.x)); return res; }
    my_type& operator*=(const my_type& r)noexcept { x = (u64)x * r.x % MOD; return *this; }
    my_type operator*(const my_type& r) const noexcept { my_type res = *this; return res *= r; }
    my_type pow(unsigned long long i) const noexcept {
        my_type a = *this, res = 1;
        while(i){ if(i & 1){ res *= a; } a *= a; i >>= 1; }
        return res;
    }
    my_type inv() const { return my_type(ExtGcd(x, MOD).first); }
    unsigned int val() const noexcept { return x; }
    static constexpr unsigned int mod() { return MOD; }
    static my_type raw(unsigned int val) noexcept { auto res = my_type(); res.x = val; return res; }
    my_type& operator/=(const my_type& r){ return operator*=(r.inv()); }
    my_type operator/(const my_type& r) const { return operator*(r.inv()); }
};

} // namespace nachia

namespace nachia {

template<
    class S,
    class F,
    S op(S l, S r),
    F composition(F f, F x),
    S mapping(F f, S x)
>
struct PersistentLazySegtree {
public:
    struct Node {
        int l;
        int r;
        S a;
        F f;
    };
    struct Agent{
    public:
        Agent(){}
        Agent(int _sz, int _root, PersistentLazySegtree* _q) : sz(_sz), root(_root), q(_q) {}
        int size() const { return sz; }
        Agent set(int at, S x) const { return copy(q->set(root,sz,at,x,q->id)); }
        S prod(int l, int r) const { return q->prod(root,sz,l,r,q->id); }
        Agent apply(int l, int r, F f) const { return copy(q->apply(root,sz,l,r,f,q->id)); }
        Agent crossover(Agent right, int p) const {
            return copy(q->crossover(root, right.root, sz, p, q->id, q->id));
        }
    private:
        int sz;
        int root;
        PersistentLazySegtree* q = nullptr;
        Agent copy(int newRoot) const { return Agent(sz, newRoot, q); }
    };

    PersistentLazySegtree(){}

    PersistentLazySegtree(S _e, F _id, int reserved_size = 0)
        : e(_e), id(_id) { v.reserve(reserved_size); }

    Agent construct(const std::vector<S>& val){
        return { int(val.size()), fromRange(val.begin(), int(val.size())), this };
    }

private:
    int newLeaf(S x){
        int res = v.size();
        v.push_back({ -1, -1, x, id });
        return res;
    }
    int newMid(int l, int r){
        int res = v.size();
        v.push_back({ l, r, op(v[l].a, v[r].a), id });
        return res;
    }
    int applyAtNode(int p, F f){
        if(v[p].l == -1) return newLeaf(mapping(f, v[p].a));
        int res = v.size();
        v.push_back({ v[p].l, v[p].r, mapping(f, v[p].a), composition(f, v[p].f) });
        return res;
    }
    int set(int p, int n, int at, S x, F prop){
        if(n == 1) return newLeaf(x);
        int m = n / 2;
        auto nxf = composition(prop, v[p].f);
        if(at < m) return newMid(set(v[p].l, m, at, x, nxf), applyAtNode(v[p].r, nxf));
        return newMid(applyAtNode(v[p].l, nxf), set(v[p].r, n-m, at-m, x, nxf));
    }
    S prod(int p, int n, int l, int r, F prop){
        if(l <= 0 && n <= r) return mapping(prop, v[p].a);
        if(r <= 0 || n <= l) return e;
        int m = n / 2;
        auto nxf = composition(prop, v[p].f);
        return op(
            prod(v[p].l, m, l, r, nxf),
            prod(v[p].r, n-m, l-m, r-m, nxf)
        );
    }
    int apply(int p, int n, int l, int r, F f, F prop){
        if(l <= 0 && n <= r) return applyAtNode(p, composition(f, prop));
        if(r <= 0 || n <= l) return applyAtNode(p, prop);
        int m = n / 2;
        auto nxf = composition(prop, v[p].f);
        int l2 = apply(v[p].l, m, l, r, f, nxf);
        int r2 = apply(v[p].r, n-m, l-m, r-m, f, nxf);
        return newMid(l2, r2);
    }
    int crossover(int p, int q, int n, int at, F propl, F propr){
        if(at <= 0) return applyAtNode(q, propr);
        if(n <= at) return applyAtNode(p, propl);
        int m = n / 2;
        auto nxfl = composition(propl, v[p].f);
        auto nxfr = composition(propr, v[q].f);
        int l2 = crossover(v[p].l, v[q].l, m, at, nxfl, nxfr);
        int r2 = crossover(v[p].r, v[q].r, n-m, at-m, nxfl, nxfr);
        return newMid(l2, r2);
    }
    int fromRange(typename std::vector<S>::const_iterator a, int n){
        if(n == 1) return newLeaf(a[0]);
        int m = n / 2;
        return newMid(fromRange(a, m), fromRange(a+m, n-m));
    }

    S e;
    F id;
    std::vector<Node> v;
};

} // namespace nachia

template<class T, int sz>
struct ValArrayOverRing {
    using X = ValArrayOverRing;
    std::array<T, sz> m;
    T& operator[](int i){ return m[i]; }
    const T& operator[](int i) const { return m[i]; }
    X& operator+=(const X& r){ for(int i=0; i<sz; i++){ m[i] += r[i]; } return *this; }
    X& operator-=(const X& r){ for(int i=0; i<sz; i++){ m[i] -= r[i]; } return *this; }
    X& operator*=(const X& r){ for(int i=0; i<sz; i++){ m[i] *= r[i]; } return *this; }
    X operator+(const X& r) const { X p = *this; p += r; return p; }
    X operator-(const X& r) const { X p = *this; p -= r; return p; }
    X operator*(const X& r) const { X p = *this; p *= r; return p; }
};

namespace nachia {

template<class Value>
struct Affine{
    using X = ValArrayOverRing<Value, 2>;
    Value a;
    Value b;
    static Affine Id(){ return { Value(1), Value(0) }; }
    Affine operator()(const Affine& x) const { return { a * x.a, a * x.b + b }; }
    X operator()(const X& x) const { return { x[0], a * x[1] + b * x[0] }; }
    Affine operator+(const Affine& r) const { return { a + r.a, b + r.b }; }
    Affine operator-(const Affine& r) const { return { a - r.a, b - r.b }; }
    Affine& operator+=(const Affine& r) const { a += r.a; b += r.b; return *this; }
    Affine& operator-=(const Affine& r) const { a -= r.a; b -= r.b; return *this; }
};

} // namespace nachia


using namespace std;

using Modint = nachia::StaticModint<998244353>;
using Affine = nachia::Affine<Modint>;
using Value = Affine::X;
Value op(Value l, Value r){ return l + r; }
Value mapping(Affine f, Value x){ return f(x); }
Affine composition(Affine f, Affine x){ return f(x); }

vector<int> solve(int N, int Q, const vector<int>& A, const vector<array<int,6>>& queries){
    using Ds = nachia::PersistentLazySegtree<Value, Affine, op, composition, mapping>;
    Ds ds(Value(), Affine::Id());
    vector<Ds::Agent> data(Q+1);
    vector<Value> mA(N);
    for(int i=0; i<N; i++) mA[i] = { 1, A[i] };
    data[0] = ds.construct(mA);
    vector<int> ans;
    for(int qi=1; qi<=Q; qi++){
        auto& q = queries[qi-1];
        if(q[0] == 0){
            auto [dum0, t, l, r, c, d] = q; t++;
            Modint cm = c;
            Modint dm = d;
            data[qi] = data[t].apply(l, r, {cm,dm});
        }
        else if(q[0] == 1){
            auto [dum0, t, s, l, r, dum1] = q; t++; s++;
            data[qi] = data[t].crossover(data[s], l).crossover(data[t], r);
        }
        else if(q[0] == 2){
            auto [dum0, t, l, r, dum1, dum2] = q; t++;
            Modint v = data[t].prod(l, r)[1];
            ans.push_back(int(v.val()));
        }
    }
    return ans;
}


int main(){
    int N, Q; scanf("%d%d", &N, &Q);
    vector<int> A(N);
    for(auto& a : A) scanf("%d", &a);
    vector<array<int, 6>> queries(Q);
    for(auto& q : queries){
        scanf("%d", &q[0]);
        if(q[0] == 0){
            scanf("%d%d%d%d%d", &q[1], &q[2], &q[3], &q[4], &q[5]);
        } else if(q[0] == 1){
            scanf("%d%d%d%d", &q[1], &q[2], &q[3], &q[4]);
            q[5] = 0;
        } else if(q[0] == 2){
            scanf("%d%d%d", &q[1], &q[2], &q[3]);
            q[4] = q[5] = 0;
        } else exit(1);
    }
    auto ans = solve(N, Q, A, queries);
    for(auto a : ans) printf("%d\n", a);
    return 0;
}
