#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

struct Query {
    int ty;
    char c;
};

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = gen.uniform(Q_MIN, Q_MAX);
    int sigma = 5;
    auto alphabet = gen.choice(sigma, 'a', 'z');

    int current_len = 0;

    printf("%d\n", q);

    for (int i = 0; i < q; i++) {
        int ty = 0;
        if (current_len >= 1) {
            ty = gen.uniform(0, 3);
        }
        else {
            ty = gen.uniform(0, 1);
        }

        if (ty == 0 || ty == 1) {
            char c = alphabet[gen.uniform(0, sigma - 1)];
            printf("%d %c\n", ty, c);
        }
        else {
            printf("%d\n", ty);
        }
    }

    return 0;
}
