#include <set>
#include <utility>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int n = 50;
	int m = 100;
	int s = gen.uniform(0, n - 1);
	int t;
	do t = gen.uniform(0, n - 1); while (s == t);
	println(n, ' ', m, ' ', s, ' ', t);
	
	std::set<std::pair<int, int> > used;
	for (int i = 0; i < m; i++) {
		int a, b;
		do a = gen.uniform(0, n - 1), b = gen.uniform(0, n - 1); while (a == b || !used.insert({a, b}).second);
		int c = gen.uniform((int) C_MIN, 100);
		println(a, ' ', b, ' ', c);
	}
	return 0;
}
