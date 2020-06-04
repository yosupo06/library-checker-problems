#include "testlib.h"
#include <vector>
#include <set>

int main(int argc, char * argv[])
{
  setName("compare sequences of tokens");
  registerTestlibCmd(argc, argv);

  int L = inf.readInt(); // l
  int R = inf.readInt(); // r
  int M = inf.readInt();
  int max_deg=0;
  std::vector<int> a(M);
  std::vector<int> b(M);
  std::vector<std::vector<int>> cols(R+L);
  std::vector<int> deg(L+R,0);
  for (int i = 0; i < M; i++) {
    a[i] = inf.readInt();
    b[i] = inf.readInt();
    ++deg[a[i]];
    ++deg[b[i]+L];
  }
  for (int &d:deg) max_deg=std::max(max_deg,d);
  int k_ouf = ouf.readInt();  
  if (max_deg != k_ouf) {
    quitf(_wa, "# of color is  - expected: '%d', found '%d'", max_deg, k_ouf);
  }
  for (int i = 0; i < M; i++) {
    int col = ouf.readInt();
    if (!(0<=col && col<max_deg)) {
      quitf(_wa, "color is not in the expected range");
    }
    cols[a[i]].push_back(col);
    cols[b[i]+L].push_back(col);
  }
  for (auto &v:cols) {
    std::set<int> vis;
    for (int &col:v) {
      if (vis.count(col)!=0) {
        quitf(_wa, "coloring is not proper");
      }
      vis.insert(col);
    }
  }
  if (!ouf.seekEof()) {
    quitf(_wa, "extra tokens");
  }
 
  quitf(_ok, "OK");
}
