#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = choose_prime_for_large_binomial_degree(gen, N_MAX);
    int n = max_binomial_degree(N_MAX, p);
    print_case(p, shifted_binomial_irreducible(gen, n, p));
    return 0;
}
