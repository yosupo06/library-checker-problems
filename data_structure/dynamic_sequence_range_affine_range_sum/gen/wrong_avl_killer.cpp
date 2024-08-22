#include "random.h"
#include <iostream>
#include "../params.h"

// https://qiita.com/QCFium/items/e8d17032172eba3215a7

struct BIT {
	int n;
	std::vector<int> data;
	BIT (int n) : n(n) {
		data.resize(n + 1);
	}
	void add(int i, int val) {
		for (i++; i <= n; i += i & -i) data[i] += val;
	}
	int sum(int r) {
		int res = 0;
		for (; r; r -= r & -r) res += data[r];
		return res;
	}
};

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
	
	int mask = 1;
	{
		int m = q - 1;
		while (1) {
			int next = mask * 2 + 1;
			if (std::min(mask, m - mask) >= std::min(next, m - next)) break;
			mask = next;
		}
	}
	
	BIT tree((mask + 1) << 1);
	tree.add(mask, 1);
	
	int len = n;
	for (int i = 0; i < q; i++) {
		if (i < q - 1) {
			int cur = (i + 1) ^ mask;
			int index = tree.sum(cur);
			if (seed) index = len - index;
			printf("0 %d %d\n", index, gen.uniform<int>(0, MOD - 1));
			tree.add(cur, 1);
			len++;
		} else {
			auto lr = gen.uniform_pair<int>(0, len);
			printf("4 %d %d\n", lr.first, lr.second);
		}
	}
	
	return 0;
}
