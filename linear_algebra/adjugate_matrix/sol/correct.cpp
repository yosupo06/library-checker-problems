// Author: Dmytro Fedoriaka

#include <cinttypes>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>

struct Random {
  private:
    // Use xoshiro256**
    // References: http://xoshiro.di.unimi.it/xoshiro256starstar.c
    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    std::array<uint64_t, 4> s;

    uint64_t next() {
        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;

        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;

        s[3] = rotl(s[3], 45);

        return result_starstar;
    }

    // random choice from [0, upper]
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            // b = 00..0011..11
            return next() & upper;
        }
        int lg = 63 - __builtin_clzll(upper);
        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
        while (true) {
            uint64_t r = next() & mask;
            if (r <= upper)
                return r;
        }
    }

  public:
    Random(uint64_t seed = 0) {
        // Use splitmix64
        // Reference: http://xoshiro.di.unimi.it/splitmix64.c
        for (int i = 0; i < 4; i++) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    // random choice from [lower, upper]
    template <class T>
    T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    // random choice from false or true
    bool uniform_bool() { return uniform(0, 1) == 1; }

    // random choice from [0.0, 1.0]
    double uniform01() {
        uint64_t v = next(1ULL << 63);
        return double(v) / (1ULL << 63);
    }

    // random choice non-empty sub-interval from interval [lower, upper)
    // equal: random choice 2 disjoint elements from [lower, upper]
    template <class T>
    std::pair<T, T> uniform_pair(T lower, T upper) {
        assert(upper - lower >= 1);
        T a, b;
        do {
            a = uniform(lower, upper);
            b = uniform(lower, upper);
        } while (a == b);
        if (a > b) std::swap(a, b);
        return {a, b};
    }

    // generate random lower string that length = n
    std::string lower_string(size_t n) {
        std::string res = "";
        for (size_t i = 0; i < n; i++) {
            res += uniform('a', 'z');
        }
        return res;
    }

    // random shuffle
    template <class Iter>
    void shuffle(Iter first, Iter last) {
        if (first == last) return;
        // Reference and edit:
        // cpprefjp - C++日本語リファレンス
        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)
        int len = 1;
        for (auto it = first + 1; it != last; it++) {
            len++;
            int j = uniform(0, len - 1);
            if (j != len - 1)
                iter_swap(it, first + j);
        }
    }

    // generate random permutation that length = n
    template <class T>
    std::vector<T> perm(size_t n) {
        std::vector<T> idx(n);
        std::iota(idx.begin(), idx.end(), T(0));
        shuffle(idx.begin(), idx.end());
        return idx;
    }

    // random choise n elements from [lower, upper]
    template <class T>
    std::vector<T> choice(size_t n, T lower, T upper) {
        assert(T(n) <= upper - lower + 1);
        std::set<T> res;
        while (res.size() < n) res.insert(uniform(lower, upper));
        return {res.begin(), res.end()};
    }
} global_gen;

using namespace std;

int64_t MOD = 998244353;
struct IntMod {
  int64_t v;
  IntMod() : v(0) {}
  IntMod(int64_t v_) : v(v_) {if((uint64_t)v>=(uint64_t)MOD){v%=MOD;if(v<0)v+=MOD;}}
  inline IntMod operator + (const IntMod& y) const {IntMod a(*this); a+=y; return a;}
  inline IntMod operator - (const IntMod& y) const {IntMod a(*this); a-=y; return a;}
  inline IntMod operator * (const IntMod& y) const {return {v*y.v};}
  inline IntMod pow(int64_t y) const {IntMod a(1),m(v);while(y!=0){if(y&1){a=a*m;}m=m*m;y>>=1;}return a;}
  inline IntMod inverse() const {
    int64_t g=MOD,r=v,x=0,y=1;
    while(r!=0){int64_t q=g/r;g%=r;swap(g,r);x-=q*y;swap(x,y);}
    return IntMod(x+(x<0)*MOD);
  }
  bool operator == (const IntMod& y) const {return v==y.v;}
  bool operator != (const IntMod& y) const {return v!=y.v;}
  inline void operator += (const IntMod& y) {(v+=y.v)>=MOD && (v-=MOD);}
  inline void operator -= (const IntMod& y) {(v-=y.v)<0 && (v+=MOD);}
  inline void operator *= (const IntMod& y) {v*=y.v; v%=MOD;}
};
inline IntMod operator / (const IntMod& x, const IntMod& y) {return x * y.inverse();}

template <typename T>
class SquareMatrix {
 public:
  SquareMatrix(size_t n) : n_(n) { data_.resize(n * n); }
  static SquareMatrix<T> Read() {
    size_t n;
    scanf("%zu", &n);
    SquareMatrix ans(n);
    for (size_t i = 0; i < n * n; ++i) scanf("%" SCNd64, &ans.data_[i].v);
    return ans;
  }
  static SquareMatrix<T> MakeZeroMatrix(size_t n) {
    SquareMatrix ans(n);
    ans.data_.assign(n * n, 0);
    return ans;
  }

  SquareMatrix<T> AdjointToMinors() const {
    SquareMatrix ans(n_);
    for (size_t i = 0; i < n_; i++) {
      for (size_t j = 0; j < n_; j++) {
        T val = Get(j, i);
        if ((i + j) % 2 == 1) val *= -1;
        ans.Set(i, j, val);
      }
    }
    return ans;
  }

