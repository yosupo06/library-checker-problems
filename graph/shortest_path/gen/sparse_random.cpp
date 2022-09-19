#include <set>
#include <utility>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int n = gen.uniform(N_MIN, N_MAX);
	int m = gen.uniform(M_MIN, M_MAX);
	int s = gen.uniform(0, n - 1);
	int t;
	do t = gen.uniform(0, n - 1); while (s == t);
	println(n, ' ', m, ' ', s, ' ', t);
	
	std::set<std::pair<int, int> > used;
	for (int i = 0; i < m; i++) {
		int a, b;
		do a = gen.uniform(0, n - 1), b = gen.uniform(0, n - 1); while (a == b || !used.insert({a, b}).second);
		int c = gen.uniform(C_MIN, C_MAX);
		println(a, ' ', b, ' ', c);
	}
	return 0;
}
