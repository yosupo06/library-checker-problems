#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    int d1 = choose_binomial_degree(gen, min(100, (int)N_MAX / 2));
    int d2 = choose_binomial_degree(gen, min(100, (int)N_MAX - d1));
    ll p = 998244353;
    Poly f = mul(shifted_binomial_irreducible(gen, d1, p),
                 shifted_binomial_irreducible(gen, d2, p), p);
    print_case(p, f);
    return 0;
}
