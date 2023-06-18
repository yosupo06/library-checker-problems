#include <cstdio>
#include <string>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MIN, N_MAX);

    string s = gen.lower_string(n);

    printf("%s\n", s.c_str());
    return 0;
}
