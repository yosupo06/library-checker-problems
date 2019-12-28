#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct E {
    int from, to;
    ll dist;
};

struct PairingHeapAllAdd {
    struct Node;
    using NP = shared_ptr<Node>;
    struct Node {
        E e;
        ll offset = 0;
        NP head = nullptr, next = nullptr;
        Node(E _e) : e(_e) {}
    };
    NP n = nullptr;
    size_t length = 0;
    PairingHeapAllAdd() {}
    PairingHeapAllAdd(V<E> e) {
        length = e.size();
        for (auto d : e) {
            n = merge(n, NP(new Node(d)));
        }
    }

    NP merge(NP x, NP y) {
        if (!x) return y;
        if (!y) return x;
        if (x->e.dist + x->offset > y->e.dist + y->offset) swap(x, y);
        y->offset -= x->offset;
        y->next = x->head;
        x->head = y;
        return x;
    }
    E front() { return n->e; }
    void removeFront() {
        assert(n);
        assert(length > 0);
        length--;
        NP x;
        NP s = n->head;
        while (s) {
            NP a, b;
            a = s;
            s = s->next;
            a->next = nullptr;
            a->offset += n->offset;
            if (s) {
                b = s;
                s = s->next;
                b->next = nullptr;
                b->offset += n->offset;
            }
            a = merge(a, b);
            assert(a);
            if (!x)
                x = a;
            else {
                a->next = x->next;
                x->next = a;
            }
        }
        n = nullptr;
        while (x) {
            NP a = x;
            x = x->next;
            n = merge(a, n);
        }
    }
    void meld(PairingHeapAllAdd& r) {
        length += r.length;
        n = merge(n, r.n);
        r.n = nullptr;
    }
    ll& offset() { return n->offset; }
};

/**
Information of directed mst
*/
struct DirectedMSTInfo {
    ll cost;   /// mst cost
    V<E> res;  /// edge list
    DirectedMSTInfo(size_t n) {
        cost = 0;
        res = V<E>(n);
    }
};

/// calc directed mst
DirectedMSTInfo directedMST(VV<E> g, int r) {
    int n = int(g.size());
    VV<E> rg(n);
    for (int i = 0; i < n; i++) {
        for (auto e : g[i]) {
            rg[e.to].push_back(e);
        }
    }
    V<PairingHeapAllAdd> heap;
    for (int i = 0; i < n; i++) {
        heap.emplace_back(rg[i]);
    }
    heap.resize(2 * n);

    // union find
    V<int> tr(2 * n, -1);
    V<int> uf(2 * n, -1);
    auto root = [&](int i) {
        V<int> st;
        while (uf[i] != -1) {
            st.push_back(i);
            i = uf[i];
        }
        for (int j : st) {
            uf[j] = i;
        }
        return i;
    };

    V<int> used(2 * n);
    V<E> res(2 * n);
    int c = 1, pc = int(n);
    used[r] = 1;
    auto mark = [&](int p) {
        c++;
        while (used[p] == 0 || used[p] == c) {
            if (used[p] == c) {
                // compress
                int np = pc++;
                int q = p;
                do {
                    heap[q].offset() -= res[q].dist + heap[q].offset();
                    heap[np].meld(heap[q]);
                    tr[q] = uf[q] = np;
                    q = root(res[q].from);
                } while (q != np);
                p = np;
            }
            assert(used[p] == 0);
            used[p] = c;

            assert(root(p) == p);
            while (heap[p].length && root(heap[p].front().from) == p) {
                heap[p].removeFront();
            }
            assert(heap[p].length);
            E mi = heap[p].front();
            res[p] = mi;
            p = root(mi.from);
        }
    };
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        mark(i);
    }

    auto info = DirectedMSTInfo(n);
    V<bool> vis(pc);
    for (int i = pc - 1; i >= 0; i--) {
        if (i == r) continue;
        if (vis[i]) continue;
        int f = res[i].to;
        while (f != -1 && !vis[f]) {
            vis[f] = true;
            f = tr[f];
        }
        info.cost += res[i].dist;
        info.res[res[i].to] = res[i];
    }
    return info;
}

int main() {

    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    VV<E> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        g[a].push_back({a, b, c});
    }

    auto res = directedMST(g, s);

    printf("%lld\n", res.cost);
    for (int i = 0; i < n; i++) {
        printf("%d", (i == s ? s : res.res[i].from));
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
