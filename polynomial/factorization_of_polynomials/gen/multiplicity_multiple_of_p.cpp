#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    vector<int> ps = {2, 3, 5, 7};
    ll p = ps[gen.uniform<int>(0, (int)ps.size() - 1)];
    int e = (int)p * gen.uniform<int>(1, 5);
    int d = gen.uniform<int>(1, max(1, (int)N_MAX / e));
    Poly g = random_irreducible(gen, d, p);
    Poly f = {1};
    for (int i = 0; i < e; i++) f = mul(f, g, p);
    print_case(p, f);
    return 0;
}
