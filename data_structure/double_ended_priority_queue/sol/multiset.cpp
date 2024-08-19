#include <cassert>
#include <cstdio>
#include <set>
#include <vector>

int main() {
    int n, q;
    ::scanf("%d %d", &n, &q);

    std::vector<int> init_vals(n);
    for (auto &e : init_vals) {
        ::scanf("%d", &e);
    }
    std::multiset<int> s(init_vals.begin(), init_vals.end());

    for (int i = 0, query_type, x; i < q; ++i) {
        ::scanf("%d", &query_type);
        if (query_type == 0) {
            ::scanf("%d", &x);
            s.insert(x);
        } else if (query_type == 1) {
            assert(not s.empty());
            auto it = s.begin();
            ::printf("%d\n", *it);
            s.erase(it);
        } else if (query_type == 2) {
            assert(not s.empty());
            auto it = std::prev(s.end());
            ::printf("%d\n", *it);
            s.erase(it);
        } else {
            assert(false);
        }
    }

    return 0;
}