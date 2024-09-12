#include "testlib.h"

#include <vector>
#include <tuple>
#include <cassert>

using namespace std;
using ll = long long;

ll read_ans_cnt(ll N, InStream& stream) {
  ll n = stream.readInt();
  vector<pair<ll, ll>> ANS(n);
  for (int i = 0; i < n; ++i) {
    ll x = stream.readLong(0LL, 1LL << 30);
    ll y = stream.readLong(0LL, 1LL << 30);
    stream.ensure(x * x + y * y == N);
    ANS[i] = {x, y};
  }
  // check distinct
  sort(ANS.begin(), ANS.end());
  for (int i = 0; i < n - 1; ++i) stream.ensure(ANS[i] != ANS[i + 1]);
  return n;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int Q = inf.readInt();
  for (int q = 0; q < Q; ++q) {
    ll N = inf.readLong();
    ll ans_cnt = read_ans_cnt(N, ans);
    ll ouf_cnt = read_ans_cnt(N, ouf);
    if (ans_cnt > ouf_cnt) {
      quitf(_wa, "Not found all solutions. N=%lld, ans_cnt=%lld, ouf_cnt=%lld", N, ans_cnt, ouf_cnt);
    } else if (ans_cnt < ouf_cnt) {
      quitf(_fail, "Writer does not find all solutions! N=%lld, ans_cnt=%lld, ouf_cnt=%lld", N, ans_cnt, ouf_cnt);
    }
  }
  quitf(_ok, "OK");
}
