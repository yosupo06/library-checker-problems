#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  const int base_n = 256;
  std::vector<Point> base = primitive_polygon(base_n);
  std::vector<std::vector<Point>> cases;
  int sum_n = 0;
  while (sum_n < 20'000) {
    int n = gen.uniform<int>(3, 30);
    if (sum_n + n > 20'000) break;
    std::vector<int> ids(base_n);
    std::iota(ids.begin(), ids.end(), 0);
    gen.shuffle(ids.begin(), ids.end());
    ids.resize(n);
    std::vector<Point> polygon = select_vertices(base, std::move(ids));
    cyclic_shift(polygon, gen);
    cases.push_back(std::move(polygon));
    sum_n += n;
  }
  output(cases);
  return 0;
}
