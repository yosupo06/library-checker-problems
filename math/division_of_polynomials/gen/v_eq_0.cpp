
#include "../params.h"
#include "random.h"
using namespace std;

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const { return pow(mod - 2); }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};
//

template <typename mint>
struct NTT {
  static constexpr uint32_t get_pr() {
    uint32_t _mod = mint::get_mod();
    using u64 = uint64_t;
    u64 ds[32] = {};
    int idx = 0;
    u64 m = _mod - 1;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        ds[idx++] = i;
        while (m % i == 0) m /= i;
      }
    }
    if (m != 1) ds[idx++] = m;

    uint32_t _pr = 2;
    while (1) {
      int flg = 1;
      for (int i = 0; i < idx; ++i) {
        u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
        while (b) {
          if (b & 1) r = r * a % _mod;
          a = a * a % _mod;
          b >>= 1;
        }
        if (r == 1) {
          flg = 0;
          break;
        }
      }
      if (flg == 1) break;
      ++_pr;
    }
    return _pr;
  };

  static constexpr uint32_t mod = mint::get_mod();
  static constexpr uint32_t pr = get_pr();
  static constexpr int level = __builtin_ctzll(mod - 1);
  mint dw[level], dy[level];

  void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inverse();
    for (int i = k - 2; i > 0; --i)
      w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
    dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
    for (int i = 3; i < k; ++i) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  NTT() { setwy(level); }

  void fft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if (k & 1) {
      int v = 1 << (k - 1);
      for (int j = 0; j < v; ++j) {
        mint ajv = a[j + v];
        a[j + v] = a[j] - ajv;
        a[j] += ajv;
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    mint one = mint(1);
    mint imag = dw[1];
    while (v) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = j1 + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dw[2], wx = one;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, wx = ww * xx;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww,
               t3 = a[j2 + v] * wx;
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j0 + v] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j2 + v] = t0m2 - t1m3;
        }
        xx *= dw[__builtin_ctzll((jh += 4))];
      }
      u <<= 2;
      v >>= 2;
    }
  }

  void ifft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    mint one = mint(1);
    mint imag = dy[1];
    while (u) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = v + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;
          a[j0] = t0p1 + t2p3, a[j2] = t0p1 - t2p3;
          a[j1] = t0m1 + t2m3, a[j3] = t0m1 - t2m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dy[2], yy = one;
      u <<= 2;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, yy = xx * imag;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;
          a[j0 + v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;
        }
        xx *= dy[__builtin_ctzll(jh += 4)];
      }
      u >>= 4;
      v <<= 2;
    }
    if (k & 1) {
      u = 1 << (k - 1);
      for (int j = 0; j < u; ++j) {
        mint ajv = a[j] - a[j + u];
        a[j] += a[j + u];
        a[j + u] = ajv;
      }
    }
  }

  void ntt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    fft4(a, __builtin_ctz(a.size()));
  }

  void intt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    ifft4(a, __builtin_ctz(a.size()));
    mint iv = mint(a.size()).inverse();
    for (auto &x : a) x *= iv;
  }

  vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
    int l = a.size() + b.size() - 1;
    if (min<int>(a.size(), b.size()) <= 40) {
      vector<mint> s(l);
      for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
      return s;
    }
    int k = 2, M = 4;
    while (M < l) M <<= 1, ++k;
    setwy(k);
    vector<mint> s(M), t(M);
    for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i];
    for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i];
    fft4(s, k);
    fft4(t, k);
    for (int i = 0; i < M; ++i) s[i] *= t[i];
    ifft4(s, k);
    s.resize(l);
    mint invm = mint(M).inverse();
    for (int i = 0; i < l; ++i) s[i] *= invm;
    return s;
  }

  void ntt_doubling(vector<mint> &a) {
    int M = (int)a.size();
    auto b = a;
    intt(b);
    mint r = 1, zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
    for (int i = 0; i < M; i++) b[i] *= r, r *= zeta;
    ntt(b);
    copy(begin(b), end(b), back_inserter(a));
  }
};

template <typename mint>
struct FormalPowerSeries : vector<mint> {
  using vector<mint>::vector;
  using FPS = FormalPowerSeries;

