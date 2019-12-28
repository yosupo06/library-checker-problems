#include <utility>
#include <array>
#include <cassert>

using i64 = long long;

struct cluster {
  i64 length;

  using V = i64;
  cluster(i64 l): length(l) {}
  static cluster identity() {
    return cluster(0);
  }
  static cluster compress(const cluster& a, const cluster& b, V, V, V cv) {
    return cluster(
        a.length + b.length + cv
        );
  }
  static cluster rake(const cluster& a, const cluster&, V, V, V) {
    return cluster(
        a.length
        );
  }
  static cluster reverse(const cluster& c) {
    return c;
  }
  static std::size_t select(const cluster&, const cluster&, V, V, V) {
    return 0;
  }
};

class vertex;

class node;
int parent_dir(node*);
node* link(vertex, vertex, cluster);
void test_comp_set(node* n);

class vertex_raw {
  cluster::V val;
  node* hand;

public:

  vertex_raw(cluster::V val): val(val), hand(nullptr) {}

  node* handle() const { return this->hand; }
  void set_handle(node* hand) { this->hand = hand; }
  const cluster::V& value() const { return this->val; }
  void set_value(cluster::V val) {
    this->val = val;
  }
};

class vertex {
  vertex_raw* ver;

private:


public:

  static vertex dangling() { return vertex(); } 

  vertex(): ver(nullptr) {}
  vertex(cluster::V val): ver( new vertex_raw(val)) {
    vertex dummy;
    dummy.ver = new vertex_raw(cluster::V());
    link(*this, dummy, cluster::identity());
  }

  bool operator==(const vertex& other) { return this->ver == other.ver; }
  
  inline node* handle() const { return this->ver->handle(); }
  inline void set_handle(node* hand) { this->ver->set_handle(hand); }
  inline const cluster::V& value() const { return this->ver->value(); }
  inline void set_value(cluster::V val) { this->ver->set_value(val); }
};

enum class Type { Compress, Rake, Edge, None };

static std::size_t ni = 0;
extern node ns[2020202];

class node {
  node* ch[2];
  node* par;
  node* ra;
  node* me;
  bool rev;
  cluster fo;
  vertex v[2];
  Type ty;



public:

  node(): par(nullptr), ra(nullptr), me(nullptr), rev(false),
    fo(cluster::identity()), ty(Type::None) {} 



  static node* new_edge(vertex v, vertex u, cluster val) {
    //node* n = new node();
    node* n = ns + (ni++);
    n->v[0] = v;
    n->v[1] = u;
    n->fo = val;
    n->me = n;
    n->ty = Type::Edge;

    n->fix();

    return n;
  }

  static node* new_compress(node* left, node* right) {
    //node* n = new node();
    node* n = ns + (ni++);
    n->ch[0] = left;
    n->ch[1] = right;
    n->me = n;
    n->ty = Type::Compress;
    n->fix();
    return n;
  }

  static node* new_rake(node* left, node* right) {
    //node * n = new node();
    node* n = ns + (ni++);
    n->ch[0] = left;
    n->ch[1] = right;
    n->me = n;
    n->ty = Type::Rake;
    n->fix();
    return n;
  }

  inline void fix() {
    if(this->ty == Type::Edge) {
      if(!this->parent()) {
        this->endpoint(0).set_handle(this->me);
        this->endpoint(1).set_handle(this->me);
      }
      else if(this->parent()->ty == Type::Compress) {
        if(parent_dir(this->me) == -1) {
          this->endpoint(0).set_handle(this->me);
        }
      }
      else if(this->parent()->ty == Type::Rake) {
        this->endpoint(0).set_handle(this->me);
      }
    }
    else if(this->ty == Type::Compress) {
      this->push();
      this->v[0] = this->child(0)->endpoint(0);
      this->v[1] = this->child(1)->endpoint(1);
      assert(this->child(0)->endpoint(1) == this->child(1)->endpoint(0));

      cluster left = this->child(0)->fold();
      node* l = this->child(0);
      if(this->rake()) {
        node* r = this->rake();
        left = cluster::rake(l->fold(), r->fold(), l->endpoint(0).value(), r->endpoint(0).value(), l->endpoint(1).value());
      }
      node* r = this->child(1);
      this->fo= cluster::compress(left, r->fold(),
          l->endpoint(0).value(), r->endpoint(1).value(), l->endpoint(1).value());
      
      this->child(0)->endpoint(1).set_handle(this->me);

      if(!this->parent()) {
        this->endpoint(0).set_handle(this->me);
        this->endpoint(1).set_handle(this->me);
      }
      else if(this->parent()->ty == Type::Compress) {
        if(parent_dir(this->me) == -1) {
          this->endpoint(0).set_handle(this->me);
        }
      }
      else if(this->parent()->ty == Type::Rake) {
        this->endpoint(0).set_handle(this->me);
      }

    }
    else if(this->ty == Type::Rake) {
      this->push();
      this->v[0] = this->child(0)->endpoint(0);
      this->v[1] = this->child(0)->endpoint(1);
      this->fo = cluster::rake(this->child(0)->fold(), this->child(1)->fold(),
          this->child(0)->endpoint(0).value(), this->child(1)->endpoint(0).value(), this->child(0)->endpoint(1).value());
    }
    else { assert(false); }
  }

