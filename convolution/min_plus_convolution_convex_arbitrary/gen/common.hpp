
using namespace std;
using ll = long long;

vector<ll> rand_gen(Random& gen, int N, int min_slope, int max_slope) {
  vector<ll> A(N);
  while (1) {
    vector<int> slope(N - 1);
    for (int i = 0; i < N - 1; ++i) {
      slope[i] = gen.uniform<int>(min_slope, max_slope);
    }
    sort(slope.begin(), slope.end());
    for (int i = 0; i < N - 1; ++i) A[i + 1] = A[i] + slope[i];
    ll mi = *(min_element(A.begin(), A.end()));
    ll ma = *(max_element(A.begin(), A.end()));
    if (ma - mi > A_MAX) continue;
    for (int i = 0; i < N; ++i) A[i] -= mi;
    ma -= mi;
    int add = gen.uniform<int>(0, A_MAX - ma);
    for (int i = 0; i < N; ++i) A[i] += add;
    break;
  }
  return A;
}

vector<ll> rand_B(Random& gen, int N) {
  vector<ll> B(N);
  for (int i = 0; i < N; ++i) B[i] = gen.uniform<int>(A_MIN, A_MAX);
  return B;
}

void out(vector<ll>& A, vector<ll>& B) {
  int n = A.size(), m = B.size();
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    if (i) printf(" ");
    printf("%lld", A[i]);
  }
  printf("\n");
  for (int i = 0; i < m; ++i) {
    if (i) printf(" ");
    printf("%lld", B[i]);
  }
  printf("\n");
}