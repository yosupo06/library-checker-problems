#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <vector>
#include <set>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

std::vector<int> a;
std::vector<std::set<int> > hen;

void add(int i, int prev, int val) {
	a[i] += val;
	for (auto j : hen[i]) if (j != prev) add(j, i, val);
}
int64_t sum(int i, int prev) {
	int64_t res = a[i];
	for (auto j : hen[i]) if (j != prev) res += sum(j, i);
	return res;
}

int main() {
	int n = ri();
	int q = ri();
	if ((int64_t) n * q >= 10000000) return EXIT_FAILURE;
	a.resize(n);
	for (auto &i : a) i = ri();
	hen.resize(n);
	for (int i = 1; i < n; i++) {
		int x = ri();
		int y = ri();
		hen[x].insert(y);
		hen[y].insert(x);
	}
	for (int i = 0; i < q; i++) {
		int t = ri();
		if (t == 0) {
			int x = ri();
			int y = ri();
			hen[x].erase(y);
			hen[y].erase(x);
			x = ri();
			y = ri();
			hen[x].insert(y);
			hen[y].insert(x);
		} else if (t == 1) {
			int x = ri();
			int p = ri();
			add(x, p, ri());
		} else if (t == 2) {
			int x = ri();
			int p = ri();
			printf("%lld\n", (long long) sum(x, p));
		}
	}
	return 0;
}
