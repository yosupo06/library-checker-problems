#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define fi first
#define se second

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

struct Rollback_Mo {
  vc<pair<int, int>> LR;
  void add(int L, int R) { LR.emplace_back(L, R); }

  template <typename AL, typename AR, typename F1, typename F2, typename F3,
            typename O>
  void calc(AL add_left, AR add_right, F1 reset, F2 save, F3 rollback,
            O query) {
    const int Q = len(LR);
    if (Q == 0) return;
    int N = 0;
    for (auto &&[L, R]: LR) chmax(N, R);
    const int b_num = sqrt(Q);
    const int b_sz = ceil(N, b_num);
    vvc<int> QID((N - 1) / b_sz + 1);
    // 左端の属するブロックで分類
    // 左端と右端が同じブロックに属するものは、先に処理してしまう。
    auto naive = [&](int qid) -> void {
      save();
      auto [L, R] = LR[qid];
      FOR(i, L, R) add_right(i);
      query(qid);
      rollback();
    };

    FOR(qid, Q) {
      auto [L, R] = LR[qid];
      int iL = L / b_sz, iR = R / b_sz;
      if (iL == iR) {
        naive(qid);
        continue;
      }
      QID[iL].eb(qid);
    }

    FOR(iL, len(QID)) {
      auto &I = QID[iL];
      if (I.empty()) continue;
      sort(all(I),
           [&](auto &a, auto &b) -> bool { return LR[a].se < LR[b].se; });
      int LMAX = 0;
      for (auto &&qid: I) {
        auto [L, R] = LR[qid];
        chmax(LMAX, L);
      }
      reset();
      int l = LMAX, r = LMAX;
      for (auto &&qid: I) {
        auto [L, R] = LR[qid];
        while (r < R) add_right(r++);
        save();
        while (L < l) add_left(--l);
        query(qid);
        rollback();
        l = LMAX;
      }
    }
  }
};

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  vc<int> A(N);
  FOR(i, N) { scanf("%d", &A[i]); }

  vc<int> key = A;
  UNIQUE(key);
  for (auto &x: A) x = LB(key, x);

  Rollback_Mo mo;
  FOR(Q) {
    int L, R;
    scanf("%d %d", &L, &R);
    mo.add(L, R);
  }

  int K = len(key);
  vc<int> FREQ(K);
  int max_freq = 0, argmax = 0;
  vc<pair<int, int>> ANS(Q);

  vc<int> history;
  int save_time = 0;
  int save_max_freq = 0, save_argmax = 0;
  auto add = [&](int i) -> void {
    int x = A[i];
    FREQ[x]++;
    if (chmax(max_freq, FREQ[x])) argmax = x;
    history.eb(x);
  };
  auto reset = [&]() -> void {
    while (len(history)) {
      int x = POP(history);
      FREQ[x]--;
    }
    max_freq = 0, argmax = 0;
  };
  auto save = [&]() -> void {
    save_time = len(history);
    save_max_freq = max_freq, save_argmax = argmax;
  };
  auto rollback = [&]() -> void {
    while (len(history) > save_time) {
      int x = POP(history);
      FREQ[x]--;
    }
    max_freq = save_max_freq, argmax = save_argmax;
  };
  auto query = [&](int q) -> void { ANS[q] = {key[argmax], max_freq}; };
  mo.calc(add, add, reset, save, rollback, query);
  for (auto &[a, b]: ANS) printf("%d %d\n", a, b);
}

signed main() {
  solve();
  return 0;
}
