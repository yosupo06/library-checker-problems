#include <iostream>
#include <tuple>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++)
    {
        int a = gen.uniform<int>(-A_MAX, A_MAX);
        printf("%d", a);
        if (i != n - 1)
            printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++)
    {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        int l, r;
        l = gen.uniform(0, 10);
        r = gen.uniform(n - 10, n);
        if (t == 0)
        {
            if (gen.uniform01() <= .01)
                tie(l, r) = gen.uniform_pair(0, n);
            int b = gen.uniform<int>(-B_MAX, B_MAX);
            int c = gen.uniform<int>(-C_MAX, C_MAX);
            printf("%d %d %d %d\n", l, r, b, c);
        }
        else
        {
            if (gen.uniform01() <= .01)
                tie(l, r) = gen.uniform_pair(0, n);
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
