#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <cstdlib>

using namespace std;

void solve() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);

  for (int q = 0; q < Q; ++q) {
    int t, x;
    scanf("%d%d", &t, &x);
    if (t == 0) {
      // insert
      vector<int> nxt;
      for (auto& a: A) {
        if (a < x) nxt.emplace_back(a);
      }
      nxt.emplace_back(x);
      for (auto& a: A) {
        if (x < a) nxt.emplace_back(a);
      }
      swap(A, nxt);
    }

    if (t == 1) {
      // erase
      vector<int> nxt;
      for (auto& a: A) {
        if (a < x) nxt.emplace_back(a);
      }
      for (auto& a: A) {
        if (x < a) nxt.emplace_back(a);
      }
      swap(A, nxt);
    }

    if (t == 2) {
      // x-th
      x = x - 1;
      int ans = (x < int(A.size()) ? A[x] : -1);
      printf("%d\n", ans);
    }

    if (t == 3) {
      int ans = 0;
      for (auto& a: A) ans += (a <= x);
      printf("%d\n", ans);
    }

    if (t == 4) {
      int ans = -1;
      for (auto& a: A) {
        if (a <= x) ans = a;
      }
      printf("%d\n", ans);
    }

    if (t == 5) {
      int ans = -1;
      for (auto& a: A) {
        if (a >= x && ans == -1) ans = a;
      }
      printf("%d\n", ans);
    }
  }
}

signed main() { solve(); }
