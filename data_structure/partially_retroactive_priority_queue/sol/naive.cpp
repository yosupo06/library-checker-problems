#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    std::vector<std::pair<int, int>> operations(N);
    for (auto &[t, x] : operations) scanf("%d%d", &t, &x);
    while (Q--) {
        int k, a, b;
        scanf("%d%d%d", &k, &a, &b);
        operations[k] = {a, b};
        std::priority_queue<int, std::vector<int>, std::greater<>> M;
        long long sum = 0;
        for (auto [t, x] : operations) {
            if (t == 0) {
                M.push(x);
                sum += x;
            } else if (t == 1 && !M.empty()) {
                sum -= M.top();
                M.pop();
            }
        }
        printf("%zu %lld\n", M.size(), sum);
    }
}
