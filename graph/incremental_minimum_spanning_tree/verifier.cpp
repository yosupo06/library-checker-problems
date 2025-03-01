#include "params.h"
#include "testlib.h"
#include <set>

using namespace std;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, N_MAX);
  inf.readSpace();
  int m = inf.readInt(1, M_MAX);
  inf.readChar('\n');
  set<int> s;
  for (int i = 0; i < m; i++) {
    inf.readInt(0, n - 1);
    inf.readSpace();
    inf.readInt(0, n - 1);
    inf.readSpace();
    int w = inf.readInt(1, W_MAX);
    s.insert(w);
    inf.readChar('\n');
  }
  inf.readEof();
  ensure((int)s.size() == m);

  return 0;
}
