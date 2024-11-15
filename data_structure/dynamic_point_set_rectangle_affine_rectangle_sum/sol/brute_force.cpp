#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include "modint.hpp"
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;

signed main() 
{
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    u32 n, q;
    // cin >> n >> q;
    scanf("%u %u", &n, &q);
    using mint = atcoder::modint998244353;
    using Point = pair<pair<u32, u32>, mint>;

    vec<Point> t(n);
    for (auto &[p, w]: t) {
        // cin >> p.first >> p.second >> n;
        scanf("%u %u %u", &p.first, &p.second, &n);
        w = n;
    }
    u32 op, a, b, c, d, e, f;
    while (q--) {
        // cin >> op;
        scanf("%u", &op);
        if (op == 0) {
            // cin >> a >> b >> c;
            scanf("%u %u %u", &a, &b, &c);
            t.emplace_back(make_pair(a, b), c);
        }
        else if (op == 1) {
            // cin >> a >> b;
            scanf("%u %u", &a, &b);
            t[a].second = b;
        }
        else if (op == 2) {
            // cin >> a >> b >> c >> d;
            scanf("%u %u %u %u", &a, &b, &c, &d);
            mint res = 0;
            for (auto [p, w]: t) {
                auto [x, y] = p;
                if (a <= x && x < c && b <= y && y < d) {
                    res += w;
                }
            }
            // cout << res.val() << '\n';
            printf("%u\n", res.val());
        }
        else {
            // cin >> a >> b >> c >> d >> e >> f;
            scanf("%u %u %u %u %u %u", &a, &b, &c, &d, &e, &f);
            for (auto &[p, w]: t) {
                auto [x, y] = p;
                if (a <= x && x < c && b <= y && y < d) {
                    w = e * w + f;
                }
            }
        }
    }
    return 0;
}