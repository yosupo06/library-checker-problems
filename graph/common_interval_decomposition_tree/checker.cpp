#include "testlib.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;

struct result
{
    int root;
    vector<vector<int>> g;
    vector<pair<int, int>> interval;
    vector<string> s;
};
result read_solution(int N, InStream &stream)
{
    int M = stream.readInt();
    int root = -1;
    vector<vector<int>> g(M);
    vector<pair<int, int>> interval(M);
    vector<string> s(M);
    for (int i = 0; i < M; i++)
    {
        auto p = stream.readInt(-1, M - 1);
        interval[i].first = stream.readInt(0, N - 1);
        interval[i].second = stream.readInt(0, N - 1);
        s[i] = stream.readWord();
        if (p == -1)
        {
            root = i;
        }
        else
        {
            g[p].emplace_back(i);
        }
    }
    {
        auto interval2 = interval;
        sort(interval2.begin(), interval2.end());
        interval2.erase(unique(interval2.begin(), interval2.end()), interval2.end());
        if ((int)interval2.size() != M)
        {
            stream.quitf(_wa, "There are two vertices with the same interval.");
        }
    }
    if (root == -1)
    {
        stream.quitf(_wa, "Root is not exist.");
    }
    if (interval[root] != make_pair(0, N - 1))
    {
        stream.quitf(_wa, "Root is not [0,N-1].");
    }
    return result{root, g, interval, s};
}

bool compare(result s, result t)
{
    auto dfs = [&](auto dfs, int now_s, int now_t) -> void
    {
        if (s.g[now_s].size() != t.g[now_t].size())
        {
            quitf(_wa, "not matched.");
        }
        if (s.interval[now_s] != t.interval[now_t])
        {
            quitf(_wa, "not matched.");
        }
        sort(s.g[now_s].begin(), s.g[now_s].end(), [&](auto i, int j)
             { return s.interval[i] < s.interval[j]; });
        sort(t.g[now_t].begin(), t.g[now_t].end(), [&](auto i, int j)
             { return t.interval[i] < t.interval[j]; });
        for (int i = 0; i < (int)s.g[now_s].size(); ++i)
        {
            dfs(dfs, s.g[now_s][i], t.g[now_t][i]);
        }
    };
    dfs(dfs, s.root, t.root);
    quitf(_ok, "OK");
}
int main(int argc, char *argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        P[i] = inf.readInt();
    }
    compare(read_solution(N, ans), read_solution(N, ouf));
}
