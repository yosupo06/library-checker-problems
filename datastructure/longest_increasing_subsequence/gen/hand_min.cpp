#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(N_MAX, N_MAX);
    printf("%d\n", N);
    int a = A_MAX;
    for (int i = 0; i < N; i++) {
        printf("%d", a);
        a--;
        if (i != N - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
