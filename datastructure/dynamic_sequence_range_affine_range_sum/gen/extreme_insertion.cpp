#include "random.h"
#include <iostream>
#include "../params.h"

// insert in order (x2 : ascending or descending)
// insert alternately, front & back

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = 1;
	int q = N_AND_Q_MAX;
	printf("%d %d\n", n, q);
	
	std::vector<int> a(n);
	for (auto &i : a) i = gen.uniform<int>(0, MOD - 1);
	
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", a[i]);
	}
	puts("");
	
	int len = n;
	for (int i = 0; i < q; i++) {
		if (i + 1 < q) {
			int index = seed == 0 ? 0 : seed == 1 ? len : (i & 1) ? 0 : len;
			printf("0 %d %d\n", index, gen.uniform<int>(0, MOD - 1));
		} else {
			auto lr = gen.uniform_pair<int>(0, len);
			printf("4 %d %d\n", lr.first, lr.second);
		}
	}
	
	return 0;
}
