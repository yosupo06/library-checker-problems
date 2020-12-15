#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

static constexpr u32 Mod = 998244353;

struct modint {
  u32 v;
  modint(const u32 v_ = 0) : v(v_) {}
  friend modint operator+(const modint &l, const modint &r) {
    modint ret(l.v + r.v);
    if (ret.v >= Mod) {
      ret.v -= Mod;
    }
    return ret;
  }
  friend modint operator-(const modint &l, const modint &r) {
    modint ret(l.v - r.v);
    if (l.v < r.v) {
      ret.v += Mod;
    }
    return ret;
  }
  friend modint operator*(const modint &l, const modint &r) {
    return modint(static_cast<u64>(l.v) * r.v % Mod);
  }
};

void walsh_hadamard(std::vector<modint> &a) {
  const usize n = a.size();
  for (usize w = 1; w != n; w *= 2) {
    for (usize k = 0; k != n; k += w * 2) {
      for (usize i = 0; i != w; i += 1) {
        const modint x = a[k + i];
        const modint y = a[k + w + i];
        a[k + i] = x + y;
        a[k + w + i] = x - y;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  usize m;
  std::cin >> m;
  const usize n = 1 << m;
  std::vector<modint> a(n), b(n), c(n);
  for (auto &e : a) {
    std::cin >> e.v;
  }
  walsh_hadamard(a);
  for (auto &e : b) {
    std::cin >> e.v;
  }
  walsh_hadamard(b);
  for (usize i = 0; i != n; i += 1) {
    c[i] = a[i] * b[i];
  }
  walsh_hadamard(c);
  const modint inv = modint(Mod - (Mod - 1) / n);
  for (usize i = 0; i != n; i += 1) {
    std::cout << (c[i] * inv).v << " \n"[i + 1 == n];
  }
  return 0;
}
