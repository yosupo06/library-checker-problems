#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll N = seed % 5 + 1;

    long long SQ = sqrtl(N);
    while (SQ * SQ + SQ <= N)
        SQ++;
    long long sz = N / SQ + SQ - 1;
    printf("1\n%lld\n", N);
    for (int i = 0; i < sz; i++)
    {
        int x = gen.uniform<int>(0, MOD - 1);
        if (i == sz - 1)
            printf("%d\n", x);
        else
            printf("%d ", x);
    }
    for (int i = 0; i < sz; i++)
    {
        int x = gen.uniform<int>(0, MOD - 1);
        if (i == sz - 1)
            printf("%d\n", x);
        else
            printf("%d ", x);
    }
    return 0;
}