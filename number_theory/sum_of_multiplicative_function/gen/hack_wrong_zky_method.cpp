#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tr2/dynamic_bitset>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
namespace prime {
using uint128 = __uint128_t;
using uint64 = unsigned long long;
using int64 = long long;
using uint32 = unsigned int;
using pii = std::pair<uint64, uint32>;
inline uint64 sqr(uint64 x) { return x * x; }
inline uint32 isqrt(uint64 x) { return sqrtl(x); }
inline uint32 ctz(uint64 x) { return __builtin_ctzll(x); }
template <typename word>
word gcd(word a, word b) {
  while (b) {
    word t = a % b;
    a = b;
    b = t;
  }

  return a;
}
template <typename word, typename dword, typename sword>
struct Mod {
  Mod() : x(0) {}
  Mod(word _x) : x(init(_x)) {}
  bool operator==(const Mod &rhs) const { return x == rhs.x; }
  bool operator!=(const Mod &rhs) const { return x != rhs.x; }
  Mod &operator+=(const Mod &rhs) {
    if ((x += rhs.x) >= mod) x -= mod;

    return *this;
  }
  Mod &operator-=(const Mod &rhs) {
    if (sword(x -= rhs.x) < 0) x += mod;

    return *this;
  }
  Mod &operator*=(const Mod &rhs) {
    x = reduce(dword(x) * rhs.x);
    return *this;
  }
  Mod operator+(const Mod &rhs) const { return Mod(*this) += rhs; }
  Mod operator-(const Mod &rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(const Mod &rhs) const { return Mod(*this) *= rhs; }
  Mod operator-() const { return Mod() - *this; }
  Mod pow(uint64 e) const {
    Mod ret(1);

    for (Mod base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }

    return ret;
  }
  word get() const { return reduce(x); }
  static constexpr int word_bits = sizeof(word) * 8;
  static word modulus() { return mod; }
  static word init(word w) { return reduce(dword(w) * r2); }
  static void set_mod(word m) {
    mod = m, inv = mul_inv(mod), r2 = -dword(mod) % mod;
  }
  static word reduce(dword x) {
    word y =
        word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }
  static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }
  static word mod, inv, r2;
  word x;
};
using Mod64 = Mod<uint64, uint128, int64>;
using Mod32 = Mod<uint32, uint64, int>;
template <>
uint64 Mod64::mod = 0;
template <>
uint64 Mod64::inv = 0;
template <>
uint64 Mod64::r2 = 0;
template <>
uint32 Mod32::mod = 0;
template <>
uint32 Mod32::inv = 0;
template <>
uint32 Mod32::r2 = 0;
template <class word, class mod>
bool composite(word n, const uint32 *bases, int m) {
  mod::set_mod(n);
  int s = __builtin_ctzll(n - 1);
  word d = (n - 1) >> s;
  mod one{1}, minus_one{n - 1};

  for (int i = 0, j; i < m; ++i) {
    mod a = mod(bases[i]).pow(d);

    if (a == one || a == minus_one) continue;

    for (j = s - 1; j > 0; --j) {
      if ((a *= a) == minus_one) break;
    }

    if (j == 0) return true;
  }

  return false;
}
bool is_prime(uint64 n) {
  assert(n < (uint64(1) << 63));
  static const uint32 bases[][7] = {
      {2, 3},
      {2, 299417},
      {2, 7, 61},
      {15, 176006322, uint32(4221622697)},
      {2, 2570940, 211991001, uint32(3749873356)},
      {2, 2570940, 880937, 610386380, uint32(4130785767)},
      {2, 325, 9375, 28178, 450775, 9780504, 1795265022}};

  if (n <= 1) return false;

  if (!(n & 1)) return n == 2;

  if (n <= 8) return true;

  int x = 6, y = 7;

  if (n < 1373653)
    x = 0, y = 2;
  else if (n < 19471033)
    x = 1, y = 2;
  else if (n < 4759123141)
    x = 2, y = 3;
  else if (n < 154639673381)
    x = y = 3;
  else if (n < 47636622961201)
    x = y = 4;
  else if (n < 3770579582154547)
    x = y = 5;

  if (n < (uint32(1) << 31)) {
    return !composite<uint32, Mod32>(n, bases[x], y);
  } else if (n < (uint64(1) << 63)) {
    return !composite<uint64, Mod64>(n, bases[x], y);
  }

  return true;
}
struct ExactDiv {
  ExactDiv() {}
  ExactDiv(uint64 n) : n(n), i(Mod64::mul_inv(n)), t(uint64(-1) / n) {}
  friend uint64 operator/(uint64 n, ExactDiv d) { return n * d.i; };
  bool divide(uint64 n) { return n / *this <= t; }
  uint64 n, i, t;
};
std::vector<ExactDiv> primes;
void init(uint32 n) {
  uint32 sqrt_n = sqrt(n);
  std::vector<bool> is_prime(n + 1, 1);
  primes.clear();

  for (uint32 i = 2; i <= sqrt_n; ++i)
    if (is_prime[i]) {
      if (i != 2) primes.push_back(ExactDiv(i));

      for (uint32 j = i * i; j <= n; j += i) is_prime[j] = 0;
    }
}
template <typename word, typename mod>
word brent(word n, word c) {
  const uint64 s = 256;
  mod::set_mod(n);
  const mod one = mod(1), mc = mod(c);
  mod y = one;

  for (uint64 l = 1;; l <<= 1) {
    auto x = y;

    for (int i = 0; i < (int)l; ++i) y = y * y + mc;

    mod p = one;

    for (int k = 0; k < (int)l; k += s) {
      auto sy = y;

      for (int i = 0; i < (int)std::min(s, l - k); ++i) {
        y = y * y + mc;
        p *= y - x;
      }

      word g = gcd(n, p.x);

      if (g == 1) continue;

      if (g == n)
        for (g = 1, y = sy; g == 1;) {
          y = y * y + mc, g = gcd(n, (y - x).x);
        }

      return g;
    }
  }
}
uint64 brent(uint64 n, uint64 c) {
  if (n < (uint32(1) << 31)) {
    return brent<uint32, Mod32>(n, c);
  } else if (n < (uint64(1) << 63)) {
    return brent<uint64, Mod64>(n, c);
  }

  return 0;
}
std::vector<pii> factors(uint64 n) {
  assert(n < (uint64(1) << 63));

  if (n <= 1) return {};

  std::vector<pii> ret;

  uint32 v = sqrtl(n);

  if (uint64(v) * v == n) {
    ret = factors(v);

    for (auto &&e : ret) e.second *= 2;

    return ret;
  }

  v = cbrtl(n);

  if (uint64(v) * v * v == n) {
    ret = factors(v);

    for (auto &&e : ret) e.second *= 3;

    return ret;
  }

  if (!(n & 1)) {
    uint32 e = __builtin_ctzll(n);
    ret.emplace_back(2, e);
    n >>= e;
  }

  uint64 lim = sqr(primes.back().n);

  for (auto &&p : primes) {
    if (sqr(p.n) > n) break;

    if (p.divide(n)) {
      uint32 e = 1;
      n = n / p;

      while (p.divide(n)) n = n / p, e++;

      ret.emplace_back(p.n, e);
    }
  }

  uint32 s = ret.size();

  while (n > lim && !is_prime(n)) {
    for (uint64 c = 1;; ++c) {
      uint64 p = brent(n, c);

      if (!is_prime(p)) continue;

      uint32 e = 1;
      n /= p;

      while (n % p == 0) n /= p, e += 1;

      ret.emplace_back(p, e);
      break;
    }
  }

  if (n > 1) ret.emplace_back(n, 1);

  if (ret.size() - s >= 2) sort(ret.begin() + s, ret.end());

  return ret;
}
}  // namespace prime
struct FastIO {
  static const int S = 655360;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len) pos = 0, len = fread(buf, 1, S, in);

    if (pos == len) {
      eof = true;
      return -1;
    }

    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;

    while (c <= 32) c = nextChar();

    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';

    return x;
  }
  inline prime::uint64 next_u64() {
    int c = nextChar();
    prime::uint64 x = 0;

    while (!eof && c <= 32) c = nextChar();

    if (eof) return 0;

    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';

    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;

    while (c <= 32) c = nextChar();

    if (c == '-') s = -1, c = nextChar();

    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';

    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();

    while (c <= 32) c = nextChar();

    for (; c > 32; c = nextChar()) *s++ = c;

    *s = 0;
  }
} io;

