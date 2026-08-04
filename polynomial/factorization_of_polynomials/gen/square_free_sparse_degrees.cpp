#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = gen.uniform_bool() ? 101 : 998244353;
    Poly f = {1};
    for (int d = 1; (int)f.size() - 1 + d <= N_MAX; d = d * 2 + 1) {
        f = mul(f, random_irreducible(gen, d, p), p);
    }
    print_case(p, f);
    return 0;
}
