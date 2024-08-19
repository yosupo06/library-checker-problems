#include "base.hpp"

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  gen_random(gen, N_MAX);
}
