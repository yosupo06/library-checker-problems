#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;

    char c = gen.uniform('a', 'z');

    string s(n, c);

    printf("%s\n", s.c_str());
    return 0;
}
