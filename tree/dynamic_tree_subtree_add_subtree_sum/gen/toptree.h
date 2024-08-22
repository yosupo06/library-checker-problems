#include <array>
#include <algorithm>
#include <assert.h>

namespace TopTree {
	struct Node;
	extern Node *NONE;
	struct Node {
		Node *p = NONE;
		std::array<std::array<Node *, 2>, 2> ch = { { {NONE, NONE}, {NONE, NONE} } };
		Node *light_down = NONE;
		bool rev = false;
		
		int size_heavy = 0;
		int size_light = 0;
		Node *fetch() {
			for (auto &i : ch) for (auto j : i) if (j != NONE) j->flush();
			if (light_down != NONE) light_down->flush();
			
			size_heavy = 1 + ch[0][0]->size_heavy + ch[0][1]->size_heavy + light_down->size_light;
			size_light = size_heavy + ch[1][0]->size_light + ch[1][1]->size_light;
			return this;
		}
		void flush() {
			if (rev) {
				ch[0][0]->rev ^= 1;
				ch[0][1]->rev ^= 1;
				std::swap(ch[0][0], ch[0][1]);
				rev = false;
			}
		}
#   	define l ch[cat][0]
#   	define r ch[cat][1]
		template<int cat> Node *rotate(int dir) {
			Node *new_root = ch[cat][!dir];
			if (!cat) std::swap(new_root->ch[1], ch[1]);
			ch[cat][!dir] = new_root->ch[cat][dir];
			ch[cat][!dir]->p = this;
			new_root->ch[cat][dir] = this;
			for (auto &i : p->ch) for (auto &j : i) if (j == this) j = new_root;
			if (p->light_down == this) p->light_down = new_root;
			new_root->p = p;
			p = new_root;
			return fetch(), new_root->fetch();
		}
		template<int cat> bool is_root() {
			return p == NONE || (p->l != this && p->r != this);
		}
		template<int cat> void splay() {
			flush();
			while (!is_root<cat>()) {
				if (p->is_root<cat>()) {
					p->flush(), flush();
					p->rotate<cat>(p->l == this);
				} else {
					Node *pp = p->p;
					pp->flush(), p->flush(), flush();
					bool dir0 = pp->l == p;
					bool dir1 = p->l == this;
					if (dir0 == dir1) pp->rotate<cat>(dir0);
					p->rotate<cat>(dir1);
					if (dir0 != dir1) pp->rotate<cat>(dir0);
				}
			}
		}
#   	undef l
#   	undef r
		void expose() {
			Node *cur = this;
			cur->splay<0>();
			for (; cur != NONE; ) {
				cur->splay<1>();
				if (cur->p == NONE) break;
				cur = cur->p;
				cur->splay<0>();
				cur->light_down->flush();
				if (cur->ch[0][1] != NONE) {
					cur->ch[0][1]->flush();
					std::swap(cur->ch[0][1]->ch[1], cur->light_down->ch[1]);
					std::swap(cur->ch[0][1], cur->light_down);
					for (auto i : cur->light_down->ch[1]) i->p = cur->light_down;
					cur->light_down->fetch();
				} else {
					cur->ch[0][1] = cur->light_down;
					Node *rightest = cur->light_down->ch[1][0];
					if (rightest == NONE) rightest = cur->light_down->ch[1][1];
					else {
						Node *tmp = cur->light_down->ch[1][1];
						rightest->p = NONE;
						while (rightest->flush(), (rightest->ch[1][1] != NONE))
							rightest = rightest->ch[1][1];
						rightest->splay<1>();
						rightest->ch[1][1] = tmp;
						tmp->p = rightest;
						rightest->fetch();
					}
					cur->light_down = rightest;
					rightest->p = cur;
					cur->ch[0][1]->ch[1] = {NONE, NONE};
				}
				cur->fetch();
			}
			splay<0>();
			Node *right = ch[0][1];
			if (right != NONE) {
				right->flush();
				right->ch[1][0] = light_down;
				light_down->p = right;
				light_down = right;
				ch[0][1] = NONE;
				right->fetch();
				fetch();
			}
		}
		void link(Node *parent) {
			parent->expose();
			expose();
			p = parent;
			parent->ch[0][1] = this;
			parent->fetch();
		}
		Node *cut() {
			expose();
			Node *res = ch[0][0];
			ch[0][0]->p = NONE;
			ch[0][0] = NONE;
			fetch();
			return res;
		}
		void evert() {
			expose();
			rev ^= 1;
			flush();
		}
		Node *kth_light(int k) {
			assert(k < size_light);
			flush();
			if (k < ch[1][0]->size_light) return ch[1][0]->kth_light(k);
			k -= ch[1][0]->size_light;
			if (k < size_heavy) return kth_heavy(k);
			k -= size_heavy;
			return ch[1][1]->kth_light(k);
		}
		Node *kth_heavy(int k) {
			assert(k < size_heavy);
			flush();
			if (!k) return this;
			k--;
			if (k < ch[0][0]->size_heavy) return ch[0][0]->kth_heavy(k);
			k -= ch[0][0]->size_heavy;
			if (k < ch[0][1]->size_heavy) return ch[0][1]->kth_heavy(k);
			k -= ch[0][1]->size_heavy;
			return light_down->kth_light(k);
		}
		int size() { return size_light; }
	};
	Node *NONE = new Node;
}
