#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(490'000, 500'000);

    char c = gen.uniform('a', 'z');

    string s(n, c);

    printf("%s", s.c_str());
    return 0;
}
