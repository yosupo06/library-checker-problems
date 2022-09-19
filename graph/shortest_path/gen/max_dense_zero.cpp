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
	int s = gen.uniform(0, n - 1);
	int t;
	do t = gen.uniform(0, n - 1); while (s == t);
	println(n, ' ', m, ' ', s, ' ', t);
	
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j)
		println(i, ' ', j, ' ', 0);
	return 0;
}
