#include <cstdio>

int main() {
    int left, right;
    std::scanf("%d%d", &left, &right);
    // Taking the larger side always gives an independent set, but may miss the optimum.
    const int first = left >= right ? 0 : left;
    const int size = left >= right ? left : right;
    std::printf("%d\n", size);
    for (int i = 0; i < size; ++i) std::printf("%s%d", i == 0 ? "" : " ", first + i);
    std::puts("");
}
