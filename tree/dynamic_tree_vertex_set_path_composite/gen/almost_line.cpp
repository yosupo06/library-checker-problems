#include "../params.h"
#include "random.h"

namespace {

struct Node {
    int val;
    int rev;
    int size;
    int l, r;
} node[N_AND_Q_MAX];

void maintain(int x) {
    node[x].size = node[node[x].l].size + 1 + node[node[x].r].size;
}

void pushdown(int x) {
    if (node[x].rev) {
        std::swap(node[x].l, node[x].r);
        node[node[x].l].rev ^= 1;
        node[node[x].r].rev ^= 1;
        node[x].rev = 0;
    }
}

void reverse(int x) {
    if (x == 0) return;
    node[x].rev ^= 1;
}

void zig(int& x) {
    int l = node[x].l;
    node[x].l = node[l].r;
    maintain(x);
    node[l].r = x;
    x = l;
}

void zag(int& x) {
    int r = node[x].r;
    node[x].r = node[r].l;
    maintain(x);
    node[r].l = x;
    x = r;
}

void splay(int& x, int k) {
    pushdown(x);
    if (int &l = node[x].l, &r = node[x].r, size = node[l].size; k == size) {
        return;
    } else if (k < size) {
        pushdown(l);
        if (int &ll = node[l].l, &lr = node[l].r, size = node[ll].size;
            k == size) {
            zig(x);
        } else if (k < size) {
            splay(ll, k);
            zig(x);
            zig(x);
        } else {
            splay(lr, k - size - 1);
            zag(l);
            zig(x);
        }
    } else {
        pushdown(r);
        k -= size + 1;
        if (int &rl = node[r].l, &rr = node[r].r, size = node[rl].size;
            k == size) {
            zag(x);
        } else if (k < size) {
            splay(rl, k);
            zig(r);
            zag(x);
        } else {
            splay(rr, k - size - 1);
            zag(x);
            zag(x);
        }
    }
}

}  // namespace

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int m;
    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a_i = gen.uniform(1ll, MOD - 1);
        int b_i = gen.uniform(0ll, MOD - 1);
        printf("%d %d\n", a_i, b_i);
    }

    auto perm = gen.perm<int>(n);
    node[m = 1] = {perm[0], 0, 1, 0, 0};
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        u = perm[i + 1];
        if (gen.uniform(0, 15) == 0) {
            v = perm[gen.uniform(0, i)];
        } else {
            v = node[m].val;
            ++m, node[m] = {u, 0, m, m - 1, 0};
        }
        if (gen.uniform_bool()) swap(u, v);
        printf("%d %d\n", u, v);
    }

    int rt = m;
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        printf("%d ", t);
        if (t == 0) {
            int k = gen.uniform(0, m - 2);
            splay(rt, k);
            splay(node[rt].r, 0);
            int u = node[rt].val;
            int v = node[node[rt].r].val;
            int t = gen.uniform(1, 3);
            if (t & 1) {
                int t = node[rt].r;
                node[rt].r = 0;
                reverse(rt);
                splay(rt, k);
                node[rt].r = t;
            }
            if (t & 2) {
                reverse(node[rt].r);
                splay(node[rt].r, 0);
            }
            int w = node[rt].val;
            int x = node[node[rt].r].val;
            printf("%d %d %d %d\n", u, v, w, x);
        } else if (t == 1) {
            int p = gen.uniform(0, n - 1);
            int c = gen.uniform(1ll, MOD - 1);
            int d = gen.uniform(0ll, MOD - 1);
            printf("%d %d %d\n", p, c, d);
        } else {
            auto u = gen.uniform(0, n - 1);
            auto v = gen.uniform(0, n - 1);
            int x = gen.uniform(0ll, MOD - 1);
            printf("%d %d %d\n", u, v, x);
        }
    }
    return 0;
}
