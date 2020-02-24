#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using uint = unsigned int;
using ll = long long;

struct P {
    ll x, y;
    bool operator<(P r) const {
        return atan2(y, x) < atan2(r.y, r.x);
    }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<P> ps(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &ps[i].x, &ps[i].y);
    }
    sort(ps.begin(), ps.end());
    for (auto p : ps) {
        printf("%lld %lld\n", p.x, p.y);
    }
    return 0;
}
