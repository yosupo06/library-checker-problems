#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    vector<int> ps = {2, 3, 5};
    ll p = ps[gen.uniform<int>(0, (int)ps.size() - 1)];
    int m = gen.uniform<int>(1, N_MAX / (int)p);
    Poly f(m * p + 1);
    for (int i = 0; i < m; i++) f[i * p] = gen.uniform<ll>(0, p - 1);
    f[m * p] = 1;
    print_case(p, f);
    return 0;
}
