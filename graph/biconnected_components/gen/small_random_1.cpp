#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(2, 100);
    int m = gen.uniform<int>(M_MIN, 200);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int a = gen.uniform<int>(0, n - 1);
        int b = gen.uniform<int>(0, n - 2);
        if(a <= b) b++;
        printf("%d %d\n", a, b);
    }
    return 0;
}