  inline void push() {
    if(this->ty == Type::Compress) {
      if(this->rev) {
        std::swap(this->ch[0], this->ch[1]);
        this->child(0)->reverse();
        this->child(1)->reverse();
        this->rev = false;
      }
    }
  }

  inline void reverse() {
    if(this->ty == Type::Edge) {
      std::swap(this->v[0], this->v[1]);
      this->fo = cluster::reverse(this->fold());
    }
    else if(this->ty == Type::Compress) {
      std::swap(this->v[0], this->v[1]);
      this->fo = cluster::reverse(this->fold());
      this->rev ^= true;
    }
    else if(this->ty == Type::Rake) {
    }
    else { assert(false); }
  }

  inline node* parent() const { return this->par; }
  inline void set_parent(node* par) { this->par = par; }
  inline node* rake() const { return this->ra; }
  inline void set_rake(node* rake) { this->ra = rake; }
  inline node* child(std::size_t dir) const { return this->ch[dir]; }
  inline void set_child(node* ch, std::size_t dir) { this->ch[dir] = ch; }
  inline vertex endpoint(std::size_t dir) { return this->v[dir]; }
  inline Type type() const { return this->ty; }

  cluster fold() const { return this->fo; }

  bool guard;
};

int parent_dir(node* child) {
  node* par = child->parent();
  if(par) {
    if(par->guard) { return -1; }
    else if(par->child(0) == child) { return 0; }
    else if(par->child(1) == child) { return 1; }
    else { return -1; }
  }
  else { return -1; }
}

int parent_dir_guard(node* child) {
  node* par = child->parent();
  if(par) {
    if(par->child(0) == child) { return 0; }
    else if(par->child(1) == child) { return 1; }
    else { return -1; }
  }
  else { return -1; }
}

void rotate(node* t, node* x, std::size_t dir) {
  node* y = x->parent();
  int par = parent_dir_guard(x);
  t->child(dir)->push();
  x->set_child(t->child(dir), dir ^ 1);
  t->child(dir)->set_parent(x);
  t->set_child(x, dir);
  x->set_parent(t);
  t->set_parent(y);
  if(par != -1) {
    y->set_child(t, par);
  }
  else if(y && y->type() == Type::Compress) {
    y->set_rake(t);
  }
  x->fix();
  t->fix();
  if(y && !y->guard) { y->fix(); }
}

void splay(node* t) {
  assert(t->type() != Type::Edge);
  t->push();

  while(parent_dir(t) != -1) {
    node* q = t->parent();
    if(q->type() != t->type()) break;
    if(parent_dir(q) != -1 && q->parent() && q->parent()->type() == q->type()) {
      node* r = q->parent();
      if(r->parent()) r->parent()->push();
      r->push();
      q->push();
      t->push();
      int qt_dir = parent_dir(t);
      int rq_dir = parent_dir(q);
      if(rq_dir == qt_dir) {
        rotate(q, r, rq_dir ^ 1);
        rotate(t, q, qt_dir ^ 1);
      }
      else {
        rotate(t, q, qt_dir ^ 1);
        rotate(t, r, rq_dir ^ 1);
      }
    }
    else {
      if(q->parent()) q->parent()->push();
      q->push();
      t->push();
      int qt_dir = parent_dir(t);
      rotate(t, q, qt_dir ^ 1);
    }
  }
}

