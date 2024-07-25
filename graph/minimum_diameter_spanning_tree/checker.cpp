#include "testlib.h"
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;

struct Edge
{
    u32 a, b, c;
};

u64 read_ans(u32 n, u32 m, const vec<Edge> edges, InStream &stream)
{
    u64 answer = stream.readUnsignedLong();
    vec<vec<pair<u32, u32>>> g(n);
    for (u32 i = 0; i < n - 1; i++)
    {
        u32 ei = stream.readInt(0, m - 1);
        auto [u, v, w] = edges[ei];
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    u64 mdep = 0;
    u32 p = 0;
    u32 cnt = 0;
    auto dfs = [&](auto &&f, u32 x, u32 fa, u64 dep) -> void
    {
        cnt++;
        for (auto [v, w]: g[x]) if (v != fa) {
            f(f, v, x, dep + w);
        }
        if (dep > mdep) mdep = dep, p = x;
    };
    dfs(dfs, 0, 0, 0);
    quitif(cnt != n, _wa, "The output scheme is not a tree.");
    mdep = 0;
    dfs(dfs, p, p, 0);
    quitif(mdep != answer, _wa, "X (which is equal to " U64 ") is not equal to the diameter of the output scheme (which is equal to " U64 ").", answer, mdep);
    return answer;
}

int main(int argc, char *argv[])
{
    setName("compare mdst");
    registerTestlibCmd(argc, argv);

    // input
    u32 n = inf.readInt();
    u32 m = inf.readInt();
    vector<Edge> edges(m);
    for (u32 i = 0; i < m; i++)
    {
        u32 a = inf.readInt();
        u32 b = inf.readInt();
        u32 c = inf.readInt();
        edges[i] = {a, b, c};
    }

    u64 x_ans = read_ans(n, m, edges, ans);
    u64 x_ouf = read_ans(n, m, edges, ouf);

    if (x_ans < x_ouf)
    {
        quitf(_wa, "There is a better solution");
    }
    if (x_ans > x_ouf)
    {
        quitf(_fail, "Participant finds better answer");
    }
    quitf(_ok, "OK: " U64, x_ouf);
}
