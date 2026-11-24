#include <cstdio>
#include <string>

#include "../params.h"

int main() {
    // Dense maximal digits stress FFT precision and the resulting carry chain.
    const std::string a(LOG_16_A_AND_B_MAX, 'F');
    std::printf("1\n%s %s\n", a.c_str(), a.c_str());
}