node* expose_raw(node* t) {
  while(true) {
    assert(t->type() != Type::Rake);
    if(t->type() == Type::Compress) {
      splay(t);
    }
    node* n = nullptr;
    {
      node* par = t->parent();
      if(!par) { break; }
      else if(par->type() == Type::Rake) {
        par->push();
        splay(par);
        n = par->parent();
      }
      else if(par->type() == Type::Compress) {
        par->push();
        if(par->guard && parent_dir_guard(t) != -1) { break; }
        n = par;
      }
      else { assert(false); }
    }

    splay(n);

    
    int dir = parent_dir_guard(n);
    if(dir == -1 || n->parent()->type() == Type::Rake) dir = 0;
    if(dir == 1) {
      n->child(dir)->reverse();
      n->child(dir)->push();
      t->reverse();
      t->push();
    }
    int n_dir = parent_dir(t);
    if(n_dir != -1) {
      node* nch = n->child(dir);
      nch->push();
      node* rake = t->parent();
      rake->push();

      rake->set_child(nch, n_dir);
      nch->set_parent(rake);
      n->set_child(t, dir);
      t->set_parent(n);
      nch->fix();
      rake->fix();
      t->fix();
      n->fix();
      splay(rake);
    }
    else {
      node* nch = n->child(dir);
      nch->push();
      n->set_rake(nch);
      nch->set_parent(n);
      n->set_child(t, dir);
      t->set_parent(n);

      nch->fix();
      t->fix();
      n->fix();
    }
    if(t->type() == Type::Edge) {
      t = n;
    }
  }
  
  return t;
}

node* expose(vertex ver) {
  return expose_raw(ver.handle());
}

void soft_expose(vertex v, vertex u) {
  node* root = expose(v);
  if(v.handle() == u.handle()) {
    if(root->endpoint(1) == v || root->endpoint(0) == u) {
      root->reverse();
      root->push();
    }
    return;
  }
  root->guard = true;
  node* soot = expose(u);
  root->guard = false;
  root->fix();
  if(parent_dir(soot) == 0) {
    root->reverse();
    root->push();
  }
}

node* link(vertex v, vertex u, cluster weight) {
  if(!v.handle() && !u.handle()) {
    return node::new_edge(v, u, weight);
  }
  else {
    node* nnu = u.handle();
    node* nnv = v.handle();
    node* e = node::new_edge(v, u, weight);
    node* left = nullptr;

    if(!nnu) { left = e; }
    else {
      node* uu = expose_raw(nnu);
      uu->push();
      if(uu->endpoint(1) == u) {
        uu->reverse();
        uu->push();
      }
      if(uu->endpoint(0) == u) {
        node* nu = node::new_compress(e, uu);
        e->set_parent(nu);
        e->fix();
        uu->set_parent(nu);
        uu->fix();
        nu->fix();

        left = nu;
      }
      else {
        node* nu = uu;
        node* left_ch = nu->child(0);
        left_ch->push();

        nu->set_child(e, 0);
        e->set_parent(nu);
        e->fix();
        
        node* beta = nu->rake();
        node* rake = nullptr;
        if(beta) {
          beta->push();
          rake = node::new_rake(beta, left_ch);
          beta->set_parent(rake);
          left_ch->set_parent(rake);
          beta->fix();
          left_ch->fix();
        }
        else {
          rake = left_ch;
        }
        nu->set_rake(rake);
        rake->set_parent(nu);
        rake->fix();
        nu->fix();

        left = nu;
      }
    }

    if(!nnv) {}
    else {
      node* vv =expose_raw(nnv);
      vv->push();
      if(vv->endpoint(0) == v) {
        vv->reverse();
        vv->push();
      }
      if(vv->endpoint(1) == v) {
        node* top = node::new_compress(vv, left);
        vv->set_parent(top);
        left->set_parent(top);
        vv->fix();
        left->fix();
        top->fix();
      }
      else {
        node* nv = vv;
        node* right_ch = nv->child(1);
        right_ch->reverse();
        right_ch->push();

        nv->set_child(left, 1);
        left->set_parent(nv);
        left->fix();

        node* alpha = nv->rake();
        node* rake = nullptr;
        if(alpha) {
          alpha->push();
          rake = node::new_rake(alpha, right_ch);
          alpha->set_parent(rake);
          alpha->fix();
          right_ch->set_parent(rake);
          right_ch->fix();
        }
        else {
          rake = right_ch;
        }
        nv->set_rake(rake);
        rake->set_parent(nv);
        rake->fix();
        nv->fix();
      }
    }

    return e;
  }
}

