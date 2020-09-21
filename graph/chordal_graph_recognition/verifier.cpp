#include "testlib.h"
#include <set>
#include "params.h"

using namespace std;

int main(int argc, char* argv[])
{
  registerValidation(argc, argv);

  int n = inf.readInt(N_MIN, N_MAX, "n");
  inf.readSpace();
  int m = inf.readInt(M_MIN, M_MAX, "m");
  inf.readChar('\n');

  set<pair<int, int>> edges;
  for (int i = 0; i < m; i++){
    int u = inf.readInt(0, n-1, "u");
    inf.readSpace();
    int v = inf.readInt(0, n-1, "v");
    inf.readChar('\n');
    ensuref(u!=v, "Loop at vertex %d\n", u);
    ensuref(!edges.count({u,v}), "Duplicate edge between %d and %d\n", u, v);
    edges.insert({u,v});
    edges.insert({v,u});
  }
  inf.readEof();
}
