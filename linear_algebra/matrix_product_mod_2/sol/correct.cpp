#include <cstdio>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX = 4096 + 10;

using BS = bitset<MAX>;

BS A[MAX];
BS B[MAX];
BS C[MAX];

char BUF[MAX];

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  for (int i = 0; i < N; ++i) {
    scanf("%s", BUF);
    for (int j = 0; j < M; ++j) { A[i][j] = (BUF[j] - '0'); }
  }

  for (int j = 0; j < M; ++j) {
    scanf("%s", BUF);
    for (int k = 0; k < K; ++k) { B[j][k] = (BUF[k] - '0'); }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      // C[i][.] <- A[i][j] B[j][.]
      if (A[i][j]) C[i] ^= B[j];
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int k = 0; k < K; ++k) { printf("%d", 1 * C[i][k]); }
    printf("\n");
  }
}
