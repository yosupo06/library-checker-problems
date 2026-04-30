#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = choose_prime(gen);
    int n = gen.uniform<int>(1, N_MAX);
    Poly f = random_monic(gen, n, p);
    print_case(p, f);
    return 0;
}
