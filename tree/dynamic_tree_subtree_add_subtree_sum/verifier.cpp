#include <vector>
#include <algorithm>
#include "params.h"
#include "testlib.h"

struct Node;
extern Node *NONE;
struct Node {
#define l ch[0]
#define r ch[1]
	Node *p = NONE;
	Node *ch[2] = {NONE, NONE};
	bool rev = false;
	void flush() {
		if (rev) {
			l->rev ^= 1;
			r->rev ^= 1;
			std::swap(l, r);
			rev = false;
		}
	}
	void rotate(int dir) {
		Node *new_node = ch[!dir];
		ch[!dir] = new_node->ch[dir];
		ch[!dir]->p = this;
		new_node->ch[dir] = this;
		new_node->p = p;
		if (p->l == this) p->l = new_node;
		if (p->r == this) p->r = new_node;
		p = new_node;
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
			cur->r = prev;
			prev = cur;
		}
		splay();
		return prev;
	}
	void link(Node *parent) {
		expose();
		parent->expose();
		p = parent;
		parent->r = this;
	}
	void cut() {
		expose();
		l->p = NONE;
		l = NONE;
	}
	void evert() {
		expose();
		rev ^= 1;
		flush();
	}
	Node *root() {
		expose();
		Node *cur = this;
		while (cur->flush(), (cur->l != NONE)) cur = cur->l;
		return cur;
	}
#undef l
#undef r
};
Node *NONE = new Node;

int main() {
	registerValidation();
	
	int n = inf.readInt(2, N_MAX, "N");
	inf.readSpace();
	int q = inf.readInt(1, Q_MAX, "Q");
	inf.readChar('\n');
	
	for (int i = 0; i < n; i++) {
		inf.readInt(0, VAL_MAX, "a_i");
		if (i != n - 1) inf.readSpace();
	}
	inf.readChar('\n');
	
	std::vector<Node> nodes(n);
	std::set<std::pair<int, int> > hens;
	
	for (int i = 1; i < n; i++) {
		int x = inf.readInt(0, n - 1);
		inf.readSpace();
		int y = inf.readInt(0, n - 1);
		inf.readChar('\n');
		
		hens.insert(std::minmax(x, y));
		ensure(nodes[x].root() != nodes[y].root());
		nodes[x].evert();
		nodes[x].link(&nodes[y]);
	}
	
	for (int i = 0; i < q; i++) {
		int t = inf.readInt(0, 2, "t");
		inf.readSpace();
		if (t == 0) {
			int x = inf.readInt(0, n - 1, "u");
			inf.readSpace();
			int y = inf.readInt(0, n - 1, "v");
			inf.readSpace();
			
			ensure(hens.count(std::minmax(x, y)));
			hens.erase(std::minmax(x, y));
			nodes[x].evert();
			nodes[y].cut();
			
			x = inf.readInt(0, n - 1, "w");
			inf.readSpace();
			y = inf.readInt(0, n - 1, "x");
			
			ensure(nodes[x].root() != nodes[y].root());
			nodes[x].evert();
			nodes[x].link(&nodes[y]);
			hens.insert(std::minmax(x, y));
		} else if (t == 1) {
			int v = inf.readInt(0, n - 1, "v");
			inf.readSpace();
			int p = inf.readInt(0, n - 1, "p");
			inf.readSpace();
			inf.readInt(0, VAL_MAX, "x");
			
			ensure(hens.count(std::minmax(v, p)));
		} else {
			int v = inf.readInt(0, n - 1, "v");
			inf.readSpace();
			int p = inf.readInt(0, n - 1, "p");
			
			ensure(hens.count(std::minmax(v, p)));
		}
		inf.readChar('\n');
	}
	inf.readEof();
	return 0;
}
