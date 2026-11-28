#include <cstdio>
#include "../params.h"

int main() {
    const int right = R_MAX;
    std::printf("1 %d %d\n", right, right);
    for (int v = 0; v < right; ++v) std::printf("0 %d\n", v);
}
