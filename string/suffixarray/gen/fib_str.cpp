#include <iostream>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string a = gen.lower_string(gen.uniform(1, 5));
    string b = gen.lower_string(gen.uniform(1, 5));

    while (a.size() + b.size() <= N_MAX) {
        string c = a + b;
        a = b;
        b = c;
    }
   
    string s = b;

    printf("%s\n", s.c_str());
    return 0;
}
