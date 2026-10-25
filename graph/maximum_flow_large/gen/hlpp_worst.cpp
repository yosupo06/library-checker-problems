#include "../params.h"
#include "adversarial.h"

// Weininger, Anti-HLPP (CC0); Cheriyan-Maheshwari (1989).
// https://doi.org/10.1137/0218072
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_hlpp.cpp
int main() {
    const auto [k, w, l] = hlpp_parameters(N_MAX, M_MAX, C_MAX);
    anti_hlpp_network(k, w, l).print(N_MAX, M_MAX, C_MAX);
}
