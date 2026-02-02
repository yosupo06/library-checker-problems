#include <iostream>
using namespace std;
const int N = 200010;
using i64 = long long;
const i64 inf = 3e18;
struct Linear {
    i64 k = 0, b = inf;
    inline i64 operator()(int &x) {
        return k * x + b;
    }
} g;
struct Node {
    int l, r, ls, rs;
    Linear f;
    inline int mid(void) {
        return (l + r) >> 1;
    }
    inline bool better(Linear &g) {
        return f(l) >= g(l) && f(r) >= g(r);
    }
    inline bool worse(Linear &g) {
        return f(l) <= g(l) && f(r) <= g(r);
    }
} tr[N * 64];
i64 k, b;
int n, m, l, r, mem, rt, op;
inline void alloc(int &p, int l, int r) {
    p = ++mem, tr[p] = {l, r, 0, 0, Linear()};
}
inline int ls(int p) {
    if (tr[p].ls == 0) {
        alloc(tr[p].ls, tr[p].l, tr[p].mid());
    }
    return tr[p].ls;
}
inline int rs(int p) {
    if (tr[p].rs == 0) {
        alloc(tr[p].rs, tr[p].mid() + 1, tr[p].r);
    }
    return tr[p].rs;
}
void insert(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r) {
        if (tr[p].better(g)) {
            tr[p].f = g;
        } else if (tr[p].l != tr[p].r) {
            if (!tr[ls(p)].worse(g)) insert(ls(p), l, r);
            if (!tr[rs(p)].worse(g)) insert(rs(p), l, r);
        }
    } else {
        if (l <= tr[p].mid()) insert(ls(p), l, r);
        if (r > tr[p].mid()) insert(rs(p), l, r);
    }
}
i64 query(int p, int x) {
    if (p == 0) return inf;
    i64 res = tr[p].f(x);
    if (tr[p].l != tr[p].r) {
        res = min(res, query(x <= tr[p].mid() ? tr[p].ls : tr[p].rs, x));
    }
    return res;
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(void) {
    optimizeIO(), cin >> n >> m;
    alloc(rt, -1000000000, 1000000000);
    for (int i = 1; i <= n; i++) {
        cin >> l >> r >> k >> b;
        g = {k, b}, insert(rt, l, r - 1);
    }
    while (m--) {
        cin >> op >> l;
        if (op == 0) {
            cin >> r >> k >> b;
            g = {k, b}, insert(rt, l, r - 1);
        } else {
            i64 res = query(rt, l);
            if (res != inf) {
                cout << res << '\n';
            } else {
                cout << "INFINITY\n";
            }
        }
    }
    return 0;
}
