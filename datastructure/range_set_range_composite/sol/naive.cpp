#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
using i64 = long long;

const i64 MOD = 998244353;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    assert(i64(n) * q <= 10000'0000);

    vector<int> a(n);
    vector<int> b(n);
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        scanf("%d", &b[i]);
    }

    for(int ph=0; ph<q; ph++){
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            int c; scanf("%d", &c);
            int d; scanf("%d", &d);
            for(int i=l; i<r; i++){
                a[i] = c;
                b[i] = d;
            }            
        } else {
            int l; scanf("%d", &l);
            int r; scanf("%d", &r);
            i64 x; scanf("%lld", &x);
            for(int i=l; i<r; i++){
                x *= a[i];
                x += b[i];
                x %= MOD;
            }
            printf("%lld\n", x);
        }
    }
    return 0;
}
