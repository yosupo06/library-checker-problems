#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }


////////////////////////////////////////////////////////////////////////////////
namespace radix3 {

constexpr int THREE[20] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467};

template <class R> inline void div3(R &a);

template <class R> inline void zero(int q, R *as) {
  memset(as, 0, (2 * THREE[q]) * sizeof(R));
}
template <class R> inline void cpy(int q, R *as, R *bs) {
  memcpy(as, bs, (2 * THREE[q]) * sizeof(R));
}
template <class R> inline void add(int q, R *as, R *bs) {
  for (int j = 0; j < 2 * THREE[q]; ++j) as[j] += bs[j];
}
template <class R> inline void add2(int q, R *as, R *bs) {
  for (int j = 0; j < 2 * THREE[q]; ++j) as[j] += 2 * bs[j];
}
template <class R> inline void mulSet(int q, R *as, R *bs, int r) {
  if (r >= THREE[q + 1]) r -= THREE[q + 1];
  if (r < THREE[q]) {
    memcpy(as + r, bs, (2 * THREE[q] - r) * sizeof(R));
    for (int j = 2 * THREE[q] - r; j < 2 * THREE[q]; ++j) { as[j + r - 2 * THREE[q]] = -bs[j]; as[j + r - THREE[q]] -= bs[j]; }
  } else if (r < 2 * THREE[q]) {
    memcpy(as + r, bs, (2 * THREE[q] - r) * sizeof(R));
    memcpy(as, bs + (THREE[q + 1] - r), (r - THREE[q]) * sizeof(R));
    for (int j = 2 * THREE[q] - r; j < THREE[q]; ++j) { as[j + r - 2 * THREE[q]] -= bs[j]; as[j + r - THREE[q]] = -bs[j]; }
    for (int j = THREE[q]; j < THREE[q + 1] - r; ++j) { as[j + r - 2 * THREE[q]] = -bs[j]; as[j + r - THREE[q]] -= bs[j]; }
  } else {
    memcpy(as, bs + (THREE[q + 1] - r), (r - THREE[q]) * sizeof(R));
    for (int j = 0; j < THREE[q + 1] - r; ++j) { as[j + r - 2 * THREE[q]] -= bs[j]; as[j + r - THREE[q]] = -bs[j]; }
  }
}
template <class R> inline void mulAdd(int q, R *as, R *bs, int r) {
  if (r >= THREE[q + 1]) r -= THREE[q + 1];
  const int j2 = max(2 * THREE[q] - r, 0);
  const int j3 = min(THREE[q + 1] - r, 2 * THREE[q]);
  for (int j = 0; j < j2; ++j) as[j + r] += bs[j];
  for (int j = j2; j < j3; ++j) { as[j + r - 2 * THREE[q]] -= bs[j]; as[j + r - THREE[q]] -= bs[j]; }
  for (int j = j3; j < 2 * THREE[q]; ++j) as[j + r - THREE[q + 1]] += bs[j];
}
template <class R> inline void mulAdd2(int q, R *as, R *bs, int r) {
  if (r >= THREE[q + 1]) r -= THREE[q + 1];
  const int j2 = max(2 * THREE[q] - r, 0);
  const int j3 = min(THREE[q + 1] - r, 2 * THREE[q]);
  for (int j = 0; j < j2; ++j) as[j + r] += 2 * bs[j];
  for (int j = j2; j < j3; ++j) { as[j + r - 2 * THREE[q]] -= 2 * bs[j]; as[j + r - THREE[q]] -= 2 * bs[j]; }
  for (int j = j3; j < 2 * THREE[q]; ++j) as[j + r - THREE[q + 1]] += 2 * bs[j];
}
template <class R> inline void mulSub(int q, R *as, R *bs, int r) {
  if (r >= THREE[q + 1]) r -= THREE[q + 1];
  const int j2 = max(2 * THREE[q] - r, 0);
  const int j3 = min(THREE[q + 1] - r, 2 * THREE[q]);
  for (int j = 0; j < j2; ++j) as[j + r] -= bs[j];
  for (int j = j2; j < j3; ++j) { as[j + r - 2 * THREE[q]] += bs[j]; as[j + r - THREE[q]] += bs[j]; }
  for (int j = j3; j < 2 * THREE[q]; ++j) as[j + r - THREE[q + 1]] -= bs[j];
}
template <class R> inline void mulSub2(int q, R *as, R *bs, int r) {
  if (r >= THREE[q + 1]) r -= THREE[q + 1];
  const int j2 = max(2 * THREE[q] - r, 0);
  const int j3 = min(THREE[q + 1] - r, 2 * THREE[q]);
  for (int j = 0; j < j2; ++j) as[j + r] -= 2 * bs[j];
  for (int j = j2; j < j3; ++j) { as[j + r - 2 * THREE[q]] += 2 * bs[j]; as[j + r - THREE[q]] += 2 * bs[j]; }
  for (int j = j3; j < 2 * THREE[q]; ++j) as[j + r - THREE[q + 1]] -= 2 * bs[j];
}

