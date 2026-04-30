#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    int d1 = choose_binomial_degree(gen, min(70, (int)N_MAX / 3));
    int d2 = choose_binomial_degree(gen, min(70, ((int)N_MAX - d1) / 2));
    int d3 = choose_binomial_degree(gen, min(70, (int)N_MAX - d1 - d2));
    ll p = 998244353;
    Poly f = {1};
    f = mul(f, shifted_binomial_irreducible(gen, d1, p), p);
    f = mul(f, shifted_binomial_irreducible(gen, d2, p), p);
    f = mul(f, shifted_binomial_irreducible(gen, d3, p), p);
    print_case(p, f);
    return 0;
}
