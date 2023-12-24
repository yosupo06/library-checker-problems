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

    int n = N_MAX;
    int m = n - 1;

    vector<E> edges;
    for (int i = 1; i < n; i++)
    {
        int c = gen.uniform(0LL, C_MAX);
        edges.push_back({0, i, c});
    }

    vector<int> idx = gen.perm<int>(n);
    printf("%d %d\n", n, m);
    for (auto e : edges)
    {
        printf("%d %d %d\n", idx[e.from], idx[e.to], e.cost);
    }
    return 0;
}