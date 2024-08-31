#include <iostream>
#include <vector>
#include "../params.h"

using namespace std;

int main() {
  int n = N_MAX;
  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { a[i][j] = (1 + i) * (1 + j); }
  }

  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d", a[i][j]);
      if (j != n - 1) printf(" ");
    }
    printf("\n");
  }
  return 0;
}
