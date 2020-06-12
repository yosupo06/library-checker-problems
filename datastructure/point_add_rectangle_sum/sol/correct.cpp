#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

struct SegTree {
	size_t n;
	std::vector<int64_t> data;
	std::vector<int> xs;
	void reserve(int i) { xs.push_back(i); }
	void build0() {
		std::sort(xs.begin(), xs.end());
		for (n = 1; n < xs.size(); n <<= 1);
		data.resize(n << 1);
	}
	void build1() {
		for (int i = n; --i; ) data[i] = data[i << 1] + data[i << 1 | 1];
	}
	void add_pre(int i, int val) {
		i = std::lower_bound(xs.begin(), xs.end(), i) - xs.begin();
		data[i + n] += val;
	}
	void add(int i, int val) {
		i = std::lower_bound(xs.begin(), xs.end(), i) - xs.begin();
		for (i += n; i; i >>= 1) data[i] += val;
	}
	int64_t sum(int l, int r) {
		l = std::lower_bound(xs.begin(), xs.end(), l) - xs.begin();
		r = std::lower_bound(xs.begin(), xs.end(), r) - xs.begin();
		int64_t res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (r & 1) res += data[--r];
			if (l & 1) res += data[l++];
		}
		return res;
	}
};
struct SegTree2D {
	size_t n;
	std::vector<SegTree> trees;
	SegTree2D (size_t n_) {
		for (n = 1; n < n_; n <<= 1);
		trees.resize(n << 1);
	}
	void reserve(int i, int j) {
		for (i += n; i; i >>= 1) trees[i].reserve(j);
	}
	void build0() {
		for (auto &i : trees) i.build0();
	}
	void build1() {
		for (auto &i : trees) i.build1();
	}
	void add_pre(int i, int j, int val) {
		for (i += n; i; i >>= 1) trees[i].add_pre(j, val);
	}
	void add(int i, int j, int val) {
		for (i += n; i; i >>= 1) trees[i].add(j, val);
	}
	int64_t sum(int l0, int r0, int l1, int r1) {
		int64_t res = 0;
		for (l0 += n, r0 += n; l0 < r0; l0 >>= 1, r0 >>= 1) {
			if (r0 & 1) res += trees[--r0].sum(l1, r1);
			if (l0 & 1) res += trees[l0++].sum(l1, r1);
		}
		return res;
	}
};

int main() {
	int n = ri();
	int q = ri();
	std::vector<int> xs;
	struct Point {
		int x;
		int y;
		int weight;
	};
	std::vector<Point> pts(n);
	for (auto &i : pts) {
		i.x = ri();
		i.y = ri();
		i.weight = ri();
		xs.push_back(i.x);
	}
	std::vector<int> a(q), b(q), c(q), d(q);
	for (int i = 0; i < q; i++) {
		a[i] = ri() - 1;
		if (!a[i]) a[i] = ri();
		b[i] = ri();
		c[i] = ri();
		d[i] = ri();
		if (a[i] == -1) xs.push_back(b[i]);
	}
	std::sort(xs.begin(), xs.end());
	SegTree2D tree(xs.size());
	for (auto &i : pts) {
		i.x = std::lower_bound(xs.begin(), xs.end(), i.x) - xs.begin();
		tree.reserve(i.x, i.y);
	}
	for (int i = 0; i < q; i++) {
		if (a[i] == -1) {
			b[i] = std::lower_bound(xs.begin(), xs.end(), b[i]) - xs.begin();
			tree.reserve(b[i], c[i]);
		} else {
			a[i] = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
			c[i] = std::lower_bound(xs.begin(), xs.end(), c[i]) - xs.begin();
		}
	}
	tree.build0();
	for (auto i : pts) tree.add_pre(i.x, i.y, i.weight);
	tree.build1();
	for (int i = 0; i < q; i++) {
		if (a[i] == -1) tree.add(b[i], c[i], d[i]);
		else printf("%lld\n", (long long) tree.sum(a[i], c[i], b[i], d[i]));
	}
	return 0;
}
