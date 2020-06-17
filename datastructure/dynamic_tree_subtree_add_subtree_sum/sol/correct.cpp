#include <stdio.h>
#include <inttypes.h>
#include <vector>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

struct Node;
extern Node *NONE;
struct Node {
#define l ch[0]
#define r ch[1]
	Node *p = NONE;
	Node *ch[2] = {NONE, NONE};
	int64_t val = 0;
	int size = 0;
	int size_light = 0; // LIGHT
	int64_t sum = 0;
	int64_t sum_light = 0; // LIGHT
	int64_t added = 0;
	int64_t cancel = 0;
	bool rev = false;
	void flush() {
		if (p != NONE) {
			add(p->added - cancel);
			cancel = p->added;
		}
		if (rev) {
			l->rev ^= 1;
			r->rev ^= 1;
			std::swap(l, r);
			rev = false;
		}
	}
	void fetch() {
		if (l != NONE) l->flush();
		if (r != NONE) r->flush();
		size = 1 + l->size + r->size + size_light;
		sum = val + l->sum + r->sum + sum_light;
	}
	void add(int add_val) {
		val += add_val;
		sum += (int64_t) size * add_val;
		sum_light += (int64_t) size_light * add_val;
		added += add_val;
	}
	void rotate(int dir) {
		Node *new_root = ch[!dir];
		if (new_root->ch[dir] != NONE) new_root->ch[dir]->flush();
		ch[!dir] = new_root->ch[dir];
		ch[!dir]->p = this;
		ch[!dir]->cancel = added;
		new_root->ch[dir] = this;
		new_root->p = p;
		new_root->cancel = p->added;
		if (p->l == this) p->l = new_root;
		if (p->r == this) p->r = new_root;
		p = new_root;
		cancel = new_root->added;
		return fetch(), new_root->fetch();
	}
	bool is_root() { return p == NONE || (p->l != this && p->r != this); }
	void splay() {
		while (!is_root()) {
			if (p->is_root()) {
				p->flush(), flush();
				p->rotate(p->l == this);
			} else {
				Node *pp = p->p;
				pp->flush(), p->flush(), flush();
				bool flag0 = pp->l == p;
				bool flag1 = p->l == this;
				if (flag0 == flag1) pp->rotate(flag0);
				p->rotate(flag1);
				if (flag0 != flag1) pp->rotate(flag0);
			}
		}
		flush();
	}
	Node *expose() {
		Node *prev = NONE;
		for (Node *cur = this; cur != NONE; cur = cur->p) {
			cur->splay();
			if (cur->r != NONE) { // add
				cur->r->flush();
				cur->size_light += cur->r->size;
				cur->sum_light += cur->r->sum;
			}
			cur->r = prev;
			if (cur->r != NONE) { // remove
				cur->r->flush();
				cur->size_light -= cur->r->size;
				cur->sum_light -= cur->r->sum;
			}
			cur->fetch();
			prev = cur;
		}
		splay();
		return prev;
	}
	void link(Node *parent) {
		expose();
		parent->expose();
		parent->r = this;
		p = parent;
		cancel = parent->added;
		parent->fetch();
	}
	void cut() {
		expose();
		l->flush();
		l->p = NONE;
		l = NONE;
		fetch();
	}
	void evert() {
		expose();
		rev ^= 1;
		flush();
	}
#undef l
#undef r
};
Node *NONE = new Node;


int main() {
	int n = ri(), q = ri();
	std::vector<Node> nodes(n);
	for (auto &i : nodes) i.val = ri(), i.fetch();
	for (int i = 1; i < n; i++) {
		int x = ri();
		int y = ri();
		nodes[x].evert();
		nodes[x].link(&nodes[y]);
	}
	for (int i = 0; i < q; i++) {
		int t = ri();
		if (t == 0) {
			int x = ri();
			int y = ri();
			nodes[x].evert();
			nodes[y].cut();
			x = ri();
			y = ri();
			nodes[x].evert();
			nodes[x].link(&nodes[y]);
		} else {
			int x = ri();
			int p = ri();
			nodes[p].evert();
			nodes[x].cut();
			if (t == 1) nodes[x].add(ri());
			else printf("%lld\n", (long long) nodes[x].sum);
			nodes[x].link(&nodes[p]);
		}
	}
	return 0;
}
