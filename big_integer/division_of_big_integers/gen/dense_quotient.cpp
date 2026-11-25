#include <cstdio>
#include <string>

int main() {
    // A = B * (10^(3m) - 1), B = 5 * 10^(m-1) + 1.
    // The quotient is dense and the remainder is exactly zero.
    std::puts("5");
    for (int m : {31, 32, 33, 34, 65}) {
        auto a = "5" + std::string(m - 1, '0') + std::string(2 * m, '9')
               + "4" + std::string(m - 1, '9');
        auto b = "5" + std::string(m - 2, '0') + "1";
        std::printf("%s %s\n", a.c_str(), b.c_str());
    }
}
