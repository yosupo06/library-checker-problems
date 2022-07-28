#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

constexpr int MOD = 998244353;
int mul(int a, int b){
    return static_cast<int>(static_cast<unsigned long long>(a) * b % MOD);
}
int main() {
    int n;
    scanf("%d", &n);
    assert(n <= 14);
    const int N = 1 << n, mask = N - 1;
    vector<int> a(N), b(N), c(N);
    for(int& i : a) scanf("%d", &i);
    for(int& i : b) scanf("%d", &i);
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
        const int k = (i * j) & mask;
        c[k] += mul(a[i], b[j]);
        if(c[k] >= MOD) c[k] -= MOD;
    }
    for(int i = 0; i < N; i++) printf("%d%c", c[i], " \n"[i + 1 == N]);
}
