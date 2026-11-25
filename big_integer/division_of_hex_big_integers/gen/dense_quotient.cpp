#include <cstdio>
#include <string>

int main() {
    // A = B * (16^(3m) - 1), B = 8 * 16^(m-1) + 1.
    // The quotient is dense and the remainder is exactly zero.
    std::puts("5");
    for (int m : {28, 29, 30, 31, 32}) {
        auto a = "8" + std::string(m - 1, '0') + std::string(2 * m, 'F')
               + "7" + std::string(m - 1, 'F');
        auto b = "8" + std::string(m - 2, '0') + "1";
        std::printf("%s %s\n", a.c_str(), b.c_str());
    }
}
