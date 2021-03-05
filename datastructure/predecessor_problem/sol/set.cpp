// std::set
// O((N + Q) log N)

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct naive_Predecessor {
  int N;
  set<int> st;
  naive_Predecessor(int n) : N(n) {}
  void set(int k) { st.insert(k); }
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
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;
  string T;
  cin >> T;

  naive_Predecessor dict(N);
  for (int i = 0; i < N; i++) {
    if (T[i] == '1') dict.set(i);
  }

  while (Q--) {
    int c, k;
    cin >> c >> k;
    if (c == 1) {
      dict.set(k);
    } else if (c == 2) {
      dict.reset(k);
    } else if (c == 3) {
      cout << dict.get(k) << "\n";
    } else if (c == 4) {
      cout << dict.find_next(k) << "\n";
    } else {
      cout << dict.find_prev(k) << "\n";
    }
  }
}
