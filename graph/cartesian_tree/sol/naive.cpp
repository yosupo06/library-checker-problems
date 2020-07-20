#include <algorithm>
#include <cstdio>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
using namespace::std;

vector<int> solve(int n, const vector<int> & a) {
    vector<int> p(n, -1);
    auto go = [&](auto && go, int l, int r, int parent) {
        if (l == r) return;
        int m = min_element(a.begin() + l, a.begin() + r) - a.begin();
        p[m] = parent;
        go(go, l, m, m);
        go(go, m + 1, r, m);
    };
    go(go, 0, n, -1);
    return p;
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
    vector<int> p = solve(n, a);

    // output
    REP (i, n) {
        printf("%d%c", p[i], i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
