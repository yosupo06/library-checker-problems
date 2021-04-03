#include "random.h"
#include <iostream>
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int n = gen.uniform<int>(1, N_AND_Q_MAX);
	int q = gen.uniform<int>(1, N_AND_Q_MAX);
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
		int t = 0;
		if (len) t = gen.uniform(0, 4);
		
		if (t == 0) {
			int i = gen.uniform<int>(0, len);
			int x = gen.uniform<int>(0, MOD - 1);
			printf("%d %d %d\n", t, i, x);
			len++;
		} else if (t == 1) {
			int i = gen.uniform<int>(0, len - 1);
			printf("%d %d\n", t, i);
			len--;
		} else {
			auto lr = gen.uniform_pair<int>(0, len);
			if (gen.uniform(0, 9) == 0) lr.first = 0;
			if (gen.uniform(0, 9) == 0) lr.second = len;
			if (t == 3) {
				int b = gen.uniform<int>(0, MOD - 1);
				int c = gen.uniform<int>(0, MOD - 1);
				printf("%d %d %d %d %d\n", t, lr.first, lr.second, b, c);
			} else printf("%d %d %d\n", t, lr.first, lr.second);
		}
	}
	
	return 0;
}
