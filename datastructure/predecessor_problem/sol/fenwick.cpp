// Fenwick Tree (construct in linear time)
// O(N + Q log N)

#include <cassert>
#include <string>
#include <vector>

using namespace std;

struct BIT_Predecessor {
  int N, lg;
  vector<int> data;
  BIT_Predecessor() = default;
  BIT_Predecessor(int size) { init(size); }

  void init(int size) {
    N = size + 2;  // memorize [0, N + 1]
    data.assign(N + 1, 0);
    lg = 31 - __builtin_clz(N);
  }
  void insert(int k) {
    if (get(k) == 1) return;
    for (++k; k <= N; k += k & -k) data[k] += 1;
  }
  void reset(int k) {
    if (get(k) == 0) return;
    for (++k; k <= N; k += k & -k) data[k] -= 1;
  }
  int sum(int k) const {
    int ret = 0;
    for (++k; k; k -= k & -k) ret += data[k];
    return ret;
  }
  int get(int k) const { return sum(k) - sum(k - 1); }

  int find_next(int i) const {
    int w = sum(i - 1);
    int x = 0;
    for (int k = 1 << lg; k; k >>= 1) {
      if (x + k <= N && data[x + k] <= w) {
        w -= data[x + k];
        x += k;
      }
    }
    if (x == N) return -1;
    return x;
  }

  int find_prev(int i) const {
    int w = sum(i) - 1;
    if (w < 0) return -1;
    int x = 0;
    for (int k = 1 << lg; k; k >>= 1) {
      if (x + k <= N && data[x + k] <= w) {
        w -= data[x + k];
        x += k;
      }
    }
    return x;
  }
};

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  char c = getchar();

  BIT_Predecessor dict(N);
  for (int i = 0; i < N; i++) {
    c = getchar();
    int j = i + 1;
    dict.data[j] += c - '0';
    int k = j + (j & -j);
    if (k <= dict.N) dict.data[k] += dict.data[j];
  }

  while (Q--) {
    int c, k;
    scanf("%d %d\n", &c, &k);
    if (c == 0) {
      dict.insert(k);
    } else if (c == 1) {
      dict.reset(k);
    } else if (c == 2) {
      printf("%d\n", dict.get(k));
    } else if (c == 3) {
      printf("%d\n", dict.find_next(k));
    } else if (c == 4) {
      printf("%d\n", dict.find_prev(k));
    }
  }
}
