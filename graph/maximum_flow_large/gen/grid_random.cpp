#include "../params.h"
#include "network.h"

// Goldfarb-Grigoriadis (1988): https://doi.org/10.1007/BF02288321
// Bidirectional variant: https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/genrmf.cpp
// Original forward-only DIMACS generator (seeds 6..9):
// https://archive.dimacs.rutgers.edu/pub/netflow/generators/network/genrmf/
int main(int argc, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    int a = seed < 2 ? 4 : (seed < 4 ? 5 : 12);
    int b = seed < 2 ? 120 : (seed < 4 ? 75 : 12);
    // The DIMACS 1991 original has only forward inter-frame arcs. Keep it
    // separate from the bidirectional variant used for seeds 0..5.
    if (seed >= 6) { a = seed < 8 ? 4 : 12; b = seed < 8 ? 120 : 12; }
    if (argc > 3) { a = std::atoi(argv[2]); b = std::atoi(argv[3]); }
    Random rng(seed);
    genrmf_network(a, b, rng, seed < 6).print(N_MAX, M_MAX, C_MAX);
}
