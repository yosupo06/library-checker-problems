#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, (int)N_MAX);

    string s = gen.lower_string(n);

    printf("%s\n", s.c_str());
    return 0;
}
