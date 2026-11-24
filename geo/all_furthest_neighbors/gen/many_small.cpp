#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  std::vector<std::vector<Point>> cases;
  cases.reserve(T_MAX);
  for (int i = 0; i < T_MAX; ++i) {
    ll a = gen.uniform<ll>(1, X_AND_Y_ABS_MAX);
    ll b = gen.uniform<ll>(1, X_AND_Y_ABS_MAX);
    std::vector<Point> polygon = {{-a, 0}, {0, -b}, {a, 0}};
    cyclic_shift(polygon, gen);
    cases.push_back(std::move(polygon));
  }
  output(cases);
  return 0;
}
