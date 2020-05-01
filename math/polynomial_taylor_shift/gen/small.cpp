#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = seed + 1;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        a[i] = gen.uniform(0ll, MOD - 1);
    }
    int c = gen.uniform(0ll, MOD - 1);

    printf("%d %d\n", n, c);
    for (int i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i != n - 1)
            printf(" ");
    }
    printf("\n");
    return 0;
}