  void MulByScalar(T k) {
    for (size_t i = 0; i < n_ * n_; ++i) data_[i] *= k;
  }

  void Print() const {
    for (size_t i = 0; i < n_; i++) {
      for (size_t j = 0; j < n_; j++) {
        printf("%" SCNd64 "%c", data_[i * n_ + j].v, " \n"[j + 1 == n_]);
      }
    }
  }

  int GetN() const { return n_; }
  T Get(int i, int j) const { return data_[i * n_ + j]; }
  void Set(int i, int j, T value) { data_[i * n_ + j] = value; }

 private:
  size_t n_;
  vector<T> data_;
};

class GaussEliminator {
 public:
  // For non-degenrate matrix, finds determinant and inverse.
  // For degenerate matrix, finds rank.
  void Run(const SquareMatrix<IntMod>& mx) {
    int n = mx.GetN();
    n_ = n;
    row_size_ = 2 * n;

    rows_.assign(n, vector<int64_t>(2 * n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) rows_[i][j] = mx.Get(i, j).v;
      rows_[i][n + i] = 1;
    }
    det_inv_ = 1;

    // Forward pass.
    int row_idx = 0;
    for (int col_idx = 0; col_idx < n; col_idx++) {
      if (rows_[row_idx][col_idx] == 0) {
        int row_to_swap = -1;
        for (int j = row_idx + 1; j < n_; j++) {
          if (rows_[j][col_idx] != 0) {
            row_to_swap = j;
            break;
          }
        }
        if (row_to_swap == -1) {
          // Matrix is degenerate, but carry on because we want to know rank.
          continue;
        }
        SwapRows(row_idx, row_to_swap);
      }

      MulRowBy(row_idx, IntMod(rows_[row_idx][col_idx]).inverse().v);
      for (int j = row_idx + 1; j < n; j++) {
        AddRows(j, row_idx, -rows_[j][col_idx]);
      }
      row_idx++;
    }

    // Check if matrix is degenarate, in which case only compute rank.
    rank_ = row_idx;
    if (rank_ != n) {
      assert(rank_ < n);
      return;
    }

    // Backward pass.
    for (int i = n - 1; i > 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        AddRows(j, i, -rows_[j][i]);
      }
    }
  }

  SquareMatrix<IntMod> GetInverse() {
    assert(rank_ == n_);
    SquareMatrix<IntMod> ans(n_);
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < n_; j++) {
        ans.Set(i, j, IntMod(rows_[i][n_ + j]));
      }
    }
    return ans;
  }

  IntMod GetDeterminant() {
    return rank_ == n_ ? IntMod(det_inv_).inverse() : IntMod(0);
  }

  int GetRank() { return rank_; }

 private:
  // rows[i1] += k*rows[i2]
  void AddRows(size_t i1, size_t i2, int64_t k) {
    // assert(i1 != i2);
    if (k == 0) return;
    int64_t* ptr1 = &(rows_[i1][0]);
    int64_t* ptr1_end = ptr1 + row_size_;
    const int64_t* ptr2 = &(rows_[i2][0]);
    while (ptr1 != ptr1_end) {
      *ptr1 = (*ptr1 + k * (*ptr2)) % MOD;
      ptr1++;
      ptr2++;
    }
  }

  void SwapRows(size_t i1, size_t i2) {
    // assert(i1 != i2);
    det_inv_ *= -1;
    swap(rows_[i1], rows_[i2]);
  }

  void MulRowBy(int i, int64_t k) {
    assert(k != 0);
    det_inv_ = (det_inv_ * k) % MOD;
    int64_t* ptr1 = &(rows_[i][0]);
    int64_t* ptr1_end = ptr1 + row_size_;
    while (ptr1 != ptr1_end) {
      *ptr1 = (*ptr1 * k) % MOD;
      ptr1++;
    }
  }

  vector<vector<int64_t>> rows_;
  int64_t det_inv_;
  int rank_ = -1;
  int n_, row_size_;
};

SquareMatrix<IntMod> GetAdjoint(const SquareMatrix<IntMod>& A) {
  int n = A.GetN();
  GaussEliminator ge;

  SquareMatrix<IntMod> A_ext(n + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A_ext.Set(i, j, A.Get(i, j));
    }
  }
  for (int i = 0; i < n + 1; i++) {
    A_ext.Set(n, i, IntMod(global_gen.uniform<int64_t>(0, MOD - 1)));
    A_ext.Set(i, n, IntMod(global_gen.uniform<int64_t>(0, MOD - 1)));
  }
  ge.Run(A_ext);
  if (ge.GetRank() != n + 1) {
    return SquareMatrix<IntMod>::MakeZeroMatrix(n);
  }

  SquareMatrix<IntMod> A2 = ge.GetInverse();  // A_ext^-1.
  IntMod x_hat = A2.Get(n, n);
  SquareMatrix<IntMod> ans(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans.Set(i, j, x_hat * A2.Get(i, j) - A2.Get(i, n) * A2.Get(n, j));
    }
  }
  ans.MulByScalar(ge.GetDeterminant());
  return ans;
}

int32_t main() {
  SquareMatrix<IntMod> A = SquareMatrix<IntMod>::Read();
  SquareMatrix<IntMod> M = GetAdjoint(A);
  M.Print();

  return 0;
}
