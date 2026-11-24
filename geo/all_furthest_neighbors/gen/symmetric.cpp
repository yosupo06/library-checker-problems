#include <cstdlib>

#include "genlib.hpp"

std::vector<Point> symmetric_polygon(int m) {
  std::vector<Point> polygon;
  polygon.reserve(2 * m + 1);
  for (int x = -m; x <= m; ++x) {
    if (x == 0) continue;
    polygon.emplace_back(x, ll(x) * x);
  }
  polygon.emplace_back(0, ll(m) * m + 10);
  return polygon;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  std::vector<std::vector<Point>> cases;
  for (int i = 0; i < 8; ++i) {
    std::vector<Point> polygon = symmetric_polygon(30'000);
    rotate_quarter(polygon, (int(seed) + i) % 4);
    cyclic_shift(polygon, gen);
    cases.push_back(std::move(polygon));
  }
  std::vector<Point> last = symmetric_polygon(9'995);
  rotate_quarter(last, int(seed) % 4);
  cyclic_shift(last, gen);
  cases.push_back(std::move(last));

  output(cases);
  return 0;
}
