#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = MAX_N;

    vector<int> perm = gen.perm<int>(n);

    using P = pair<int, int>;
    
    // construct the graph
    vector<P> edges;
    for (int i = 0; i + 1 < n; i++) {
        edges.push_back({ perm[i], perm[i + 1] });
    }
    
    // shuffle edge input order
    gen.shuffle(edges.begin(), edges.end());
    for (auto& e : edges) {
        if (gen.uniform_bool()) {
            swap(e.first, e.second);
        }
    }

    // output
    int m = (int)edges.size();

    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        printf("%d %d\n", edges[i].first, edges[i].second);
    }
    return 0;
}