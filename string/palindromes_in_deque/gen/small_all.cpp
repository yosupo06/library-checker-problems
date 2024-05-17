// visit all strings |s| <= len
// and calls any query from each state

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

struct Query {
    int ty;
    char c;
};

long long required_query_count(int sigma, int len){
    if (len == 0) return sigma * 4;
    return sigma * (2 + required_query_count(sigma, len - 1));
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int sigma = int(seed) + 2;

    int len = 0;
    while (required_query_count(sigma, len + 1) <= Q_MAX) len += 1;

    auto alphabet = gen.choice(sigma, 'a', 'z');
    gen.shuffle(alphabet.begin(), alphabet.end());

    vector<Query> buf;
    for (int c = 0; c < sigma; c++) {
        buf.push_back({ 0, alphabet[c] });
        buf.push_back({ 2, '-' });
        buf.push_back({ 1, alphabet[c] });
        buf.push_back({ 3, '-' });
    }

    for (int i = 0; i < len; i++) {
        vector<Query> new_buf;
        for (int c = 0; c < sigma; c++) {
            new_buf.push_back({ 0, alphabet[c] });
            for (auto query : buf) new_buf.push_back(query);
            new_buf.push_back({ 2, '-' });
        }
        buf = std::move(new_buf);
    }

    printf("%d\n", int(buf.size()));

    for (auto query : buf) {
        if (query.ty <= 1) {
            printf("%d %c\n", query.ty, query.c);
        }
        else {
            printf("%d\n", query.ty);
        }
    }

    return 0;
}
