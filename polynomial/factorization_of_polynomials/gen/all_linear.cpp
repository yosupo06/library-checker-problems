#include "poly_gen.hpp"

int main(int, char* argv[]) {
    auto gen = Random(atoll(argv[1]));
    ll p = choose_prime(gen);
    int n = gen.uniform<int>(1, N_MAX);
    Poly f = {1};
    for (int i = 0; i < n; i++) {
        ll root = gen.uniform<ll>(0, p - 1);
        f = mul(f, {norm(-root, p), 1}, p);
    }
    print_case(p, f);
    return 0;
}
