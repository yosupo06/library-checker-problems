#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "../params.h"
#include "random.h"

int mpow(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = (int64_t) res * a % MOD;
		a = (int64_t) a * a % MOD;
	}
	return res;
}
int inv(int x) { return mpow(x, MOD - 2); }

int main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = N_AND_M_MAX;
	std::vector<int> a(n), b(n);
	for (auto &i : a) i = gen.uniform(0LL, MOD - 1);
	for (auto &i : b) i = gen.uniform(0LL, MOD - 1);
	// make c[n - 1] == 0
	a[0] = gen.uniform(1LL, MOD - 1); // it should not be 0
	int cur_sum = 0;
	for (int i = 0; i < n; i++) cur_sum = (cur_sum + (int64_t) a[i] * b[n - 1 - i]) % MOD;
	b[n - 1] -= ((int64_t) cur_sum * inv(a[0])) % MOD;
	if (b[n - 1] < 0) b[n - 1] += MOD;
	
	printf("%d %d\n", n, n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", a[i]);
	}
	puts("");
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", b[i]);
	}
	puts("");
	return 0;
}
