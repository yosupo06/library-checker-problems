#include <stdio.h>
#include "random.h"
#include "../params.h"

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
	printf("%d %d %d %d\n", n, m, s, t);
	
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j)
		printf("%d %d %d\n", i, j, (int) gen.uniform(C_MIN, C_MAX));
	return 0;
}
