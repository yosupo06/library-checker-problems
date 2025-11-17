#include <cstdio> // scanf, printf
#include <utility> // swap, pair
#include <cassert> // assert

using namespace std;
using ll = long long;

template <typename T>
bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T>
constexpr std::pair<T, T> divmod(T a, T b) {
  T q = a / b;
  T r = a % b;
  return {q, r};
}

template <typename T>
constexpr std::pair<T, T> divmod_floor(T a, T b) {
  T q = a / b;
  T r = a % b;
  if ((r != 0) && ((r > 0) != (b > 0))) {
    q -= 1;
    r += b;
  }
  return {q, r};
}

template <typename T>
constexpr std::pair<T, T> divmod_euclid(T a, T b) {
  T q = a / b;
  T r = a % b;
  if (r < 0) {
    if (b > 0) {
      q -= 1;
      r += b;
    } else {
      q += 1;
      r -= b;
    }
  }
  return {q, r};
}

// Computes ReturnValue = max{ a*x + b*floor((c*x + d)/m) | l <= x < r }
// for integers l, r, m, a, b, c, d with l < r and 0 < m
template <typename T>
T max_weighted_floor_of_linear(T l, T r, T m, T a, T b, T c, T d) {
  assert(l < r && 0 < m);
  T n = r - l;
  const auto [qd0, rd0] = divmod_euclid<T>(c * l + d, m);
  d = rd0;
  T sum_acc = a * l + b * qd0;
  T max_acc = sum_acc;
  while (true) {
    const auto [qc, rc] = divmod_euclid<T>(c, m);
    c = rc;
    a = a + b * qc;
    const auto [qd, rd] = divmod_euclid<T>(d, m);
    d = rd;
    sum_acc = sum_acc + b * qd;
    assert(0 < n && 0 < m && 0 <= c && c < m && 0 <= d && d < m);
    const T n1 = n - 1;
    const T y_max = (c * n1 + d) / m;
    chmax<T>(max_acc, sum_acc);
    chmax<T>(max_acc, sum_acc + a * n1 + b * y_max);
    if (y_max == 0 || (a >= 0 && b >= 0) || (a <= 0 && b <= 0)) {
      return max_acc;
    }
    if (a < 0) {
      sum_acc += a + b;
    }
    n = y_max;
    d = m - d - 1;
    std::swap(a, b);
    std::swap(c, m);
    assert(0 < n && 0 < m && 0 < c && 0 <= d);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    ll n, m, a, b, c, d;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &a, &b, &c, &d);
    ll x = max_weighted_floor_of_linear<ll>(0, n, m, a, b, c, d);
    printf("%lld\n", x);
  }
  return 0;
}
