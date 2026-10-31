#include <algorithm>
#include <cstdio>
#include <string>
#include "random.h"
#include "../params.h"

std::string make(Random& gen, int spread) {
    constexpr int count = LOG_16_A_AND_B_MAX * 4 / 14;
    std::string s;
    unsigned buffer = 0;
    int bits = 0;
    for (int i = 0; i < count; ++i) {
        buffer |= unsigned(gen.uniform(16384 - spread, 16383)) << bits;
        bits += 14;
        while (bits >= 4) {
            s += "0123456789ABCDEF"[buffer & 15];
            buffer >>= 4;
            bits -= 4;
        }
    }
    if (bits) s += "0123456789ABCDEF"[buffer];
    std::reverse(s.begin(), s.end());
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
