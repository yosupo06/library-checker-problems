#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;

struct P {
    ll x, y;
    int pos() const {
        if (y < 0) return -1;
        if (y == 0 && 0 <= x) return 0;
        return 1;
    }
    bool operator<(P r) const {
        if (pos() != r.pos()) return pos() < r.pos();
        return 0 < (x * r.y - y * r.x);
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
    for (auto p: ps) {
        printf("%lld %lld\n", p.x, p.y);
    }
    return 0;
}
