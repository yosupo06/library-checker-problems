#include <cstdio>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long nmin = N_MIN;
    if(nmin < N_MAX - 1000) nmin = N_MAX - 1000;

    int n = gen.uniform(nmin, N_MAX);

    char c = 'a';

    string s(n, c);
    s.back() = c + 1;

    printf("%s\n", s.c_str());
    return 0;
}
