#include <cstdio>
#include <string>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string a, b;

    // until a != b
    do {
        a = gen.lower_string(gen.uniform(1, 5));
        b = gen.lower_string(gen.uniform(1, 5));
    } while(a == b);

    while (a.size() + b.size() <= N_MAX) {
        string c = a + b;
        a = b;
        b = c;
    }
   
    string s = b;

    printf("%s\n", s.c_str());
    return 0;
}
