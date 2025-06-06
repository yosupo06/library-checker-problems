#include "random.h"
#include <iostream>

using namespace std;

// 1 -> 2, 2 -> 3, ..., n-1 -> n, n -> -n.
// Leads to quadratic runtime when attempting to set variables to true in ascending order.
// Also generates symmetrical testcases that flip each variable or the order.
int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);

    int n = 500'000;
    auto flip = [&] (int i) {
        if (seed & 1) i *= -1;
        // Map n <-> 1, n - 1 <-> 2, ..., -n <-> -1, -(n - 1) <-> -2, ...
        if (seed & 2) i = (i > 0 ? 1 : -1) * (n + 1) - i;
        return i;
    };
    printf("p cnf %d %d\n", n, n);
    for (int i = 1; i <= n; i++)
        printf("%d %d 0\n", flip(-i), flip(i == n ? -n : i + 1));
    return 0;
}
