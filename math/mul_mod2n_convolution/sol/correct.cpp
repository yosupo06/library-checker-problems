#include "../acl.h"
#include <cstdio>
using namespace std;
using Modint = atcoder::modint998244353;

Modint get(){
    int x;
    scanf("%d", &x);
    return Modint::raw(x);
}
void output(const vector<Modint>& c){
    for(int i = 0; i < (int)c.size(); i++){
        printf("%d%c", c[i].val(), " \n"[i + 1 == (int)c.size()]);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    const int N = 1 << n, mask = N - 1;
    vector<Modint> a(N), b(N), c(N);
    for(Modint& i : a) i = get();
    for(Modint& i : b) i = get();

    // pow5[i][j] = (-1) ** i * 5 ** j (mod 2^N), generates all odd numbers
    vector pow5(2, vector(max(1, N >> 2), 0));
    pow5[0][0] = 1;
    for(int i = 1; i < (int)pow5[0].size(); i++) pow5[0][i] = (pow5[0][i - 1] * 5) & mask;
    for(int i = 0; i < (int)pow5[0].size(); i++) pow5[1][i] = -pow5[0][i] & mask;

    // A[i][j][k] = a[2 ** i * (-1) ** j * 5 ** k (mod 2^N)]
    vector<vector<vector<Modint>>> A(n + 1), B(n + 1), C(n + 1);
    for(int i = 0; i < n - 1; i++){
        const int size = N >> (2 + i);
        A[i].assign(2, vector<Modint>(size));
        B[i].assign(2, vector<Modint>(size));
        C[i].assign(2, vector<Modint>(size));
        for(int j = 0; j < 2; j++) for(int k = 0; k < size; k++){
            A[i][j][k] = a[pow5[j][k] << i & mask];
            B[i][j][k] = b[pow5[j][k] << i & mask];
        }
    }

    // fft
    for(int i = 0; i < n - 1; i++){
        auto& x = A[i];
        for(auto& y : x) atcoder::internal::butterfly(y);
        for(int i = 0; i < (int)x[0].size(); i++){
            tie(x[0][i], x[1][i]) = pair{x[0][i] + x[1][i], x[0][i] - x[1][i]};
        }
    }
    for(int i = 0; i < n - 1; i++){
        auto& x = B[i];
        for(auto& y : x) atcoder::internal::butterfly(y);
        for(int i = 0; i < (int)x[0].size(); i++){
            tie(x[0][i], x[1][i]) = pair{x[0][i] + x[1][i], x[0][i] - x[1][i]};
        }
    }
    
    // extra
    if(n > 0){
        A[n - 1] = {{a[N >> 1]}, {0}};
        B[n - 1] = {{b[N >> 1]}, {0}};
        C[n - 1] = {{0}, {0}};
    }
    A[n] = {{a[0]}, {0}};
    B[n] = {{b[0]}, {0}};
    C[n] = {{0}, {0}};

    // calc C
    for(int i1 = 0; i1 <= n; i1++){
        for(int i2 = 0; i2 <= n; i2++){
            const int i = min(n, i1 + i2), size = max(1, N >> (2 + i));
            for(int j = 0; j < 2; j++) for(int k = 0; k < size; k++){
                C[i][j][k] += A[i1][j][k] * B[i2][j][k];
            }
        }
    }

    // ifft
    Modint mul = 1;
    for(int i = n - 2; i >= 0; i--){
        auto& x = C[i];
        mul *= Modint(2).inv();
        for(auto& y : x) atcoder::internal::butterfly_inv(y);
        for(int i = 0; i < (int)x[0].size(); i++){
            tie(x[0][i], x[1][i]) = pair{x[0][i] + x[1][i], x[0][i] - x[1][i]};
            x[0][i] *= mul;
            x[1][i] *= mul;
        }
    }

    // calc c
    for(int i = 0; i < n - 1; i++){
        const int size = N >> (2 + i);
        for(int j = 0; j < 2; j++) for(int k = 0; k < size; k++){
            c[pow5[j][k] << i & mask] = C[i][j][k];
        }
    }
    if(n > 0) c[N >> 1] = C[n - 1][0][0];
    c[0] = C[n][0][0];
    
    output(c);
}