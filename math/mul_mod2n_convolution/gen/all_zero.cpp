#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);

    int n = vector{0, 1, 3, 15}[seed];
    const int N = 1 << n;
    vector<int> a(N), b(N);

    printf("%d\n", n);
    for(int i = 0; i < N; i++) printf("%d%c", a[i], " \n"[i + 1 == N]);
    for(int i = 0; i < N; i++) printf("%d%c", b[i], " \n"[i + 1 == N]);

    return 0;
}
