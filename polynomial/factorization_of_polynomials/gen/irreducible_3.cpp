#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = choose_prime_for_large_binomial_degree(gen, N_MAX);
    int d1 = max_binomial_degree(N_MAX / 3, p);
    int d2 = max_binomial_degree((N_MAX - N_MAX / 3) / 2, p);
    int d3 = max_binomial_degree(N_MAX - N_MAX / 3 - (N_MAX - N_MAX / 3) / 2, p);
    Poly f = {1};
    f = mul(f, shifted_binomial_irreducible(gen, d1, p), p);
    f = mul(f, shifted_binomial_irreducible(gen, d2, p), p);
    f = mul(f, shifted_binomial_irreducible(gen, d3, p), p);
    print_case(p, f);
    return 0;
}
