#include <stdio.h>
#include <inttypes.h>
#include <vector>
#include <numeric>
#include <algorithm>

#define MOD 998244353

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

int main() {
	int n = ri();
	int q = ri();
	if ((int64_t) (n + q) * q >= 100000000) return EXIT_FAILURE;
	
	std::vector<int> a(n);
	for (auto &i : a) i = ri();
	
	for (int i = 0; i < q; i++) {
		int t = ri();
		if (t == 0) {
			int i = ri();
			int x = ri();
			a.insert(a.begin() + i, x);
		} else if (t == 1) {
			int i = ri();
			a.erase(a.begin() + i);
		} else {
			int l = ri();
			int r = ri();
			if (t == 2) std::reverse(a.begin() + l, a.begin() + r);
			else if (t == 3) {
				int b = ri();
				int c = ri();
				for (int j = l; j < r; j++) a[j] = ((int64_t) a[j] * b + c) % MOD;
			} else printf("%d\n", (int) (std::accumulate(a.begin() + l, a.begin() + r, 0LL) % MOD));
		}
	}
	
	return 0;
}
