//lichess arena pairing simulation
#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

struct Player {
    int rating;
    int rank;
    int color;
    int last_opponent;
    int score;
    inline bool operator<(const Player &rhs) const {
        return make_pair(rhs.score, rhs.rating) < make_pair(score, rating);
    }
};

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = 100;
    int players = 500;
    vector<Player> p;
    for (int i = 0; i < players; ++i) {
        Player q;
        q.rating = gen.uniform(1000, 3000);
        q.color = gen.uniform(0, 7);
        q.last_opponent = gen.uniform(0, players - 1);
        q.score = gen.uniform(0, 100);
        p.push_back(q);
    }
    sort(p.begin(), p.end());
    for (int i = 0; i < players; ++i) {
        p[i].rank = i;
    }
    gen.shuffle(p.begin(), p.end());
    p.resize(n);

    using P3 = pair<pair<int, int>, int>;
    vector<P3> edges;
    int maxRank = 0;
    for (int i = 0; i < n; i++) {
        if (maxRank < p[i].rank) {
            maxRank = p[i].rank;
        }
    }
    int maxw = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].color == 0 && p[j].color == 0) { continue; }
            if (p[i].color == 7 && p[j].color == 7) { continue; }
            if (p[i].last_opponent == p[j].rank) { continue; }
            if (p[j].last_opponent == p[i].rank) { continue; }
            int rank = std::min(p[i].rank, p[j].rank);
            int rank_factor = 300 + 1700 * (maxRank - rank) / (maxRank + 1);
            int w = std::abs(p[i].rank - p[j].rank) * rank_factor + std::abs(p[i].rating - p[j].rating);
            maxw = std::max(maxw, w);
            if (gen.uniform_bool()) {
                edges.push_back({{i, j}, w});
            } else {
                edges.push_back({{j, i}, w});
            }
        }
    }
    int m = (int) edges.size();
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int w = -edges[i].second + maxw + 1;
        printf("%d %d %d\n", edges[i].first.first, edges[i].first.second, w);
    }
    return 0;
}
