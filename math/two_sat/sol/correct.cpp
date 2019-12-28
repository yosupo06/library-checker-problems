#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct SCC
{
    V<int> id;
    VV<int> groups;
};

template <class E>
struct SCCExec : SCC
{
    int n;
    const VV<E> &g;
    int tm = 0;
    V<bool> flag;
    V<int> low, ord, st, gr;
    void dfs(int v)
    {
        low[v] = ord[v] = tm++;
        st.push_back(v);
        flag[v] = true;
        for (auto e : g[v])
        {
            if (ord[e.to] == -1)
            {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            }
            else if (flag[e.to])
            {
                low[v] = min(low[v], ord[e.to]);
            }
        }
        if (low[v] == ord[v])
        {
            gr.clear();
            while (true)
            {
                int u = st.back();
                st.pop_back();
                gr.push_back(u);
                if (u == v)
                    break;
            }
            for (int x : gr)
                flag[x] = false;
            groups.push_back(gr);
        }
    }
    SCCExec(const VV<E> &_g)
        : n(int(_g.size())), g(_g), flag(n), low(n), ord(n, -1)
    {
        id = V<int>(n);
        for (int i = 0; i < n; i++)
        {
            if (ord[i] == -1)
                dfs(i);
        }
        reverse(groups.begin(), groups.end());
        for (int i = 0; i < int(groups.size()); i++)
        {
            for (int x : groups[i])
            {
                id[x] = i;
            }
        }
    }
};

template <class E>
SCC get_scc(const VV<E> &g) { return SCCExec<E>(g); }

struct TwoSat {
    V<bool> res;

    struct Edge {
        int to;
    };
    VV<Edge> g;

    //(a == a_exp) || (b == b_exp)
    void add_cond(int a, bool a_exp, int b, bool b_exp) {
        g[2 * a + (a_exp ? 0 : 1)].push_back(Edge{2 * b + (b_exp ? 1 : 0)});
        g[2 * b + (b_exp ? 0 : 1)].push_back(Edge{2 * a + (a_exp ? 1 : 0)});
    }
    bool exec() {
        int n = int(res.size());
        auto s = get_scc(g);
        for (int i = 0; i < n; i++) {
            if (s.id[2 * i] == s.id[2 * i + 1]) return false;
            res[i] = s.id[2 * i] < s.id[2 * i + 1];
        }
        return true;
    }
    TwoSat() {}
    TwoSat(int n) {
        g = VV<Edge>(2 * n);
        res = V<bool>(n);
    }
};

int main() {
    {
        char* dummy = nullptr;
        scanf("%ms", &dummy);
        free(dummy);
    }
    {
        char* dummy = nullptr;
        scanf("%ms", &dummy);
        free(dummy);
    }

    int n, m;
    scanf("%d %d", &n, &m);

    TwoSat sat(n);
    for (int i = 0; i < m; i++) {
        int a, b, zero;
        scanf("%d %d %d", &a, &b, &zero);

        bool a_pos = a > 0, b_pos = b > 0;
        a = abs(a) - 1;
        b = abs(b) - 1;

        sat.add_cond(a, a_pos, b, b_pos);        
    }

    if (sat.exec()) {
        cout << "s SATISFIABLE" << endl;
        cout << "v";
        for (int i = 0; i < n; i++) {
            cout << " " << (sat.res[i] ? i + 1 : - (i + 1));
        }
        cout << " 0" << endl;
    } else {
        cout << "s UNSATISFIABLE" << endl;
    }
    return 0;
}
