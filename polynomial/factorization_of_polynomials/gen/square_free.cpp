#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = gen.uniform_bool() ? 101 : 998244353;
    int target = gen.uniform<int>(1, N_MAX);
    Poly f = {1};
    set<string> used;
    while ((int)f.size() - 1 < target) {
        int rem = target - ((int)f.size() - 1);
        int d = gen.uniform<int>(1, min(8, rem));
        Poly g;
        do {
            g = random_irreducible(gen, d, p);
        } while (!used.insert(key(g)).second);
        f = mul(f, g, p);
    }
    print_case(p, f);
    return 0;
}
