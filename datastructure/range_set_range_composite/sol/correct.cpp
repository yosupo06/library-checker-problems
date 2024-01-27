#include <cstdio>
#include <vector>
#include "range_set_range_product.hpp"

using namespace std;
const int MOD = 998244353;
using i64 = long long;

struct Elem {
    int a;
    int b;
};

Elem operator*(Elem x, Elem f){
    int a = i64(f.a) * i64(x.a) % MOD;
    int b = (i64(f.b) + i64(f.a) * i64(x.b)) % MOD;
    return { a, b };
}

int main() {
    int n; scanf("%d", &n);
    int q; scanf("%d", &q);
    nachia::RangeSetRangeProduct<Elem> ds(n, {1,0});
    for(int i=0; i<n; i++){
        int a; scanf("%d", &a);
        int b; scanf("%d", &b);
        ds.assign(i, i+1, {a,b});
    }
    for(int ph=0; ph<q; ph++){
        int t; scanf("%d", &t);
        if(t == 0){
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            int c; scanf("%d", &c);
            int d; scanf("%d", &d);
            if(l != r){ // my code don't support updating on empty ranges
                ds.assign(l, r, {c,d});
            }
        }
        else if(t == 1){
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            int x; scanf("%d", &x);
            if(l == r){ // my code don't support folding empty ranges
                printf("%d\n", x);
            } else {
                Elem e = ds.fold(l, r);
                int ans = (i64(e.a) * i64(x) + i64(e.b)) % MOD;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