void out(std::vector<long long> &vec) {
  std::mt19937 engine(19260817);

  std::sort(vec.begin(), vec.end());
  vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
  long long max = vec.back();
  if (vec.size() != 1)
    assert(max * vec.size() * vec.size() <= 1000000000000);
  else
    assert(max <= 10000000000000);
  std::shuffle(vec.begin(), vec.end(), engine);

  printf("%d\n", (int)vec.size());
  for (auto x : vec) {
    int a = std::uniform_int_distribution<int>(3, 469762048)(engine);
    int b = std::uniform_int_distribution<int>(3, 469762048)(engine);
    printf("%lld %d %d\n", x, a, b);
  }
}

int delta[9] = {0, 1, -1, 2, -2, 16, -16, 128, -128};

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);

  int remainder = seed % 6;
  if (remainder == 0) {
    std::vector<long long> ns;

    for (int i = 2;; ++i)
      if (prime::is_prime(i) && prime::is_prime(i + 2) && i * (i + 2) > 10000) {
        if ((ns.size() + 9) * (i + 2) <= 1000000)
          for (int c = 0; c < 9; ++c) ns.push_back(i * (i + 2) + delta[c]);
        else
          break;
      }
    out(ns);
  } else if (remainder == 1) {
    std::vector<long long> ns;

    for (int j = 2;; ++j)
      if (prime::is_prime(j)) {
        if (prime::is_prime(2 * j + 1) && 2 * j * (2 * j + 1) > 10000) {
          if ((ns.size() + 9) * (2 * j + 1) <= 1000000)
            for (int c = 0; c < 9; ++c)
              ns.push_back(2 * j * (2 * j + 1) + delta[c]);
          else
            break;
        }
      }
    out(ns);
  } else if (remainder == 2) {
    std::vector<long long> ns;

    for (int j = 2;; ++j)
      if (prime::is_prime(j)) {
        for (int i = 2; i <= j; ++i)
          if (prime::is_prime(i) && prime::is_prime(i * j + 2) &&
              i * j * (i * j + 2) > 10000) {
            if ((ns.size() + 9) * (i * j + 2) <= 1000000)
              for (int c = 0; c < 9; ++c)
                ns.push_back(i * j * (i * j + 2) + delta[c]);
            else
              goto donepp;
          }
      }
  donepp:
    out(ns);
    // out("10_13_469762049_gen3.in", ns);
  } else if (remainder == 3) {
    std::vector<long long> ns;

    for (long long i = std::sqrt(1E13) - 2;; --i)
      if (prime::is_prime(i) && prime::is_prime(i + 2)) {
        ns.push_back(i * (i + 2));
        break;
      }
    out(ns);
  } else if (remainder == 4) {
    std::vector<long long> ns;
    for (long long i = (std::sqrt(1E13) - 1) / 2;; --i)
      if (prime::is_prime(i) && prime::is_prime(2 * i + 1)) {
        ns.push_back(2 * i * (2 * i + 1));
        break;
      }
    out(ns);
  } else if (remainder == 5) {
    std::vector<long long> ns;
    long long L = std::sqrt((std::sqrt(1E13) - 2));
    for (long long j = L;; --j)
      if (prime::is_prime(j)) {
        for (long long i = L; i > j; --i)
          if (prime::is_prime(i) && prime::is_prime(i * j + 2)) {
            ns.push_back(i * j * (i * j + 2));
            goto donelpp;
          }
      }
  donelpp:
    out(ns);
  }

  return 0;
}