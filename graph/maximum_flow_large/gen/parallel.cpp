#include "../params.h"
#include "network.h"

int main(int, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    Random rng(seed);
    parallel_network(seed, N_MAX, M_MAX, C_MAX, rng).print(N_MAX, M_MAX, C_MAX);
}
