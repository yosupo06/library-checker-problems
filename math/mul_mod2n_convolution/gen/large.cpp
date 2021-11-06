#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 18 + seed / 2;
    const int N = 1 << n;
    vector<int> a(N), b(N);

    for(int& i : a) i = gen.uniform(0LL, MOD - 1);
    for(int& i : b) i = gen.uniform(0LL, MOD - 1);

    printf("%d\n", n);
    for(int i = 0; i < N; i++) printf("%d%c", a[i], " \n"[i + 1 == N]);
    for(int i = 0; i < N; i++) printf("%d%c", b[i], " \n"[i + 1 == N]);

    return 0;
}
