#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX, "N");
  inf.readSpace();
  int K = inf.readInt(K_MIN, K_MAX, "N");
  inf.readChar('\n');
  
  vector<int> I;
  vector<int> A;

  for (int k = 0; k < K; ++k) {
    int i = inf.readInt(0, N - 1, "i");
    inf.readSpace();
    int a = inf.readInt(1, MOD - 1, "a");
    inf.readChar('\n');
    
    I.push_back(i);
    A.push_back(a);
  }
  inf.readEof();

  for (int k = 0; k < K - 1; ++k) ensure(I[k] < I[k + 1]);
}
