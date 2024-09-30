#include <algorithm>
#include <vector>
#include <string>
#include <bitset>
#include "testlib.h"

using namespace std;
using BS = bitset<4096>;

int N, M;
BS A[4096];
BS b;

BS evaluate(BS x) {
  BS y;
  for (int i = 0; i < N; ++i) {
    int cnt = (x & A[i]).count();
    y[i] = cnt % 2;
  }
  return y;
}

int matrix_rank(vector<BS> a) {
  int N = a.size();
  int rk = 0;
  for (int j = 0; j < M; ++j) {
    if (rk == N) break;
    if (!a[rk][j]) {
      for (int i = rk + 1; i < N; ++i) {
        if (a[i][j]) {
          swap(a[rk], a[i]);
          break;
        }
      }
    }
    if (!a[rk][j]) continue;
    for (int i = rk + 1; i < N; ++i) {
      if (a[i][j]) { a[i] ^= a[rk]; }
    }
    ++rk;
  }
  return rk;
}

int get_rank(InStream& stream) {
  int r = stream.readInt(-1, M);
  if (r == -1) return -1;
  vector<BS> mat;

  for (int k = 0; k < r + 1; ++k) {
    string S = stream.readToken();
    stream.ensure(int(S.size()) == M);
    for (auto& ch: S) stream.ensure(ch == '0' || ch == '1');
    BS x;
    for (int j = 0; j < M; ++j) x[j] = (S[j] - '0');
    BS y = evaluate(x);
    if (k == 0) {
      for (int i = 0; i < N; ++i) { stream.ensure(y[i] == b[i]); }
    } else {
      for (int i = 0; i < N; ++i) { stream.ensure(y[i] == false); }
      mat.emplace_back(x);
    }
  }
  stream.ensure(matrix_rank(mat) == r);
  return r;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  // read input
  N = inf.readInt();
  M = inf.readInt();
  for (int i = 0; i < N; ++i) {
    string S = inf.readToken();
    for (int j = 0; j < M; ++j) A[i][j] = (S[j] - '0');
  }
  string S = inf.readToken();
  for (int i = 0; i < N; ++i) b[i] = (S[i] - '0');

  int k_ans = get_rank(ans);
  int k_ouf = get_rank(ouf);

  if (k_ans == -1 && k_ouf == -1) { quitf(_ok, "OK No solution"); }
  if (k_ans != -1 && k_ouf == -1) { quitf(_wa, "WA you cannot find solution"); }
  if (k_ans == -1 && k_ouf != -1) { quitf(_fail, "Judge cannot find solution"); }
  if (k_ans > k_ouf) { quitf(_wa, "There are more solutions"); }
  if (k_ans < k_ouf) { quitf(_fail, "What happened?"); }
  quitf(_ok, "OK");
}
