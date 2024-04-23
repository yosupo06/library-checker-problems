#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int get_max_n() {
    int ok = N_MIN, ng = N_MAX + 1;
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        if ((long long)mid * (mid - 1) / 2 <= M_MAX) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main(int, char **argv) {
    long long seed = atoll(argv[1]);
    Random gen(seed);
    int n = get_max_n();
    int m = n * (n - 1) / 2;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (gen.uniform_bool()) {
                edges.emplace_back(i, j);
            } else {
                edges.emplace_back(j, i);
            }
        }
    }
    gen.shuffle(edges.begin(), edges.end());
    printf("%d %d\n", n, m);
    for (pair<int, int> e : edges) {
        printf("%d %d\n", e.first, e.second);
    }
}
