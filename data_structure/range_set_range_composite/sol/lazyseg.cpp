#include <cstdio>
#include <vector>

namespace nachia{

template<
    class S,
    class F,
    S op(S l, S r),
    F composition(F f, F x),
    S mapping(F f, S x)
>
struct LazySegtree {
private:

    struct Node { S s; F f; bool propagated; };
    int N;
    int logN;
    int xN;
    std::vector<Node> A;

    void mapf(Node& a, F f){
        a.propagated = false;
        a.f = composition(f, a.f);
        a.s = mapping(f, a.s);
    }
    void mergev(int i){
        if(i<N) A[i].s = op(A[i*2].s, A[i*2+1].s);
    }
    void spread(int i){
        if(A[i].propagated || !(i < N)) return;
        mapf(A[i*2], A[i].f);
        mapf(A[i*2+1], A[i].f);
        A[i].f = A[0].f;
        A[i].propagated = true;
    }
public:

    LazySegtree() : N(0), logN(-1), xN(0){}
    LazySegtree(int n, S e, F id){
        N=1; logN=0; xN=n;
        while(N<n){ N *= 2; logN++; }
        A.assign(N*2, { e, id, true });
    }
    LazySegtree(const std::vector<S>& a, S e, F id)
        : LazySegtree(a.size(), std::move(e), std::move(id)){
        for(std::size_t i=0; i<a.size(); i++) A[i+N].s = a[i];
        for(int i=N-1; i>=1; i--) mergev(i);
    }
    void apply(int l, int r, F f){
        if(!(l < r)) return;
        if(l == 0 && r == N){ mapf(A[1], f); return; }
        l += N; r += N;
        for(int d=logN; d; d--){
            if((l >> d) << d != l) spread(l >> d);
            if((r >> d) << d != r) spread(r >> d);
        }
        int lp = l, rp = r;
        while(l < r){
            if(l&1){ mapf(A[l++], f); } l /= 2;
            if(r&1){ mapf(A[--r], f); } r /= 2;
        }
        for(int d=1 ; d<=logN; d++){
            if((lp >> d) << d != lp) mergev(lp >> d);
            if((rp >> d) << d != rp) mergev(rp >> d);
        }
    }
    S prod(int l, int r){
        if(!(l < r)) return A[0].s;
        l += N; r += N;
        for(int d=logN; d; d--){
            if((l >> d) << d != l) spread(l >> d);
            if((r >> d) << d != r) spread(r >> d);
        }
        S q1 = A[0].s, q2 = A[0].s;
        while(l < r){
            if(l&1){ q1 = op(q1, A[l++].s); } l /= 2;
            if(r&1){ q2 = op(A[--r].s, q2); } r /= 2;
        }
        return op(q1, q2);
    }
};

} // namespace nachia;


using namespace std;
const int MOD = 998244353;
using i64 = long long;

struct Elem {
    int a;
    int b;
    int len;
};

Elem lst_op(Elem x, Elem f){
    int a = i64(f.a) * i64(x.a) % MOD;
    int b = (i64(f.b) + i64(f.a) * i64(x.b)) % MOD;
    return { a, b, x.len + f.len };
}

struct Updater {
    int a; // a = -1 for null
    int b;
};

Updater lst_composition(Updater f, Updater x){
    if(f.a == -1) return x;
    return f;
}

Elem lst_mapping(Updater f, Elem x){
    if(f.a == -1) return x;
    if(x.len == 0) return x;
    int a = f.a;
    int b = f.b;
    for(int q=1; q!=x.len; q*=2){
        b = (i64(b) + i64(a) * i64(b)) % MOD;
        a = i64(a) * i64(a) % MOD;
    }
    x.a = a;
    x.b = b;
    return x;
}

int main() {
    int n; scanf("%d", &n);
    int q; scanf("%d", &q);
    vector<Elem> init(n);
    for(int i=0; i<n; i++){
        scanf("%d", &init[i].a);
        scanf("%d", &init[i].b);
        init[i].len = 1;
    }
    nachia::LazySegtree<Elem, Updater, lst_op, lst_composition, lst_mapping> ds(init, {1,0,0}, {-1,0});
    for(int ph=0; ph<q; ph++){
        int t; scanf("%d", &t);
        if(t == 0){
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            int c; scanf("%d", &c);
            int d; scanf("%d", &d);
            ds.apply(l, r, {c,d});
        }
        else if(t == 1){
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            int x; scanf("%d", &x);
            Elem e = ds.prod(l, r);
            int ans = (i64(e.a) * i64(x) + i64(e.b)) % MOD;
            printf("%d\n", ans);
        }
    }
    return 0;
}
