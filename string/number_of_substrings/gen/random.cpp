#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);

    string s = gen.lower_string(n);

    printf("%s", s.c_str());
    return 0;
}