// DFT of size 3^p over R[y] / (1 + y^(3^q) + y^(2 3^q))
template <class R> void fft(int m, R *as) {
  const int p = m / 2, q = m - m / 2;
  vector<int> ratios(p, 0);
  for (int g = 0; g < p - 1; ++g) ratios[g] = (2 * THREE[q] + 4 * THREE[q - g - 1]) % THREE[q + 1];
  vector<R> work1(2 * THREE[q]), work2(2 * THREE[q]);
  for (int l = p; --l >= 0; ) {
    int prod = 0;
    for (int h = 0, i0 = 0; i0 < THREE[p]; i0 += THREE[l + 1]) {
      for (int i = i0; i < i0 + THREE[l]; ++i) {
        R *a0 = as + 2 * THREE[q] * i;
        R *a1 = as + 2 * THREE[q] * (i + THREE[l]);
        R *a2 = as + 2 * THREE[q] * (i + 2 * THREE[l]);
        mulSet(q, work1.data(), a1, prod);
        mulSet(q, work2.data(), a2, 2 * prod);
        cpy(q, a1, a0);
        mulAdd(q, a1, work1.data(), THREE[q]);
        mulAdd(q, a1, work2.data(), 2 * THREE[q]);
        cpy(q, a2, a0);
        mulAdd(q, a2, work1.data(), 2 * THREE[q]);
        mulAdd(q, a2, work2.data(), THREE[q]);
        add(q, a0, work1.data());
        add(q, a0, work2.data());
      }
      int g = 0;
      for (int hh = ++h; hh % 3 == 0; hh /= 3) ++g;
      if ((prod += ratios[g]) >= THREE[q + 1]) prod -= THREE[q + 1];
    }
  }
}

// inverse DFT of size 3^p over R[y] / (1 + y^(3^q) + y^(2 3^q))
template <class R> void invFft(int m, R *as) {
  const int p = m / 2, q = m - m / 2;
  vector<int> invRatios(p, 0);
  for (int g = 0; g < p - 1; ++g) invRatios[g] = (4 * THREE[q] - 4 * THREE[q - g - 1]) % THREE[q + 1];
  vector<R> work1(2 * THREE[q]), work2(2 * THREE[q]);
  for (int l = 0; l < p; ++l) {
    int prod = 0;
    for (int h = 0, i0 = 0; i0 < THREE[p]; i0 += THREE[l + 1]) {
      for (int i = i0; i < i0 + THREE[l]; ++i) {
        R *a0 = as + 2 * THREE[q] * i;
        R *a1 = as + 2 * THREE[q] * (i + THREE[l]);
        R *a2 = as + 2 * THREE[q] * (i + 2 * THREE[l]);
        cpy(q, work1.data(), a0);
        mulAdd(q, work1.data(), a1, 2 * THREE[q]);
        mulAdd(q, work1.data(), a2, THREE[q]);
        cpy(q, work2.data(), a0);
        mulAdd(q, work2.data(), a1, THREE[q]);
        mulAdd(q, work2.data(), a2, 2 * THREE[q]);
        add(q, a0, a1);
        add(q, a0, a2);
        mulSet(q, a1, work1.data(), prod);
        mulSet(q, a2, work2.data(), 2 * prod);
      }
      int g = 0;
      for (int hh = ++h; hh % 3 == 0; hh /= 3) ++g;
      if ((prod += invRatios[g]) >= THREE[q + 1]) prod -= THREE[q + 1];
    }
  }
  R inv3 = 1;
  for (int l = 0; l < p; ++l) div3(inv3);
  for (int k = 0; k < 2 * THREE[m]; ++k) as[k] *= inv3;
}

