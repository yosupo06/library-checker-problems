#include "../params.h"
#include "network.h"

// MiSawa, Exponential instance for a wrong implementation of Dinic.
// https://gist.github.com/MiSawa/47b1d99c372daffb6891662db1a2b686
// Targets missing current-arc updates; this is not a lower bound for correct Dinic.
int main(int argc, char* argv[]) {
    // Optional size is used only for the exponential-growth benchmark.
    const int n = argc > 2 ? std::atoi(argv[2]) : 100;
    misawa_network(n).print(N_MAX, M_MAX, C_MAX);
}
