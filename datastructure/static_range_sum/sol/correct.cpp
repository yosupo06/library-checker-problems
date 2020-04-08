#include <cstdio>
#include <vector>
using ll = long long int;

int main() {
    int N, Q; scanf("%d%d", &N, &Q);
    std::vector<ll> A(N+1);
    for(int i=0; i<N; i++) scanf("%lld", &A[i+1]), A[i+1] += A[i];

    while(Q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%lld\n", A[r] - A[l]);
    }
    return 0;
}
