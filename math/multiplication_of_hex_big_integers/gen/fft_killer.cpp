#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "random.h"
#include "../params.h"
#include "../base.hpp"

using ll = long long;

ll TEN(int x) { return (x == 0 ? 1 : 10 * TEN(x - 1)); }

// {number, 10^n}
pair<bigint, bigint> dfs(vector<ll> digits, ll base)
{
  const int N = digits.size();
  if (N == 1)
  {
    return {bigint(digits[0]), bigint(base)};
  };
  int M = N / 2;
  auto [x1, pow1] = dfs({digits.begin(), digits.begin() + M}, base);
  auto [x2, pow2] = dfs({digits.begin() + M, digits.end()}, base);
  return {x1 * pow2 + x2, pow1 * pow2};
}

bigint make_num(Random &gen, int N, ll X, ll Y)
{
  vector<ll> digits(N);

  for (int i = 0; i < N; ++i)
  {
    ll y = gen.uniform<int>(Y - 2, Y - 1);
    // x*Y+y < X
    ll x_max = (X - 1 - y) / Y;
    ll x = gen.uniform<int>(0, x_max);
    digits[i] = x * Y + y;
  }
  return dfs(digits, X).first;
}

// https://github.com/yosupo06/library-checker-problems/pull/1020#issuecomment-1663795976
int main(int, char *argv[])
{
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<string> A, B;

  vector<ll> BASE = {TEN(9), 1LL << 32};
  vector<ll> MOD = {1 << 15, 1 << 16};

  ll X = BASE[seed % 2];
  ll Y = MOD[seed % 2];
  ll N = floor(LOG_16_A_AND_B_MAX / log2(X) / 4);

  bigint a = make_num(gen, N, X, Y);
  bigint b = make_num(gen, N, X, Y);

  A.emplace_back(a.to_string());
  B.emplace_back(b.to_string());

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++)
  {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
