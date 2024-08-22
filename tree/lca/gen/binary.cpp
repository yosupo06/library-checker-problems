#include <iostream>
#include <tuple>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int q = Q_MAX;
    printf("%d %d\n", n, q);
    vector<pair<int, int>> parent_pos;
    parent_pos.emplace_back(0, 1);
    parent_pos.emplace_back(0, 2);
    for (int i = 1; i < n; i++) {
        int size = parent_pos.size();
        int k = gen.uniform<int>(0, size - 1);
        swap(parent_pos[k], parent_pos[size - 1]);
        int p, v;
        tie(p, v) = parent_pos[size - 1];
        parent_pos.pop_back();
        for (int u = 2 * v + 1; u <= 2 * v + 2 && u < n; ++u) {
            parent_pos.emplace_back(i, u);
        }
        printf("%d", p);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int u, v;
        std::tie(u, v) = gen.uniform_pair<int>(0, n - 1);
        printf("%d %d\n", u, v);
    }
    return 0;
}
