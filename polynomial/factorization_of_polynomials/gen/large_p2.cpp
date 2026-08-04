#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = 2;
    Poly f = random_monic(gen, N_MAX, p);
    print_case(p, f);
    return 0;
}
