#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    int n = choose_binomial_degree(gen, (int)N_MAX);
    ll p = 998244353;
    print_case(p, shifted_binomial_irreducible(gen, n, p));
    return 0;
}
