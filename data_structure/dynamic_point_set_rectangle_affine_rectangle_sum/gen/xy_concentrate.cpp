#include <stdio.h>
#include <tuple>
#include <algorithm>
#include "random.h"
#include "../params.h"

const int OP[] = {0, 1, 2, 3};

const int BLOCK = 1000;

int main(int, char **argv) 
{
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	std::vector<int> xs, ys;
	for (int i = 0; i < BLOCK; i++) {
		xs.emplace_back(gen.uniform<int>(0, COORD_MAX - 1));
		ys.emplace_back(gen.uniform<int>(0, COORD_MAX - 1));
	}
	std::sort(xs.begin(), xs.end());
	std::sort(ys.begin(), ys.end());
	xs.emplace_back(COORD_MAX);
	ys.emplace_back(COORD_MAX);
	xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
	ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
	
	int n = N_MAX;
	int q = Q_MAX;
	printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        int x = xs[gen.uniform<int>(0, xs.size() - 1)];
        int y = ys[gen.uniform<int>(0, ys.size() - 1)];
        int w = gen.uniform<int>(0, MOD - 1);
		printf("%d %d %d\n", x, y, w);
    }

    for (int i = 0; i < q; ++i) {
        int op = OP[gen.uniform<int>(0, sizeof(OP) / 4 - 1)];
		printf("%d ", op);
        if (op == 0) {
            int x = xs[gen.uniform<int>(0, xs.size() - 1)];
            int y = ys[gen.uniform<int>(0, ys.size() - 1)];
            int w = gen.uniform<int>(0, MOD - 1);
			printf("%d %d %d\n", x, y, w);
            ++n;
        } 
		else if (op == 1) {
            int idx = gen.uniform<int>(0, n - 1);
            int w = gen.uniform<int>(0, MOD - 1);
			printf("%d %d\n", idx, w);
        } 
		else {
			auto [l, r] = gen.uniform_pair<int>(0, xs.size() - 1);
			auto [d, u] = gen.uniform_pair<int>(0, ys.size() - 1);
			l = xs[l], r = xs[r];
			d = ys[d], u = ys[u];

            if (op == 2) {
				printf("%d %d %d %d\n", l, d, r, u);
            } 
			else { // op == 3
                int a = gen.uniform<int>(0, MOD - 1);
                int b = gen.uniform<int>(0, MOD - 1);
				printf("%d %d %d %d %d %d\n", l, d, r, u, a, b);
            }
        }
    }
	return 0;
}