#include <cstdio>
#include <vector>

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);

    for (int q = 0; q < Q; ++q) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            int p, x;
            scanf("%d%d", &p, &x);
            A[p] = x;
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            int res = 0, cnt = 0;
            for (int i = l; i < r; i++) {
                if (cnt == 0 || res == A[i]) {
                    res = A[i];
                    cnt++;
                } else {
                    cnt--;
                }
            }
            cnt = 0;
            for (int i = l; i < r; i++) {
                if (A[i] == res) {
                    cnt++;
                }
            }
            if (cnt * 2 > r - l) {
                printf("%d\n", res);
            } else {
                printf("-1\n");
            }
        }
    }

    return 0;
}
