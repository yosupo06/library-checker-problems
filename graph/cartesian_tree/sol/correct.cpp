#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
using namespace::std;

template <class T, class Comparator = std::less<int> >
std::vector<int> construct_cartesian_tree(const std::vector<T> & a, const Comparator & cmp = Comparator()) {
    int n = a.size();
    std::vector<int> parent(n, -1);
    REP3 (i, 1, n) {
        int p = i - 1;  // parent of i
        int l = -1;  // left child of i
        while (p != -1 and cmp(a[i], a[p])) {
            int pp = parent[p];  // parent of parent of i
            if (l != -1) {
                parent[l] = p;
            }
            parent[p] = i;
            l = p;
            p = pp;
        }
        parent[i] = p;
    }
    return parent;
}

int main(){
    // input
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    REP (i, n) {
        scanf("%d", &a[i]);
    }

    // solve
    vector<int> p = construct_cartesian_tree(a);

    // output
    REP (i, n) {
        printf("%d%c", p[i], i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
