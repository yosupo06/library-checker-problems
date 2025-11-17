#include <cstdio> // scanf, printf
#include <utility> // pair
#include <cassert> // assert

using namespace std;
using ll = long long;

template <typename T> bool chmax(T& a, T b){
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

// f(x) = a*x + b*floor((c*x + d)/m)
template <typename T>
T mwf_f(T x, T m, T a, T b, T c, T d) {
  return a * x + b * divmod_floor((c * x + d), m).first;
}

// max_{f(x) in [L, R)}
// f(x) = (ax + b * floor((cx + d) / m))
template <typename T>
T max_weighted_floor_of_linear(T l, T r, T m, T a, T b, T c, T d) {
  assert(l < r && 0 < m);
  T res = mwf_f(l, m, a, b, c, d);
  for (T x = l; x < r; x++) {
    T val = mwf_f(x, m, a, b, c, d);
    chmax<T>(res, val);
  }
  return res;
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
