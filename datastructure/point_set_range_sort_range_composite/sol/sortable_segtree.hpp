
template <typename Monoid, int NODES = 4'000'000>
struct Sortable_SegTree {
  using X = typename Monoid::value_type;
  const int N;

  struct Node {
    X x, rev_x;
    int size;
    Node *l, *r;
    Node() {}
  };

  Node* pool;
  int pid;

  // 区間の左端全体を表す fastset
  FastSet ss;
  // 区間を集約した値を区間の左端にのせた segtree
  SegTree<Monoid> seg;
  // 区間の左端に、dynamic segtree の node を乗せる
  vector<bool> rev;
  vector<Node*> root;
  Sortable_SegTree(vector<int> key, vector<X> dat)
      : N(key.size()), pid(0), ss(key.size()), seg(dat) {
    {
      // key を座圧
      auto tmp = key;
      sort(tmp.begin(), tmp.end());
      tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
      assert(int(tmp.size()) == N);
      for (auto&& k: key) {
        k = lower_bound(tmp.begin(), tmp.end(), k) - tmp.begin();
      }
    }
    pool = new Node[NODES];
    init(key, dat);
  }

  void set(int i, const X& x) {
    int l = ss.prev(i);
    int r = ss.next(l + 1);
    i = (rev[l] ? r - 1 - i : i - l);
    set_rec_idx(root[l], 0, N, i, x);
    seg.set(l, (rev[l] ? root[l]->rev_x : root[l]->x));
  }

  X prod_all() { return seg.prod_all(); }

  X prod(int l, int r) {
    if (pid > NODES * 0.9) rebuild();
    make_border(l), make_border(r);
    return seg.prod(l, r);
  }

  void sort_inc(int l, int r) {
    make_border(l), make_border(r);
    while (1) {
      if (pid > NODES * 0.9) rebuild();
      Node* n = root[l];
      int i = ss.next(l + 1);
      if (i == r) break;
      root[l] = merge(n, root[i]);
      ss.erase(i);
      seg.set(i, Monoid::unit());
    }
    rev[l] = 0;
    seg.set(l, root[l]->x);
  };

  void sort_dec(int l, int r) {
    if (pid > NODES * 0.9) rebuild();
    sort_inc(l, r);
    rev[l] = 1;
    seg.set(l, root[l]->rev_x);
  };

private:
  void init(vector<int>& key, vector<X>& dat) {
    rev.assign(N, 0);
    root.clear();
    seg.set_all(dat);
    for (int i = 0; i < N; ++i) ss.insert(i);
    for (int i = 0; i < N; ++i) root.emplace_back(new_node(Monoid::unit()));
    for (int i = 0; i < N; ++i) { set_rec_key(root[i], 0, N, key[i], dat[i]); }
  }

  void make_border(int x) {
    if (x == N || ss[x]) return;
    int a = ss.prev(x);
    int b = ss.next(a + 1);
    ss.insert(x);
    if (!rev[a]) {
      auto [nl, nr] = split(root[a], x - a);
      root[a] = nl;
      root[x] = nr;
      rev[a] = rev[x] = 0;
      seg.set(a, root[a]->x);
      seg.set(x, root[x]->x);
    } else {
      auto [nl, nr] = split(root[a], b - x);
      root[a] = nr;
      root[x] = nl;
      rev[a] = rev[x] = 1;
      seg.set(a, root[a]->rev_x);
      seg.set(x, root[x]->rev_x);
    }
  }

  void rebuild() {
    vector<int> key;
    vector<X> dat;
    key.reserve(N);
    dat.reserve(N);
    auto dfs
        = [&](auto& dfs, Node* n, int node_l, int node_r, bool rev) -> void {
      if (!n) return;
      if (node_r == node_l + 1) {
        key.emplace_back(node_l);
        dat.emplace_back(n->x);
        return;
      }
      int node_m = (node_l + node_r) / 2;
      if (!rev) {
        dfs(dfs, n->l, node_l, node_m, rev);
        dfs(dfs, n->r, node_m, node_r, rev);
      }
      if (rev) {
        dfs(dfs, n->r, node_m, node_r, rev);
        dfs(dfs, n->l, node_l, node_m, rev);
      }
    };
    for (int i = 0; i < N; ++i) {
      if (ss[i]) dfs(dfs, root[i], 0, N, rev[i]);
    }
    assert(int(key.size()) == N);

    pid = 0;
    init(key, dat);
  }

  Node* new_node(X x = Monoid::unit()) {
    assert(pid < NODES);
    pool[pid].x = pool[pid].rev_x = x;
    pool[pid].l = pool[pid].r = nullptr;
    pool[pid].size = 1;
    return &(pool[pid++]);
  }

  pair<Node*, Node*> split(Node* n, int k) {
    if (k == 0) { return {nullptr, n}; }
    if (k == n->size) { return {n, nullptr}; }
    int s = (n->l ? n->l->size : 0);
    Node* b = new_node();
    if (k <= s) {
      auto [nl, nr] = split(n->l, k);
      b->l = nr;
      b->r = n->r;
      n->l = nl;
      n->r = nullptr;
    }
    if (k > s) {
      auto [nl, nr] = split(n->r, k - s);
      n->l = n->l;
      n->r = nl;
      b->l = nullptr;
      b->r = nr;
    }
    update(n);
    update(b);
    return {n, b};
  }

  Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    a->l = merge(a->l, b->l);
    a->r = merge(a->r, b->r);
    update(a);
    return a;
  }

  void update(Node* n) {
    if (!(n->l) && !(n->r)) { return; }
    if (!(n->l)) {
      n->x = n->r->x, n->rev_x = n->r->rev_x;
      n->size = n->r->size;
      return;
    }
    if (!(n->r)) {
      n->x = n->l->x, n->rev_x = n->l->rev_x;
      n->size = n->l->size;
      return;
    }
    n->x = Monoid::op(n->l->x, n->r->x);
    n->rev_x = Monoid::op(n->r->rev_x, n->l->rev_x);
    n->size = n->l->size + n->r->size;
  }

  void set_rec_key(Node* n, int node_l, int node_r, int k, const X& x) {
    if (node_r == node_l + 1) {
      n->x = n->rev_x = x;
      return;
    }
    int node_m = (node_l + node_r) / 2;
    if (k < node_m) {
      if (!(n->l)) n->l = new_node();
      set_rec_key(n->l, node_l, node_m, k, x);
    }
    if (node_m <= k) {
      if (!(n->r)) n->r = new_node();
      set_rec_key(n->r, node_m, node_r, k, x);
    }
    update(n);
  }

  void set_rec_idx(Node* n, int node_l, int node_r, int idx, const X& x) {
    if (node_r == node_l + 1) {
      n->x = n->rev_x = x;
      return;
    }
    int node_m = (node_l + node_r) / 2;
    int s = (n->l ? n->l->size : 0);
    if (idx < s) { set_rec_idx(n->l, node_l, node_m, idx, x); }
    if (idx >= s) { set_rec_idx(n->r, node_m, node_r, idx - s, x); }
    update(n);
  }
};