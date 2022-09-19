#include <vector>
#include <numeric>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int n;
	for (n = 1; n * (n - 1) <= M_MAX; n++);
	n--;
	int m = n * (n - 1);
	std::vector<int> path(n);
	std::iota(path.begin(), path.end(), 0);
	gen.shuffle(path.begin(), path.end());
	int s = path.front();
	int t = path.back();
	println(n, ' ', m, ' ', s, ' ', t);
	
	std::vector<int> next(n, -1);
	for (int i = 0; i + 1 < (int) path.size(); i++) next[path[i]] = path[i + 1];
	
	auto rnd_small = [&] () { return gen.uniform((int) C_MIN, 10); };
	auto rnd_big = [&] () { return gen.uniform((int) C_MIN, (int) C_MAX); };
	
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j)
		println(i, ' ', j, ' ', next[i] == j ? rnd_small() : rnd_big());
	return 0;
}
