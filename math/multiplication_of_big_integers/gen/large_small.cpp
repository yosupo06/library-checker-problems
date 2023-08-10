#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "random.h"
#include "../params.h"

string make_num(Random& gen, int n, bool negative) {
  string x;
  for (int i = 0; i < n; ++i) { x += char('0' + gen.uniform<int>(0, 9)); }
  if (n >= 2) { x[0] = char('0' + gen.uniform<int>(1, 9)); }
  if (negative && x != "0") { x = "-" + x; }
  return x;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  vector<string> A, B;
  int n1 = LOG_10_A_AND_B_MAX / 10 * 9;
  int n2 = LOG_10_A_AND_B_MAX / 10 * 1;
  A.emplace_back(make_num(gen, n1, n2));
  B.emplace_back(make_num(gen, n2, n1));

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
