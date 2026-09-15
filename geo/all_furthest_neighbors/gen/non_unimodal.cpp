#include <algorithm>
#include <cstdlib>

#include "genlib.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  Random gen(seed);

  const std::vector<Point> clockwise = {
      {0, 0},          {-18'767, -43'052}, {-21'874, -41'502},
      {-100'000, 0},  {-280, 6'810},      {-189, 4'855},
  };

  std::vector<std::vector<Point>> cases;
  const int case_count = 40'000;
  cases.reserve(case_count);
  for (int t = 0; t < case_count; ++t) {
    std::vector<Point> polygon = clockwise;
    std::reverse(polygon.begin(), polygon.end());

    ll a, b;
    do {
      a = gen.uniform<ll>(-4'000, 4'000);
      b = gen.uniform<ll>(-4'000, 4'000);
    } while (a == 0 && b == 0);
    for (Point& p : polygon) {
      ll x = p.first;
      ll y = p.second;
      p = {a * x - b * y, b * x + a * y};
    }
    cyclic_shift(polygon, gen);
    cases.push_back(std::move(polygon));
  }

  output(cases);
  return 0;
}
