#include <tuple>

template <typename T, typename U>
T floor(T x, U y) {
  return (x > 0 ? x / y : (x - y + 1) / y);
}

template <typename T>
struct Gaussian_Integer {
  T x, y;
  using G = Gaussian_Integer;

  Gaussian_Integer(T x = 0, T y = 0) : x(x), y(y) {}
  Gaussian_Integer(pair<T, T> p) : x(p.fi), y(p.se) {}

  T norm() const { return x * x + y * y; }
  G conjugate() const { return G(x, -y); }

  G &operator+=(const G &g) {
    x += g.x, y += g.y;
    return *this;
  }
  G &operator-=(const G &g) {
    x -= g.x, y -= g.y;
    return *this;
  }
  G &operator*=(const G &g) {
    tie(x, y) = make_pair(x * g.x - y * g.y, x * g.y + y * g.x);
    return *this;
  }
  G &operator/=(const G &g) {
    *this *= g.conjugate();
    T n = g.norm();
    x = floor(x + n / 2, n);
    y = floor(y + n / 2, n);
    return *this;
  }
  G &operator%=(const G &g) {
    auto q = G(*this) / g;
    q *= g;
    (*this) -= q;
    return *this;
  }
  G operator-() { return G(-x, -y); }
  G operator+(const G &g) { return G(*this) += g; }
  G operator-(const G &g) { return G(*this) -= g; }
  G operator*(const G &g) { return G(*this) *= g; }
  G operator/(const G &g) { return G(*this) /= g; }
  G operator%(const G &g) { return G(*this) %= g; }
  bool operator==(const G &g) { return (x == g.x && y == g.y); }

  static G gcd(G a, G b) {
    while (b.x != 0 || b.y != 0) {
      a %= b;
      swap(a, b);
    }
    return a;
  }

  // (g,x,y) s.t ax+by=g
  static tuple<G, G, G> extgcd(G a, G b) {
    if (b.x != 0 || b.y != 0) {
      G q = a / b;
      auto [g, x, y] = extgcd(b, a - q * b);
      return {g, y, x - q * y};
    }
    return {a, G{1, 0}, G{0, 0}};
  }
};
