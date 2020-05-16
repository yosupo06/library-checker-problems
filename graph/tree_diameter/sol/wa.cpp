#include <cstdio>
#include <vector>

int main() {
    int N, Q; scanf("%d%d", &N, &Q);
    std::vector<int> A(N+1);
    for(int i=0; i<N; i++) scanf("%d", &A[i+1]), A[i+1] += A[i];

    while(Q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", A[r] - A[l]);
    }
    return 0;
}
