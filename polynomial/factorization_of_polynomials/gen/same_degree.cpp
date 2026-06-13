#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = gen.uniform_bool() ? 101 : 998244353;
    int d = gen.uniform<int>(1, 12);
    int k = gen.uniform<int>(2, max(2, (int)N_MAX / d));
    Poly f = {1};
    set<string> used;
    for (int i = 0; i < k; i++) {
        Poly g;
        do {
            g = random_irreducible(gen, d, p);
        } while (!used.insert(key(g)).second);
        f = mul(f, g, p);
    }
    print_case(p, f);
    return 0;
}
