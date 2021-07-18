#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500;
    int m = 10;
    set<int> a;
    a.insert(0);
    a.insert(n);
    for (int i = 0; i < m; ++i) {
        a.insert(gen.uniform(1, n - 1));
    }
    vector<int> b(a.cbegin(), a.cend());
    using P3 = pair<pair<int, int>, int>;
    vector<P3> edges;
    vector<int> c;
    for(int i = 1; i < (int) b.size(); ++i) {
        int l = b[i] - b[i-1];
        if (l == 1) {
          continue;
        }
        for(int j = 0; j < l; ++j) {
            int k = (j + 1) % l;
            int w = gen.uniform(1, 1000000);
            edges.push_back({{b[i-1] + j, b[i-1] + k}, w});
            if (l == 2) {
              //fix for duplicated edges
              break;
            }
        }
        c.push_back(gen.uniform(b[i-1], b[i] - 1));
    }
    for(int i = 0; i < (int) c.size(); ++i) {
        int j = (i + 1) % (int) c.size();
        int w = gen.uniform(1, 1000000);
        edges.push_back({{c[i], c[j] }, w});
    }
    gen.shuffle(edges.begin(), edges.end());
    printf("%d %d\n", n, (int) edges.size());
    for (int i = 0; i < (int) edges.size(); i++) {
        printf("%d %d %d\n", edges[i].first.first, edges[i].first.second, edges[i].second);
    }
    return 0;
}
