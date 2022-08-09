// O(p^2) 時間の前計算のもと、O(log n) 時間
struct Stirling_Number_Query {
  const int p;
  vector<vector<int>> MEMO_C;
  vector<vector<int>> MEMO_S1;
  vector<vector<int>> MEMO_S2;

  Stirling_Number_Query(int p, bool first_kind = true, bool second_kind = true)
      : p(p) {
    build_C();
    if (first_kind) build_S1();
    if (second_kind) build_S2();
  }

  int C(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    int res = 1;
    while (n) {
      int i = n % p, j = k % p;
      if (j > i) return 0;
      res = res * MEMO_C[i][j] % p;
      n /= p;
      k /= p;
    }
    return res;
  }

  int S1(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    ll i = n / p;
    int j = n % p;
    if (i > k) return 0;
    ll a = (k - i) / (p - 1);
    int b = (k - i) % (p - 1);
    if (b == 0 && j > 0) {
      b += (p - 1);
      a -= 1;
    }
    if (a < 0 || i < a || b > j) return 0;
    int x = C(i, a);
    int y = MEMO_S1[j][b];
    int res = x * y % p;
    if ((i + a) % 2 == 1 && res) { res = p - res; }
    return res;
  }

  int S2(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    ll i = k / p;
    int j = k % p;
    if (n < i) return 0;
    ll a = (n - i) / (p - 1);
    int b = (n - i) - (p - 1) * a;
    if (b == 0) {
      b += p - 1;
      a -= 1;
    }
    if (a < 0 || j > b) return 0;
    if (b < p - 1) { return C(a, i) * MEMO_S2[b][j] % p; }
    if (j == 0) return C(a, i - 1);
    return C(a, i) * MEMO_S2[p - 1][j] % p;
  }

private:
  void build_C() {
    auto& A = MEMO_C;
    A.resize(p);
    A[0] = {1};
    for (int i = 1; i < p; ++i) {
      A[i] = A[i - 1];
      A[i].emplace_back(0);
      for (int j = 1; j <= i; ++j) {
        A[i][j] += A[i - 1][j - 1];
        if (A[i][j] >= p) A[i][j] -= p;
      }
    }
  }

  void build_S1() {
    auto& A = MEMO_S1;
    A.resize(p);
    A[0] = {1};
    for (int i = 1; i < p; ++i) {
      A[i].assign(i + 1, 0);
      for (int j = 0; j <= i; ++j) {
        if (j) A[i][j] += A[i - 1][j - 1];
        if (j < i) A[i][j] += A[i - 1][j] * (p - i + 1);
        A[i][j] %= p;
      }
    }
  }

  void build_S2() {
    auto& A = MEMO_S2;
    A.resize(p);
    A[0] = {1};
    for (int i = 1; i < p; ++i) {
      A[i].assign(i + 1, 0);
      for (int j = 0; j <= i; ++j) {
        if (j) A[i][j] += A[i - 1][j - 1];
        if (j < i) A[i][j] += A[i - 1][j] * j;
        A[i][j] %= p;
      }
    }
  }
};