  FPS &operator+=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  FPS &operator+=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  FPS &operator-=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  FPS &operator-=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= r;
    return *this;
  }

  FPS &operator*=(const mint &v) {
    for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
    return *this;
  }

  FPS &operator/=(const FPS &r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    if ((int)r.size() <= 64) {
      FPS f(*this), g(r);
      g.shrink();
      mint coeff = g.back().inverse();
      for (auto &x : g) x *= coeff;
      int deg = (int)f.size() - (int)g.size() + 1;
      int gs = g.size();
      FPS quo(deg);
      for (int i = deg - 1; i >= 0; i--) {
        quo[i] = f[i + gs - 1];
        for (int j = 0; j < gs; j++) f[i + j] -= quo[i] * g[j];
      }
      *this = quo * coeff;
      this->resize(n, mint(0));
      return *this;
    }
    return *this = ((*this).rev().pre(n) * r.rev().inv(n)).pre(n).rev();
  }

  FPS &operator%=(const FPS &r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }

  FPS operator+(const FPS &r) const { return FPS(*this) += r; }
  FPS operator+(const mint &v) const { return FPS(*this) += v; }
  FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
  FPS operator-(const mint &v) const { return FPS(*this) -= v; }
  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
  FPS operator*(const mint &v) const { return FPS(*this) *= v; }
  FPS operator/(const FPS &r) const { return FPS(*this) /= r; }
  FPS operator%(const FPS &r) const { return FPS(*this) %= r; }
  FPS operator-() const {
    FPS ret(this->size());
    for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  void shrink() {
    while (this->size() && this->back() == mint(0)) this->pop_back();
  }

  FPS rev() const {
    FPS ret(*this);
    reverse(begin(ret), end(ret));
    return ret;
  }

  FPS dot(FPS r) const {
    FPS ret(min(this->size(), r.size()));
    for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  FPS pre(int sz) const {
    return FPS(begin(*this), begin(*this) + min((int)this->size(), sz));
  }

  FPS operator>>(int sz) const {
    if ((int)this->size() <= sz) return {};
    FPS ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  FPS operator<<(int sz) const {
    FPS ret(*this);
    ret.insert(ret.begin(), sz, mint(0));
    return ret;
  }

  FPS diff() const {
    const int n = (int)this->size();
    FPS ret(max(0, n - 1));
    mint one(1), coeff(1);
    for (int i = 1; i < n; i++) {
      ret[i - 1] = (*this)[i] * coeff;
      coeff += one;
    }
    return ret;
  }

  FPS integral() const {
    const int n = (int)this->size();
    FPS ret(n + 1);
    ret[0] = mint(0);
    if (n > 0) ret[1] = mint(1);
    auto mod = mint::get_mod();
    for (int i = 2; i <= n; i++) ret[i] = (-ret[mod % i]) * (mod / i);
    for (int i = 0; i < n; i++) ret[i + 1] *= (*this)[i];
    return ret;
  }

  mint eval(mint x) const {
    mint r = 0, w = 1;
    for (auto &v : *this) r += w * v, w *= x;
    return r;
  }

  FPS log(int deg = -1) const {
    assert((*this)[0] == mint(1));
    if (deg == -1) deg = (int)this->size();
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  FPS pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();
    if (deg == -1) deg = n;
    for (int i = 0; i < n; i++) {
      if ((*this)[i] != mint(0)) {
        if (i * k > deg) return FPS(deg, mint(0));
        mint rev = mint(1) / (*this)[i];
        FPS ret =
            (((*this * rev) >> i).log(deg) * k).exp(deg) * ((*this)[i].pow(k));
        ret = (ret << (i * k)).pre(deg);
        if ((int)ret.size() < deg) ret.resize(deg, mint(0));
        return ret;
      }
    }
    return FPS(deg, mint(0));
  }

  static void *ntt_ptr;
  static void set_fft();
  FPS &operator*=(const FPS &r);
  void ntt();
  void intt();
  void ntt_doubling();
  static int ntt_pr();
  FPS inv(int deg = -1) const;
  FPS exp(int deg = -1) const;
};
template <typename mint>
void *FormalPowerSeries<mint>::ntt_ptr = nullptr;

template <typename mint>
void FormalPowerSeries<mint>::set_fft() {
  if (!ntt_ptr) ntt_ptr = new NTT<mint>;
}

template <typename mint>
FormalPowerSeries<mint> &FormalPowerSeries<mint>::operator*=(
    const FormalPowerSeries<mint> &r) {
  if (this->empty() || r.empty()) {
    this->clear();
    return *this;
  }
  set_fft();
  auto ret = static_cast<NTT<mint> *>(ntt_ptr)->multiply(*this, r);
  return *this = FormalPowerSeries<mint>(ret.begin(), ret.end());
}

template <typename mint>
void FormalPowerSeries<mint>::ntt() {
  set_fft();
  static_cast<NTT<mint> *>(ntt_ptr)->ntt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::intt() {
  set_fft();
  static_cast<NTT<mint> *>(ntt_ptr)->intt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::ntt_doubling() {
  set_fft();
  static_cast<NTT<mint> *>(ntt_ptr)->ntt_doubling(*this);
}

template <typename mint>
int FormalPowerSeries<mint>::ntt_pr() {
  set_fft();
  return static_cast<NTT<mint> *>(ntt_ptr)->pr;
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::inv(int deg) const {
  assert((*this)[0] != mint(0));
  if (deg == -1) deg = (int)this->size();
  FormalPowerSeries<mint> res(deg);
  res[0] = {mint(1) / (*this)[0]};
  for (int d = 1; d < deg; d <<= 1) {
    FormalPowerSeries<mint> f(2 * d), g(2 * d);
    for (int j = 0; j < min((int)this->size(), 2 * d); j++) f[j] = (*this)[j];
    for (int j = 0; j < d; j++) g[j] = res[j];
    f.ntt();
    g.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = 0; j < d; j++) f[j] = 0;
    f.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = d; j < min(2 * d, deg); j++) res[j] = -f[j];
  }
  return res.pre(deg);
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::exp(int deg) const {
  using fps = FormalPowerSeries<mint>;
  assert((*this).size() == 0 || (*this)[0] == mint(0));
  if (deg == -1) deg = this->size();

  fps inv;
  inv.reserve(deg + 1);
  inv.push_back(mint(0));
  inv.push_back(mint(1));

  auto inplace_integral = [&](fps &F) -> void {
    const int n = (int)F.size();
    auto mod = mint::get_mod();
    while ((int)inv.size() <= n) {
      int i = inv.size();
      inv.push_back((-inv[mod % i]) * (mod / i));
    }
    F.insert(begin(F), mint(0));
    for (int i = 1; i <= n; i++) F[i] *= inv[i];
  };

  auto inplace_diff = [](fps &F) -> void {
    if (F.empty()) return;
    F.erase(begin(F));
    mint coeff = 1, one = 1;
    for (int i = 0; i < (int)F.size(); i++) {
      F[i] *= coeff;
      coeff += one;
    }
  };

  fps b{1, 1 < (int)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
  for (int m = 2; m < deg; m *= 2) {
    auto y = b;
    y.resize(2 * m);
    y.ntt();
    z1 = z2;
    fps z(m);
    for (int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
    z.intt();
    fill(begin(z), begin(z) + m / 2, mint(0));
    z.ntt();
    for (int i = 0; i < m; ++i) z[i] *= -z1[i];
    z.intt();
    c.insert(end(c), begin(z) + m / 2, end(z));
    z2 = c;
    z2.resize(2 * m);
    z2.ntt();
    fps x(begin(*this), begin(*this) + min<int>(this->size(), m));
    x.resize(m);
    inplace_diff(x);
    x.push_back(mint(0));
    x.ntt();
    for (int i = 0; i < m; ++i) x[i] *= y[i];
    x.intt();
    x -= b.diff();
    x.resize(2 * m);
    for (int i = 0; i < m - 1; ++i) x[m + i] = x[i], x[i] = mint(0);
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
    x.intt();
    x.pop_back();
    inplace_integral(x);
    for (int i = m; i < min<int>(this->size(), 2 * m); ++i) x[i] += (*this)[i];
    fill(begin(x), begin(x) + m, mint(0));
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];
    x.intt();
    b.insert(end(b), begin(x) + m, end(x));
  }
  return fps{begin(b), begin(b) + deg};
}

using fps = FormalPowerSeries<LazyMontgomeryModInt<998244353>>;

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n, m;
  do {
    n = gen.uniform<int>(1, N_MAX);
    m = gen.uniform<int>(1, N_MAX);
  } while (n < m);

  auto get_fps = [&](int len) -> fps {
    fps res(len);
    for (int i = 0; i < len; i++) {
      res[i] = gen.uniform<int>((i == len - 1), MOD - 1);
    }
    return res;
  };

  auto dump = [&](fps &f) -> void {
    int len = f.size();
    for (int i = 0; i < len; i++) {
      printf("%d", f[i].get());
      if (i != len - 1) printf(" ");
    }
    printf("\n");
    return;
  };

  // deg(r) = 0
  fps g = get_fps(m);
  fps q = get_fps(n - m + 1);
  fps f = q * g;
  assert((int)f.size() == n and f.back() != 0);

  printf("%d %d\n", n, m);
  dump(f);
  dump(g);
  return 0;
}
