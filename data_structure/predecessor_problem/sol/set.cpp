// std::insert
// O((N + Q) log N)

#include <cassert>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct naive_Predecessor {
  int N;
  set<int> st;
  naive_Predecessor(int n) : N(n) {}
  void insert(int k) { st.insert(k); }
  void reset(int k) { st.erase(k); }
  int get(int k) const { return st.find(k) != st.end(); }
  int find_next(int k) {
    auto it = st.lower_bound(k);
    return it == st.end() ? -1 : *it;
  }
  int find_prev(int k) {
    auto it = st.upper_bound(k);
    return it == st.begin() ? -1 : *(--it);
  }
};

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  char c = getchar();
  naive_Predecessor dict(N);
  for (int i = 0; i < N; i++) {
    c = getchar();
    if (c == '1') dict.insert(i);
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
