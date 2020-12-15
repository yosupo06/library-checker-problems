#include "../params.h"
#include "random.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using u32 = std::uint32_t;
using usize = std::size_t;

static constexpr u32 Mod = MOD;

void gen_random(Random &gen, const usize n) {
  assert(n <= N_MAX);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << n << "\n";
  const usize m = 1 << n;
  for (usize i = 0; i != m; i += 1) {
    std::cout << gen.uniform<u32>(0, Mod - 1) << " \n"[i + 1 == m];
  }
  for (usize i = 0; i != m; i += 1) {
    std::cout << gen.uniform<u32>(0, Mod - 1) << " \n"[i + 1 == m];
  }
}
