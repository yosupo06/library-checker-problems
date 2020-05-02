#include <stdio.h>
#include "random.h"
#include "../params.h"

/*
	a grid graph of len * len vertices
	the shortest path should be like a swirl
*/

#define INDEX(i, j) ((i) * len + (j))
int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int len;
	for (len = 0; len * len * 4 <= M_MAX; len += 2);
	len -= 2;
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	
	auto rnd_small = [&] () { return gen.uniform((int) C_MIN, 10); };
	auto rnd_big = [&] () { return gen.uniform((int) C_MIN, (int) C_MAX); };
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (j < len - 1 - i && j >= i - 1) hens.push_back({INDEX(i, j), INDEX(i, j + 1), rnd_small()});
			else if (j + 1 < len) hens.push_back({INDEX(i, j), INDEX(i, j + 1), rnd_big()});
			if (j >= len - 1 - i && j > i) hens.push_back({INDEX(i, j), INDEX(i + 1, j), rnd_small()});
			else if (i + 1 < len) hens.push_back({INDEX(i, j), INDEX(i + 1, j), rnd_big()});
			if (j >= len - i && j <= i) hens.push_back({INDEX(i, j), INDEX(i, j - 1), rnd_small()});
			else if (j) hens.push_back({INDEX(i, j), INDEX(i, j - 1), rnd_big()});
			if (j < i - 1 && j < len - i) hens.push_back({INDEX(i, j), INDEX(i - 1, j), rnd_small()});
			else if (i) hens.push_back({INDEX(i, j), INDEX(i - 1, j), rnd_big()});
		}
	}
	gen.shuffle(hens.begin(), hens.end());
	
	printf("%d %d %d %d\n", len * len, (int) hens.size(), 0, INDEX(len / 2, len / 2 - 1));
	for (auto i : hens) printf("%d %d %d\n", i.from, i.to, i.cost);
	return 0;
}
