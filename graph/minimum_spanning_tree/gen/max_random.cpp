#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

struct E
{
    int from, to, cost;
};

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MAX - 100, N_MAX);
    int m = gen.uniform(n - 1, (int)N_MAX);

    vector<E> edges;
    for (int i = 1; i < n; i++)
    {
        int c = gen.uniform(0LL, C_MAX);
        edges.push_back({gen.uniform(0, i - 1), i, c});
    }
    for (int i = n - 1; i < m; i++)
    {
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        int c = gen.uniform(0LL, C_MAX);
        edges.push_back({a, b, c});
    }

    auto idx = gen.perm<int>(n);
    printf("%d %d\n", n, m);
    for (auto e : edges)
    {
        printf("%d %d %d\n", idx[e.from], idx[e.to], e.cost);
    }
    return 0;
}