#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);
  const ll r = X_AND_Y_ABS_MAX;

  std::vector<std::vector<Point>> cases = {
      {{-r, -r}, {r, -r}, {r, r}, {-r, r}},
      {{-r, 0}, {0, -r}, {r, 0}, {0, r}},
      {{-r, -r}, {r, -r + 1}, {r - 1, r}, {-r, r - 1}},
      {{-r, 0}, {r, -1}, {r - 1, 1}},
      {{-r, -r}, {r, -r}, {0, r}},
      {{-r, 0}, {r, 0}, {r, 1}},
      {{-r, 0}, {r, -1}, {r, 0}},
  };
  for (auto& polygon : cases) cyclic_shift(polygon, gen);
  output(cases);
  return 0;
}
