#include <iostream>
#include <vector>
#include <cassert>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

#define MOD 998244353

struct AVL {
	struct Node {
		Node *l;
		Node *r;
		int sum = 0;
		int self = 0;
		std::pair<int, int> lazy = {1, 0};
		int size = 0;
		int height = 0;
		bool rev = false;
		
		Node *fetch() {
			if (l != AVL::NONE) l->flush();
			if (r != AVL::NONE) r->flush();
			sum = ((int64_t) self + l->sum + r->sum) % MOD;
			size = 1 + l->size + r->size;
			height = 1 + std::max(l->height, r->height);
			return this;
		}
		Node *flush() {
			self = ((int64_t) self * lazy.first + lazy.second) % MOD;
			sum = ((int64_t) sum * lazy.first + (int64_t) size * lazy.second) % MOD;
			l->lazy = {((int64_t) l->lazy.first * lazy.first) % MOD, ((int64_t) l->lazy.second * lazy.first + lazy.second) % MOD};
			r->lazy = {((int64_t) r->lazy.first * lazy.first) % MOD, ((int64_t) r->lazy.second * lazy.first + lazy.second) % MOD};
			lazy = {1, 0};
			if (rev) {
				std::swap(l, r);
				l->rev ^= 1;
				r->rev ^= 1;
				rev = false;
			}
			return this;
		}
		Node *rotate_r() {
			Node *new_root = l->flush();
			l = new_root->r;
			new_root->r = this;
			return fetch(), new_root->fetch();
		}
		Node *rotate_l() {
			Node *new_root = r->flush();
			r = new_root->l;
			new_root->l = this;
			return fetch(), new_root->fetch();
		}
		int diff() { return l->height - r->height; }
		Node *balance() {
			int dif = diff();
			if (dif == 2) {
				if (l->flush()->diff() < 0) l = l->rotate_l();
				return rotate_r();
			} else if (dif == -2) {
				if (r->flush()->diff() > 0) r = r->rotate_r();
				return rotate_l();
			} else return fetch();
		}
	};
	static int head;
	static Node *nodes, *NONE, *removed_tmp;
	Node *root = NONE;
	
	AVL () = default;
	AVL (Node *root) : root(root) {}
	
	void init(std::vector<int> &a) {
		root = construct(&a[0], &a[0] + a.size());
	}
	static Node *construct(int *start, int *end) {
		if (end <= start) return NONE;
		int *mid = start + ((end - start) >> 1);
		Node *l = construct(start, mid);
		Node *r = construct(mid + 1, end);
		return (nodes[head++] = {l, r, 0, *mid, {1, 0}, 0, 0, false}).fetch();
	}
	
