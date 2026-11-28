#include <cstdio>
#include <functional>
#include <queue>
#include <vector>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        pq.push(x);
    }

    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            int x;
            scanf("%d", &x);
            pq.push(x);
        } else {
            printf("%d\n", pq.top());
            pq.pop();
        }
    }
    return 0;
}
