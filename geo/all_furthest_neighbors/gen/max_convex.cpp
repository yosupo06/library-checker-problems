#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  std::vector<Point> polygon = primitive_polygon(SUM_N_MAX);
  cyclic_shift(polygon, gen);
  output({polygon});
  return 0;
}
