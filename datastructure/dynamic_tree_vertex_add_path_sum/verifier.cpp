#include <cassert>
#include <utility>
#include "params.h"
using namespace std;

struct LinkCutTree {
  struct Node {
    Node *l, *r, *p;
    int idx;

    bool rev;
    int sz;

    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx) :
        l(nullptr), r(nullptr), p(nullptr), idx(idx), rev(false), sz(1) {}
  };

  LinkCutTree() {}

  Node *make_node(int idx) {
    return new Node(idx);
  }

  void propagate(Node*) {
  }

  void toggle(Node *t) {
    assert(t);
    swap(t->l, t->r);
    t->rev ^= true;
  }

  void push(Node *t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(Node *t) {
    t->sz = 1;
    if(t->l) t->sz += t->l->sz;
    if(t->r) t->sz += t->r->sz;
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *expose(Node *t) {
    Node *rp = nullptr;
    for(Node *cur = t; cur; cur = cur->p) {
      splay(cur);
      cur->r = rp;
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void link(Node *child, Node *parent) {
    expose(child);
    expose(parent);
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(Node *child) {
    expose(child);
    auto *parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(Node *t) {
    expose(t);
    toggle(t);
    push(t);
  }

  Node *lca(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
  }

  Node *get_root(Node *x) {
    expose(x);
    while(x->l) {
      push(x);
      x = x->l;
    }
    return x;
  }

  bool same_tree(Node* x, Node* y) {
    return get_root(x) == get_root(y);
  }
};


#include "testlib.h"


struct UnionFind {
    std::vector<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

int main() {
    registerValidation();

    int n = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "Q");
    inf.readChar('\n');

    std::vector<LinkCutTree::Node*> ns;
    LinkCutTree tree;

    for (int i = 0; i < n; i++) {
        inf.readInt(A_AND_X_MIN, A_AND_X_MAX, "a_i");
        if (i != n - 1) inf.readSpace();
        ns.push_back(tree.make_node(i));
    }
    inf.readChar('\n');



    auto uf = UnionFind(n);
    std::set<std::pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt(0, n - 1, "u_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "v_i");
        inf.readChar('\n');

        ensure(!uf.same(a, b));
        uf.merge(a, b);

        ensure(!tree.same_tree(ns[a], ns[b]));
        tree.evert(ns[a]);
        tree.link(ns[a], ns[b]);

        ensure(!edges.count(minmax(a, b)));
        edges.insert(minmax(a, b));
    }

    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 2, "t");        
        inf.readSpace();
        if(t == 0) {
            int u = inf.readInt(0, n - 1, "u");
            inf.readSpace();
            int v = inf.readInt(0, n - 1, "v");
            inf.readSpace();
            int w = inf.readInt(0, n - 1, "w");
            inf.readSpace();
            int x = inf.readInt(0, n - 1, "x");

            ensure(edges.count(minmax(u, v)));
            edges.erase(minmax(u, v));
            ensure(!edges.count(minmax(w, x)));
            edges.insert(minmax(w, x));

            tree.evert(ns[u]);
            tree.cut(ns[v]);

            ensure(!tree.same_tree(ns[w], ns[x]));
            tree.evert(ns[w]);
            tree.link(ns[w], ns[x]);
        }
        else if (t == 1) {
            inf.readInt(0, n - 1, "p");
            inf.readSpace();
            inf.readInt(A_AND_X_MIN, A_AND_X_MAX, "x");
        } else {
            inf.readInt(0, n - 1, "u");
            inf.readSpace();
            inf.readInt(0, n - 1, "v");
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
