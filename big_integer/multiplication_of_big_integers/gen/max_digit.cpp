#include <cstdio>
#include <string>
#include "../params.h"

int main() {
    // Maximal digits stress FFT rounding and the following carry chain.
    const std::string a(LOG_10_A_AND_B_MAX, '9');
    std::printf("1\n%s %s\n", a.c_str(), a.c_str());
}
