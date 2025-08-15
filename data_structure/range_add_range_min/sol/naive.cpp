#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;
template<class T> inline bool chmin(T& a, T b) {if(a > b){a = b; return true;} else {return false;}};
const ll INF=(1LL<<60);

int main() {
    ll n, q;
    scanf("%lld%lld", &n, &q);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    while (q--) {
        ll type;scanf("%lld", &type);
        if (type == 0) {
            ll l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            for (int i = l; i < r; i++) {
                a[i] += x;
            }
        } else {
            ll l, r;
            scanf("%lld%lld", &l, &r);
            ll x = INF;
            for (int i = l; i < r; i++) {
                chmin(x, a[i]);
            }
            printf("%lld\n", x);
        }
    }
}
