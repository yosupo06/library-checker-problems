#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

template<class C>
struct MaxFlow {
    C flow;
    V<char> dual;  // false: S-side true: T-side
};

template<class C, class E>
struct MFExec {
    static constexpr C INF = numeric_limits<C>::max();
    C eps;
    VV<E>& g;
    int s, t;
    V<int> level, iter;

    C dfs(int v, C f) {
        if (v == t) return f;
        C res = 0;
        for (int& i = iter[v]; i < int(g[v].size()); i++) {
            E& e = g[v][i];
            if (e.cap <= eps || level[v] >= level[e.to]) continue;
            C d = dfs(e.to, min(f, e.cap));
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            res += d;
            f -= d;
            if (f == 0) break;
        }
        return res;
    }

    MaxFlow<C> info;
    MFExec(VV<E>& _g, int _s, int _t, C _eps)
        : eps(_eps), g(_g), s(_s), t(_t) {
        int N = int(g.size());

        C& flow = (info.flow = 0);
        while (true) {
            queue<int> que;
            level = V<int>(N, -1);
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int v = que.front(); que.pop();
                for (E e: g[v]) {
                    if (e.cap <= eps || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
            if (level[t] == -1) break;
            iter = V<int>(N, 0);
            while (true) {
                C f = dfs(s, INF);
                if (!f) break;
                flow += f;
            }
        }
        for (int i = 0; i < N; i++) info.dual.push_back(level[i] == -1);
    }
};

template<class C, class E>
MaxFlow<C> get_mf(VV<E>& g, int s, int t, C eps) {
    return MFExec<C, E>(g, s, t, eps).info;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);
    int L, R, M;
    cin >> L >> R >> M;

    struct E {
        int to, rev, cap;
    };
    VV<E> g(2 + L + R);
    int sv = L + R, tv = sv + 1;
    auto add_edge = [&](int from, int to, int cap) {
        g[from].push_back(E{to, int(g[to].size()), cap});
        g[to].push_back(E{from, int(g[from].size())-1, 0});
    };

    for (int i = 0; i < L; i++) {
        add_edge(sv, i, 1);
    }
    for (int i = 0; i < R; i++) {
        add_edge(L + i, tv, 1);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, L + b, 1);
    }

    auto mf = get_mf(g, sv, tv, 0);

    cout << mf.flow << endl;
    for (int i = 0; i < L; i++) {
        for (auto e: g[i]) {
            if (!(L <= e.to && e.to < L + R)) continue;
            if (e.cap) continue;
            cout << i << " " << e.to - L << endl;
        }
    }
    return 0;
}
