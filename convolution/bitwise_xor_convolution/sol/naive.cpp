#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;
using u64 = std::uint64_t;

static constexpr u64 Mod = 998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  usize m;
  std::cin >> m;
  const usize n = 1 << m;
  std::vector<u64> a(n), b(n), c(n, 0);
  for (auto &e : a) {
    std::cin >> e;
  }
  for (auto &e : b) {
    std::cin >> e;
  }
  for (usize i = 0; i != n; i += 1) {
    for (usize j = 0; j != n; j += 1) {
      c[i ^ j] += a[i] * b[j] % Mod;
    }
  }
  for (usize i = 0; i != n; i += 1) {
    std::cout << c[i] % Mod << " \n"[i + 1 == n];
  }
  return 0;
}
