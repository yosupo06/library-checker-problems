#include "../params.h"
#include "adversarial.h"

// Cherkassky-Goldberg AK topology; independent implementation.
// https://doi.org/10.1007/PL00009180
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/ak.cpp
int main() {
    const int size = std::min((int(N_MAX) - 6) / 4, (int(M_MAX) - 7) / 6);
    ak_network(size, C_MAX).print(N_MAX, M_MAX, C_MAX);
}
