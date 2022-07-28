#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const int n = min(L_MAX, min(R_MAX, M_MAX / 2));

    vector<int> partition;
    const int cnt = gen.uniform(20, 200);
    for (int i = 0; i < cnt; ++i) {
        partition.push_back(gen.uniform<int>(1, n - 1));
    }
    partition.push_back(0);
    partition.push_back(n);
    sort(partition.begin(), partition.end());
    partition.erase(unique(partition.begin(), partition.end()), partition.end());

    using P = pair<int, int>;
    set<P> edges;
    vector<int> left = gen.perm<int>(n);
    vector<int> right = gen.perm<int>(n);

    for (int i = 1; i < (int)partition.size(); ++i) {
        const int len = partition[i] - partition[i - 1];
        gen.shuffle(left.begin(), left.end());
        gen.shuffle(right.begin(), right.end());
        for (int i = 0; i < len; ++i) {
            edges.insert({left[i], right[i]});
            edges.insert({left[i], right[i + 1]});
        }
    }

    vector<P> e(edges.begin(), edges.end());
    gen.shuffle(e.begin(), e.end());

    printf("%d %d %d\n", n, n, (int)e.size());
    for (auto x: e) {
        printf("%d %d\n", x.first, x.second);
    }
    return 0;
}
