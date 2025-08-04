#include <bits/stdc++.h>

using namespace std;

void solve() {
  int Q;
  cin >> Q;

  deque<int> que;
  for (int q = 0; q < Q; ++q) {
    int t, x;
    cin >> t;
    if (t == 0) {
      cin >> x;
      que.push_front(x);
    }
    if (t == 1) {
      cin >> x;
      que.push_back(x);
    }
    if (t == 2) {
      assert(!que.empty());
      que.pop_front();
    }
    if (t == 3) {
      assert(!que.empty());
      que.pop_back();
    }
    if (t == 4) {
      cin >> x;
      assert(0 <= x && x < int(que.size()));
      cout << que[x] << '\n';
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  solve();
}