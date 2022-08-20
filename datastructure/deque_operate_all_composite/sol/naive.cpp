#include <iostream>
#include <deque>
#include <tuple>
#include <utility>

using namespace std;
using ll = long long;

const ll MOD = 998244353;

int main() {
    int q;
    scanf("%d", &q);

    deque<pair<ll, ll> > que;

    for (int i = 0; i < q; i++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            que.emplace_front(a, b);
        }
        if (ty == 1) {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            que.emplace_back(a, b);
        }
        else if (ty == 2) {
            que.pop_front();
        }
        else if (ty == 3) {
            que.pop_back();
        }
        else if (ty == 4) {
            ll x;
            scanf("%lld", &x);
            for (int i = 0; i < (int)que.size(); i++) {
                ll a, b;
                tie(a, b) = que[i];
                x = (a * x + b) % MOD;
            }
            printf("%lld\n", x);
        }
    }
    return 0;
}
