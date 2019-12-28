#include <iostream>
#include <vector>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform(0, 1000000000);
    int b = gen.uniform(0, 1000000000);
    
    printf("%d %d\n", a, b);
    return 0;
}
