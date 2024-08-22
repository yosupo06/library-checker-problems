#include <cstdio>
#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX - seed;
    const int N = 1 << n;
    vector<int> a(N, gen.uniform(0LL, MOD - 1)), b(N);

    for(int i = 0; i < n - 1; i++){
        int sum = 0;
        for(int j = 1; j < N >> i; j += 2){
            const int x = gen.uniform(0LL, MOD - 1);
            b[j << i] = x;
            sum -= x;
            if(sum < 0) sum += MOD;
        }
        b[1 << i] += sum;
        if(b[1 << i] >= MOD) b[1 << i] -= MOD;
    }

    printf("%d\n", n);
    for(int i = 0; i < N; i++) printf("%d%c", a[i], " \n"[i + 1 == N]);
    for(int i = 0; i < N; i++) printf("%d%c", b[i], " \n"[i + 1 == N]);

    return 0;
}
