#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <set>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}
typedef uint32_t u32;

struct Trie {
	struct Node {
		Node *ch[2] = {NULL, NULL};
		int count = 0;
	};
	static Node *nodes;
	static int head;
	Node *root = NULL;
	void insert(u32 n) {
		Node **cur = &root;
		for (int i = 29; ; i--) {
			if (!*cur) *cur = nodes + head++;
			(*cur)->count++;
			if (i <= -1) break;
			cur = (*cur)->ch + (n >> i & 1);
		}
	}
	void remove(u32 n) {
		Node *cur = root;
		for (int i = 30; i--; ) cur->count--, cur = cur->ch[n >> i & 1];
		cur->count--;
	}
	u32 xor_min(u32 n) {
		u32 res = 0;
		Node *cur = root;
		assert(cur->count);
		for (int i = 30; i--; ) {
			if (cur->ch[n >> i & 1] && cur->ch[n >> i & 1]->count) cur = cur->ch[n >> i & 1];
			else res |= 1 << i, cur = cur->ch[!(n >> i & 1)];
		}
		return res;
	}
};
Trie::Node *Trie::nodes = new Node[20000000];
int Trie::head = 1;

int main() {
	int q = ri();
	std::set<int> all;
	Trie tree;
	for (int i = 0; i < q; i++) {
		int t = ri();
		int x = ri();
		if (t == 0 && all.insert(x).second) tree.insert(x);
		if (t == 1 && all.erase(x)) tree.remove(x);
		if (t == 2) printf("%d\n", tree.xor_min(x));
	}
	return 0;
}