// a <- a b mod (1 + x^(3^m) + x^(2 3^m))
template <class R> void inplaceConvolve(int m, R *as, R *bs) {
  if (m <= 3) {
    vector<R> cs(4 * THREE[m] - 1, 0);
    for (int ka = 0; ka < 2 * THREE[m]; ++ka) for (int kb = 0; kb < 2 * THREE[m]; ++kb) cs[ka + kb] += as[ka] * bs[kb];
    for (int k = 4 * THREE[m] - 1; --k >= 2 * THREE[m]; ) {
      cs[k - 2 * THREE[m]] -= cs[k];
      cs[k - THREE[m]] -= cs[k];
    }
    memcpy(as, cs.data(), (2 * THREE[m]) * sizeof(R));
  } else {
    // y := x^(3^p)
    // (R[y] / (1 + y^(3^q) + y^(2 3^q)))[x]
    const int p = m / 2, q = m - m / 2;
    vector<R> as0(2 * THREE[m]), bs0(2 * THREE[m]), as1(2 * THREE[m], 0), bs1(2 * THREE[m], 0);
    for (int j = 0; j < 2 * THREE[q]; ++j) for (int i = 0; i < THREE[p]; ++i) as0[2 * THREE[q] * i + j] = as[THREE[p] * j + i];
    for (int j = 0; j < 2 * THREE[q]; ++j) for (int i = 0; i < THREE[p]; ++i) bs0[2 * THREE[q] * i + j] = bs[THREE[p] * j + i];
    // x <- y^(3^q/3^p) x
    for (int i = 0; i < THREE[p]; ++i) mulAdd(q, as1.data() + 2 * THREE[q] * i, as0.data() + 2 * THREE[q] * i, THREE[q - p] * i);
    for (int i = 0; i < THREE[p]; ++i) mulAdd(q, bs1.data() + 2 * THREE[q] * i, bs0.data() + 2 * THREE[q] * i, THREE[q - p] * i);
    fft(m, as0.data());
    fft(m, bs0.data());
    for (int i = 0; i < THREE[p]; ++i) inplaceConvolve(q, bs0.data() + 2 * THREE[q] * i, as0.data() + 2 * THREE[q] * i);
    invFft(m, bs0.data());
    fft(m, as1.data());
    fft(m, bs1.data());
    for (int i = 0; i < THREE[p]; ++i) inplaceConvolve(q, bs1.data() + 2 * THREE[q] * i, as1.data() + 2 * THREE[q] * i);
    invFft(m, bs1.data());
    zero(m, as);
    for (int i = 0; i < THREE[p]; ++i) {
      // b0 = c0 + c1
      // b1 = y^(3^q/3^p i) c0 + y^(3^q/3^p i + 3^q) c1
      // c0 = (1/3) (2 + y^(3^q)) (-y^(3^q) b0 + y^(-3^q/3^p i) b1)
      // c1 = (1/3) (2 + y^(3^q)) (b0 - y^(-3^q/3^p i) b1)
      R *b0 = bs0.data() + 2 * THREE[q] * i;
      R *b1 = bs1.data() + 2 * THREE[q] * i;
      for (int j = 0; j < 2 * THREE[q]; ++j) div3(b0[j]);
      for (int j = 0; j < 2 * THREE[q]; ++j) div3(b1[j]);
      mulSet(q, as0.data(), b1, THREE[q + 1] - THREE[q - p] * i + THREE[q]);
      mulSub2(q, as0.data(), b0, THREE[q]);
      mulSub(q, as0.data(), b0, 2 * THREE[q]);
      mulAdd2(q, as0.data(), b1, THREE[q + 1] - THREE[q - p] * i);
      mulSet(q, as1.data(), b0, THREE[q]);
      add2(q, as1.data(), b0);
      mulSub2(q, as1.data(), b1, THREE[q + 1] - THREE[q - p] * i);
      mulSub(q, as1.data(), b1, THREE[q + 1] - THREE[q - p] * i + THREE[q]);
      for (int j = 0; j < 2 * THREE[q]; ++j) as[THREE[p] * j + i] += as0[j];
      for (int j = 0; j < 2 * THREE[q] - 1; ++j) as[THREE[p] * j + i + THREE[p]] += as1[j];
      as[i] -= as1[2 * THREE[q] - 1];
      as[i + THREE[m]] -= as1[2 * THREE[q] - 1];
    }
  }
}

template <class R> vector<R> convolve(vector<R> as, vector<R> bs) {
  if (as.empty() || bs.empty()) return {};
  const int len = as.size() + bs.size() - 1;
  int m = 0;
  for (; 2 * THREE[m] < len; ++m) {}
  as.resize(2 * THREE[m], 0);
  bs.resize(2 * THREE[m], 0);
  inplaceConvolve(m, as.data(), bs.data());
  as.resize(len);
  return as;
}

}  // namespace radix3

template <> inline void radix3::div3<unsigned>(unsigned &a) {
  a *= 2863311531U;
}
template <> inline void radix3::div3<unsigned long long>(unsigned long long &a) {
  a *= 12297829382473034411ULL;
}
////////////////////////////////////////////////////////////////////////////////


int main() {
  int N, M;
  for (; ~scanf("%d%d", &N, &M); ) {
    vector<unsigned long long> A(N), B(M);
    for (int i = 0; i < N; ++i) scanf("%llu", &A[i]);
    for (int i = 0; i < M; ++i) scanf("%llu", &B[i]);
    
    const vector<unsigned long long> C = radix3::convolve(A, B);
    assert((int)C.size() == N + M - 1);

    for (int i = 0; i < N + M - 1; ++i) {
      if (i > 0) printf(" ");
      printf("%llu", C[i]);
    }
    puts("");
  }
  return 0;
}
