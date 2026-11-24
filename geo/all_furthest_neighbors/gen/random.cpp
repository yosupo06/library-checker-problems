#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  std::vector<Point> base = primitive_polygon(SUM_N_MAX);
  std::vector<int> ids(SUM_N_MAX);
  std::iota(ids.begin(), ids.end(), 0);
  gen.shuffle(ids.begin(), ids.end());

  std::vector<std::vector<Point>> cases;
  int used = 0;
  while (used < SUM_N_MAX) {
    int remaining = SUM_N_MAX - used;
    int n;
    if (remaining <= 20'000) {
      n = remaining;
    } else {
      n = gen.uniform<int>(100, 20'000);
      if (remaining - n < 3) n = remaining;
    }
    std::vector<int> current(ids.begin() + used, ids.begin() + used + n);
    std::vector<Point> polygon = select_vertices(base, std::move(current));
    cyclic_shift(polygon, gen);
    cases.push_back(std::move(polygon));
    used += n;
  }
  output(cases);
  return 0;
}
