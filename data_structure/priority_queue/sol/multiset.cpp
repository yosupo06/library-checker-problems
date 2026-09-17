#include <cstdio>
#include <set>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::multiset<int> s;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        s.insert(x);
    }

    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            int x;
            scanf("%d", &x);
            s.insert(x);
        } else {
            auto it = s.begin();
            printf("%d\n", *it);
            s.erase(it);
        }
    }
    return 0;
}