	static Node *insert(Node *node, int i, int x) {
		if (node == NONE) return &(nodes[head++] = {NONE, NONE, x, x, {1, 0}, 1, 1, false});
		node->flush();
		int lsize = node->l->size;
		if (i <= lsize) node->l = insert(node->l, i, x);
		else node->r = insert(node->r, i - lsize - 1, x);
		return node->balance();
	}
	static Node *remove_rightest(Node *node) {
		node->flush();
		if (node->r != NONE) {
			node->r = remove_rightest(node->r);
			return node->balance();
		} else return (removed_tmp = node)->l;
	}
	static Node *remove(Node *node, int i) {
		node->flush();
		int lsize = node->l->size;
		if (i < lsize) node->l = remove(node->l, i);
		else if (i > lsize) node->r = remove(node->r, i - lsize - 1);
		else {
			if (node->l == NONE) return node->r;
			node->l = remove_rightest(node->l);
			removed_tmp->l = node->l;
			removed_tmp->r = node->r;
			return removed_tmp->balance();
		}
		return node->balance();
	}
	static int sum(Node *node, int l, int r) {
		if (node == NONE) return 0;
		node->flush();
		if (r <= 0 || l >= node->size) return 0;
		if (l <= 0 && r >= node->size) return node->sum;
		int lsize = node->l->size;
		int res = l <= lsize && r > lsize ? node->self : 0;
		if (l < lsize) {
			res += sum(node->l, l, r);
			if (res >= MOD) res -= MOD;
		}
		if (r > lsize + 1) {
			res += sum(node->r, l - lsize - 1, r - lsize - 1);
			if (res >= MOD) res -= MOD;
		}
		return res;
	}
	static Node *merge_with_root(Node *l, Node *root, Node *r) {
		int dif = l->height - r->height;
		if (-1 <= dif && dif <= 1) {
			root->l = l;
			root->r = r;
			return root->fetch();
		} else if (dif > 0) {
			l->flush();
			l->r = merge_with_root(l->r, root, r);
			return l->balance();
		} else {
			r->flush();
			r->l = merge_with_root(l, root, r->l);
			return r->balance();
		}
	}
	static Node *merge(Node *l, Node *r) {
		if (l == NONE) return r;
		if (r == NONE) return l;
		l = remove_rightest(l);
		return merge_with_root(l, removed_tmp, r);
	}
	static std::pair<Node *, Node *> split(Node *node, int i) {
		if (node == NONE) return {NONE, NONE};
		node->flush();
		int lsize = node->l->size;
		Node *l = node->l;
		Node *r = node->r;
		node->l = node->r = NONE;
		if (i < lsize) {
			auto tmp = split(l, i);
			return {tmp.first, merge_with_root(tmp.second, node, r)};
		} else if (i > lsize) {
			auto tmp = split(r, i - lsize - 1);
			return {merge_with_root(l, node, tmp.first), tmp.second};
		} else return {l, merge_with_root(NONE, node, r)};
	}
	static void debug(Node *node, int indent) {
		for (int i = 0; i < indent; i++) printf(" ");
		if (node == NONE) {
			puts("NONE");
			return;
		}
		printf("#%d : %d, sum:%d, sh:{%d, %d}\n", (int) (node - nodes), node->self, node->sum, node->size, node->height);
		debug(node->l, indent + 1);
		debug(node->r, indent + 1);
	}
	void insert(int i, int x) { root = insert(root, i, x); }
	void remove(int i) { root = remove(root, i); }
	int sum(int l, int r) { return sum(root, l, r); }
	static AVL merge(AVL l, AVL r) { return AVL(merge(l.root, r.root)); }
	std::pair<AVL, AVL> split(int i) {
		auto tmp = split(root, i);
		return {AVL(tmp.first), AVL(tmp.second)};
	}
	void reverse(int l, int r) {
		auto r0 = split(root, r);
		auto r1 = split(r0.first, l);
		r1.second->rev ^= 1;
		root = merge(merge(r1.first, r1.second), r0.second);
	}
	void affine(int l, int r, int b, int c) {
		auto r0 = split(root, r);
		auto r1 = split(r0.first, l);
		r1.second->flush();
		r1.second->lazy = {b, c};
		root = merge(merge(r1.first, r1.second), r0.second);
	}
	void debug() { debug(root, 0); }
};
int AVL::head = 1;
AVL::Node *AVL::nodes = new Node[1000001], *AVL::NONE = nodes, *AVL::removed_tmp;


int main() {
	int n = ri();
	int q = ri();
	std::vector<int> a(n);
	for (auto &i : a) i = ri();
	
	AVL tree;
	tree.init(a);
	for (int i = 0; i < q; i++) {
		// tree.debug();
		int t = ri();
		if (t == 0) {
			int i = ri();
			int x = ri();
			tree.insert(i, x);
		} else if (t == 1) {
			int i = ri();
			tree.remove(i);
		} else {
			int l = ri();
			int r = ri();
			if (t == 2) tree.reverse(l, r);
			else if (t == 3) {
				int b = ri();
				int c = ri();
				tree.affine(l, r, b, c);
			} else if (t == 4) printf("%d\n", tree.sum(l, r));
		}
	}
	
	return 0;
}
