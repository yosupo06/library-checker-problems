#include <cassert>
#include <cstdio>
#include <limits>
#include <map>
#include <vector>
using namespace std;

template <typename Info> struct SplayTree {
  using info_t = Info;
  struct Node : public Info {
    Node *lch, *rch, *fa;
    Node(Info info) : Info(info), lch(nullptr), rch(nullptr), fa(nullptr){};
  };
  Node *root;
  SplayTree() : root(nullptr) {}
  Node *Update(Node *x) {
    x->Update();
    return x;
  }
  void PushDown(Node *x) {
    if (x->NeedPushDown()) {
      x->PushDown();
    }
  }

  void Zig(Node *t) {
    auto y = t->fa;
    PushDown(y), PushDown(t);
    t->fa = y->fa;
    if (y->fa) {
      if (y == y->fa->lch)
        y->fa->lch = t;
      else
        y->fa->rch = t;
    }
    y->lch = t->rch;
    if (t->rch)
      t->rch->fa = y;
    t->rch = y;
    y->fa = t;
    Update(y), Update(t);
  }

  void Zag(Node *t) {
    auto y = t->fa;
    PushDown(y), PushDown(t);
    t->fa = y->fa;
    if (y->fa) {
      if (y == y->fa->lch)
        y->fa->lch = t;
      else
        y->fa->rch = t;
    }
    y->rch = t->lch;
    if (t->lch)
      t->lch->fa = y;
    t->lch = y;
    y->fa = t;
    Update(y), Update(t);
  }

  void Splay(Node *t, Node *p = nullptr) {
    assert(t);
    while (t->fa != p) {
      auto y = t->fa;
      if (y->fa == p) {
        if (t == y->lch)
          Zig(t);
        else
          Zag(t);
      } else {
        if (y == y->fa->lch) {
          if (t == y->lch)
            Zig(y), Zig(t);
          else
            Zag(t), Zig(t);
        } else {
          if (t == y->rch)
            Zag(y), Zag(t);
          else
            Zig(t), Zag(t);
        }
      }
    }
    if (!p)
      root = t;
  }
};

template <typename Info> struct LinkCutTree {
  struct SplayInfo : public Info {
    typename SplayTree<SplayInfo>::Node *Node() {
      return reinterpret_cast<typename SplayTree<SplayInfo>::Node *>(this);
    }
    bool rev;
    int id, upid;
    SplayInfo() : rev(false), upid(-1) {}
    void Reverse() {
      auto x = Node();
      std::swap(x->lch, x->rch);
      rev ^= 1;
      Info::Reverse();
    }
    bool NeedPushDown() { return rev || Info::NeedPushDown(); }
    void PushDown() {
      auto lch = Node()->lch, rch = Node()->rch;
      if (rev) {
        if (lch)
          lch->Reverse();
        if (rch)
          rch->Reverse();
        rev = false;
      }
      if (Info::NeedPushDown()) {
        Info::PushDown(lch ? (Info *)lch : nullptr,
                       rch ? (Info *)rch : nullptr);
      }
    }
    void Update() {
      auto lch = Node()->lch, rch = Node()->rch;
      Info::Update(lch ? (Info *)lch : nullptr, rch ? (Info *)rch : nullptr);
    }
  };

  using Node = typename SplayTree<SplayInfo>::Node;

  int n;
  std::vector<Node *> node;
  SplayTree<SplayInfo> splay;
  LinkCutTree(int n_) : n(0) { ExpandTo(n_); }
  void ExpandTo(int m) {
    if (m <= n)
      return;
    node.resize(m);
    for (int i = n; i < m; i++) {
      SplayInfo info;
      info.id = i;
      node[i] = new Node(info);
    }
    n = m;
  }
  void Splay(Node *x) {
    auto y = x;
    while (y->fa)
      y = y->fa;
    splay.Splay(x);
    std::swap(x->upid, y->upid);
    x->Update();
  }
  void Splay(int x) { Splay(node[x]); }
  void Access(Node *x) {
    for (Node *y = nullptr; x;
         y = x, x = x->upid == -1 ? nullptr : node[x->upid]) {
      Splay(x);
      splay.PushDown(x);
      if (x->rch)
        x->rch->fa = nullptr, x->rch->upid = x->id;
      x->rch = y;
      if (y)
        y->fa = x, y->upid = -1;
      splay.Update(x);
    }
  }
  void Access(int x) { Access(node[x]); }
  Node *GetRoot(Node *x) {
    Access(x);
    Splay(x);
    while (x->lch) {
      splay.PushDown(x);
      x = x->lch;
    }
    Splay(x);
    return x;
  }
  int GetRoot(int x) { return GetRoot(node[x])->id; }
  void MakeRoot(Node *x) {
    Access(x);
    Splay(x);
    x->Reverse();
  }
  void MakeRoot(int x) { MakeRoot(node[x]); }
  void Link(Node *x, Node *y) {
    MakeRoot(x);
    x->upid = y->id;
  }
  void Link(int x, int y) { Link(node[x], node[y]); }
  void Cut(Node *x, Node *y) {
    MakeRoot(x);
    Access(y);
    Splay(y);
    x->fa = y->lch = nullptr;
    y->Update();
    x->upid = -1;
  }
  void Cut(int x, int y) { Cut(node[x], node[y]); }
};

struct Info {
  int val, edge_id;
  pair<int, int> max_val;
  Info()
      : val(std::numeric_limits<int>::min()), edge_id(-1),
        max_val({std::numeric_limits<int>::min(), -1}) {}
  void Reverse() {}
  bool NeedPushDown() { return false; }
  void PushDown(Info *, Info *) {}
  void Update(Info *a, Info *b) {
    max_val = {val, edge_id};
    if (a)
      max_val = max(max_val, a->max_val);
    if (b)
      max_val = max(max_val, b->max_val);
  }
};

struct IncrementalMinimumSpanningForest {
  int n;
  LinkCutTree<Info> lct;
  vector<pair<int, int>> edges;
  map<int, int> rec;
  IncrementalMinimumSpanningForest(int n_) : n(n_), lct(2 * n - 1) {}

  int AddEdge(int u, int v, int w, int id) {
    if (lct.GetRoot(u) == lct.GetRoot(v)) {
      lct.MakeRoot(u);
      lct.Access(v);
      lct.Splay(v);
      auto [max_w, max_id] = lct.node[v]->max_val;
      if (w > max_w) {
        return id;
      }
      int p = rec[max_id];
      lct.Cut(p + n, edges[p].first);
      lct.Cut(p + n, edges[p].second);
      edges[p] = {u, v};
      rec[id] = p;
      lct.node[p + n]->val = w;
      lct.node[p + n]->edge_id = id;
      lct.node[p + n]->max_val = {w, id};
      lct.Link(u, p + n);
      lct.Link(v, p + n);
      return max_id;
    } else {
      edges.emplace_back(u, v);
      int p = edges.size() - 1;
      rec[id] = p;
      lct.node[p + n]->val = w;
      lct.node[p + n]->edge_id = id;
      lct.node[p + n]->max_val = {w, id};
      lct.Link(u, p + n);
      lct.Link(v, p + n);
      return -1;
    }
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  IncrementalMinimumSpanningForest T(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    int ans = T.AddEdge(u, v, w, i);
    printf("%d ", ans);
  }
  printf("\n");

  return 0;
}
