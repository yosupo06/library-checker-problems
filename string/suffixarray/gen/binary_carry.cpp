#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int start = gen.uniform<int>(1, N_MAX);
    int n = gen.uniform(N_MAX - 10000, N_MAX);

    string s;
    for (int i = start; i < start + n; i++) {
        int j = 0;
        while (!(i & (1 << j))) j++;
        s += char('a' + j);
    }

    printf("%s\n", s.c_str());
    return 0;
}
