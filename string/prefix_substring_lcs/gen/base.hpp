#include <cstdio>
#include <string>
#include <tuple>
#include <vector>

#include "random.h"

void generate(Random &gen, const int M, const int N, const int Q) {
  const std::string S = gen.lower_string(M);
  const std::string T = gen.lower_string(N);
  std::vector<std::tuple<int, int, int>> qs(Q);
  for (auto &[a, b, c] : qs) {
    a = gen.uniform<int>(0, M);
    std::tie(b, c) = gen.uniform_pair<int>(0, N + 1);
    c -= 1;
  }

  std::printf("%d\n", Q);
  std::printf("%s\n", S.c_str());
  std::printf("%s\n", T.c_str());
  for (const auto &[a, b, c] : qs) {
    std::printf("%d %d %d\n", a, b, c);
  }
}
