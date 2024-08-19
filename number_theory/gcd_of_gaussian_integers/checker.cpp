#include <vector>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  setName("compare sequences of tokens");
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();

  for (int t = 0; t < T; ++t) {
    int ouf_a = ouf.readInt();
    int ouf_b = ouf.readInt();
    int ans_a = ans.readInt();
    int ans_b = ans.readInt();
    bool ok = 0;
    for (int i = 0; i < 4; ++i) {
      tie(ans_a, ans_b) = make_pair(ans_b, -ans_a);
      if (ouf_a == ans_a && ouf_b == ans_b) ok = 1;
    }
    if (!ok) { quitf(_wa, "wa, gcd is not correct"); }
  }
  quitf(_ok, "OK");
  return 0;
}
