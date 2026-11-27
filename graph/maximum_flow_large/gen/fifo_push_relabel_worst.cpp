#include "../params.h"
#include "adversarial.h"

// Weininger, Anti-FIFO (CC0); Cheriyan-Maheshwari (1989).
// https://doi.org/10.1137/0218072
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_fifopp.cpp
int main() {
    const int k = std::min(int(N_MAX) / 10, (int(M_MAX) + 3) / 13);
    anti_fifo_network(k, C_MAX).print(N_MAX, M_MAX, C_MAX);
}
