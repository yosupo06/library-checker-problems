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
    V<int> low, ord, st;
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
            V<int> gr;
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

struct E {
    int to;
};

int main() {

    int n, m;
    cin >> n >> m;
    VV<E> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b});
    }

    auto scc = get_scc(g);


    cout << scc.groups.size() << endl;
    for (auto v: scc.groups) {
        int l = int(v.size());
        cout << l;
        for (auto d: v) cout << " " << d;
        printf("\n");
    }
    return 0;
}
