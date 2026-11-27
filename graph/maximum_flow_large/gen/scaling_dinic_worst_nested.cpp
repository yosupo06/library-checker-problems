#include "../params.h"
#include "adversarial.h"

// Weininger, Anti-Scaling-Dinic (CC0), adapted to our shared-hub gadget.
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_scaling_dinic.cpp
int main() {
    anti_scaling_network(10, 25, 17, 50, C_MAX).print(N_MAX, M_MAX, C_MAX);
}
