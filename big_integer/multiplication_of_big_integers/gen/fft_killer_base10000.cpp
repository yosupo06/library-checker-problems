#include <cstdio>
#include <cstdlib>
#include <string>
#include "random.h"
#include "../params.h"

std::string make(Random& gen, int spread) {
    std::string s;
    char digits[5];
    for (int i = 0; i < LOG_10_A_AND_B_MAX / 4; ++i) {
        std::snprintf(digits, sizeof(digits), "%04d", gen.uniform(10000 - spread, 9999));
        s += digits;
    }
    return s;
}
int main(int, char** argv) {
    int seed = std::atoi(argv[1]);
    Random gen(seed + 1);
    int spread[] = {10, 1000};
    auto a = make(gen, spread[seed % 2]);
    auto b = make(gen, spread[seed % 2]);
    std::printf("1\n%s %s\n", a.c_str(), b.c_str());
}
