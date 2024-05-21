#include "../params.h"
#include "random.h"
#include <cstdio>

using namespace std;

int main(int, char **argv) {
    long long seed = atoll(argv[1]);
    Random gen(seed);
    int n = N_MAX;
    int m = M_MAX;
    printf("%d %d\n", n, m);
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        pair<int, int> p = gen.uniform_pair(0, n - 1);
        while (edges.count(p)) {
            p = gen.uniform_pair(0, n - 1);
        }
        edges.insert(p);
        if (gen.uniform_bool()) {
            swap(p.first, p.second);
        }
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