void bring(node* root) {
  node* rake = root->rake();

  if(!rake) {
    node* left = root->child(0);
    //delete root, root = nullptr;
    left->set_parent(nullptr);
    left->fix();
  }
  else if(rake->type() == Type::Compress || rake->type() == Type::Edge) {
    rake->push();
    node* new_right = rake;
    new_right->reverse();
    new_right->push();

    root->set_child(new_right, 1);
    new_right->set_parent(root);

    root->set_rake(nullptr);

    new_right->fix();
    root->fix();
  }
  else if(rake->type() == Type::Rake) {
    rake->push();
    while(rake->child(1)->type() == Type::Rake) {
      rake->child(1)->push();
      rake = rake->child(1);
    }
    root->guard = true;
    splay(rake);
    root->guard = false;

    node* new_rake = rake->child(0);
    node* new_right = rake->child(1);

    //delete rake, rake = nullptr;
    new_right->reverse();
    new_right->push();

    root->set_child(new_right, 1);
    new_right->set_parent(root);

    root->set_rake(new_rake);
    new_rake->set_parent(root);

    new_rake->fix();
    new_right->fix();
    root->fix();
  }
}

void cut(vertex v, vertex u) {
  soft_expose(v, u);
  node* root = v.handle();
  root->push();
  node* right = root->child(1);
  right->set_parent(nullptr);

  right->reverse();
  right->push();

  bring(right);
  bring(root);
}

cluster path_query(vertex v, vertex u) {
  soft_expose(v, u);
  node* root = v.handle();
  root->push();
  if(root->endpoint(0) == v && root->endpoint(1) == u) {
    return root->fold();
  }
  else if(root->endpoint(0) == v) {
    return root->child(0)->fold();
  }
  else if(root->endpoint(1) == u) {
    return root->child(1)->fold();
  }
  else {
    root->child(1)->push();
    return root->child(1)->child(0)->fold();
  }
}


node ns[2020202];



#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

#include <cstdio>

namespace niu {
  char cur;
  struct FIN {
    static inline bool is_blank(char c) { return c <= ' '; }
    inline char next() { return cur = getc_unlocked(stdin); }
    inline char peek() { return cur; }
    inline void skip() { while(is_blank(next())){} }
#define intin(inttype)  \
    FIN& operator>>(inttype& n) { \
      bool sign = 0; \
      n = 0; \
      skip(); \
      while(!is_blank(peek())) { \
        if(peek() == '-') sign = 1; \
        else n = (n << 1) + (n << 3) + (peek() & 0b1111); \
        next(); \
      } \
      if(sign) n = -n; \
      return *this; \
    }
intin(int)
intin(long long)
  } fin;

  char tmp[128];
  struct FOUT {
    static inline bool is_blank(char c) { return c <= ' '; }
    inline void push(char c) { putc_unlocked(c, stdout); }
    FOUT& operator<<(char c) { push(c); return *this; }
    FOUT& operator<<(const char* s) { while(*s) push(*s++); return *this; }
#define intout(inttype) \
    FOUT& operator<<(inttype n) { \
      if(n) { \
        char* p = tmp + 127; bool neg = 0; \
        if(n < 0) neg = 1, n = -n; \
        while(n) *--p = (n % 10) | 0b00110000, n /= 10; \
        if(neg) *--p = '-'; \
        return (*this) << p; \
      } \
      else { \
        push('0'); \
        return *this; \
      } \
    }
intout(int)
intout(long long)
  } fout;
}


int main() {
  using niu::fin;
  using niu::fout;
  i64 N, Q;
  fin >> N >> Q;
  vector<vertex> vs;
  for(int i = 0;i < N;i++) {
    i64 a;
    fin >> a;
    vs.push_back(vertex(a));
  }
  for(int i = 0;i + 1 < N;i++) {
    i64 a, b;
    fin >> a >> b;
    link(vs[a], vs[b], cluster::identity());
  }
  for(int i = 0;i < Q;i++) {
    i64 c, a, b;
    fin >> c >> a >> b;
    if(c == 0) {
      i64 d;
      fin >> d;
      cut(vs[a], vs[b]);
      link(vs[b], vs[d], cluster::identity());
    }
    else if(c == 1) {
      auto node = expose(vs[a]);
      vs[a].set_value(vs[a].value() + b);
      node->fix();
    }
    else if(a == b) {
      fout << vs[a].value() << '\n';
    }
    else {
      fout << path_query(vs[a], vs[b]).length + vs[a].value() + vs[b].value() << '\n';
    }
  }
}
