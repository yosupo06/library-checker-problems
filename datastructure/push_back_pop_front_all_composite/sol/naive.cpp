#include <iostream>
#include <deque>
#include <tuple>
#include <utility>

using namespace std;
using ll = long long;

const ll MOD = 998244353;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    constexpr char endl = '\n';

    int q;
    cin >> q;

    deque<pair<ll, ll> > que;

    for (int i = 0; i < q; i++) {
        int ty;
        cin >> ty;
        if (ty == 0) {
            ll a, b;
            cin >> a >> b;
            que.emplace_back(a, b);
        } else if (ty == 1) {
            que.pop_front();
        } else {
            ll x;
            cin >> x;
            for (int i = (int)que.size() - 1; i >= 0; i--) {
                ll a, b;
                tie(a, b) = que[i];
                x = (a * x + b) % MOD;
            }
            cout << x << endl;
        }
    }
    return 0;
}
