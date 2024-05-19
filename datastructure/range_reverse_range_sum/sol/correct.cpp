#include <cstdint>
#include <cstdio>
#include <memory>
#include <random>
#include <utility>

using ll = long long;
using u64 = std::uint_fast64_t;
std::mt19937_64 rng(0x1757C90436F3E0B3);

struct node;
using ptr = std::unique_ptr<node>;
struct node {
  ptr l, r;
  u64 pri;
  ll a, sum;
  int size;
  bool rev;

  node(ll a_) : l(), r(), pri(rng()), a(a_), sum(a_), size(1), rev(false) {}
};

int size(const ptr &p) { return p ? p->size : 0; }
ll sum(const ptr &p) { return p ? p->sum : 0; }
void rev(const ptr &p) {
  if (p)
    p->rev ^= 1;
}
void push(const ptr &p) {
  using std::swap;
  if (p->rev) {
    p->rev = false;
    swap(p->l, p->r);
    rev(p->l);
    rev(p->r);
  }
}
void update(const ptr &p) {
  p->size = size(p->l) + 1 + size(p->r);
  p->sum = sum(p->l) + p->a + sum(p->r);
}

std::pair<ptr, ptr> split(ptr p, int i) {
  if (!p)
    return {nullptr, nullptr};
  push(p);
  const int s = size(p->l);
  if (s >= i) {
    auto [l, r] = split(std::move(p->l), i);
    p->l = std::move(r);
    update(p);
    return {std::move(l), std::move(p)};
  } else {
    auto [l, r] = split(std::move(p->r), i - s - 1);
    p->r = move(l);
    update(p);
    return {std::move(p), std::move(r)};
  }
}

ptr merge(ptr l, ptr r) {
  if (!l)
    return r;
  if (!r)
    return l;
  if (l->pri < r->pri) {
    push(r);
    r->l = merge(std::move(l), std::move(r->l));
    update(r);
    return r;
  } else {
    push(l);
    l->r = merge(std::move(l->r), std::move(r));
    update(l);
    return l;
  }
}

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  ptr root;
  for (int i = 0; i < N; i++) {
    int a;
    scanf("%d", &a);
    root = merge(std::move(root), std::make_unique<node>(a));
  }
  for (int j = 0; j < Q; j++) {
    int t, l, r;
    scanf("%d%d%d", &t, &l, &r);
    auto [xy, z] = split(std::move(root), r);
    auto [x, y] = split(std::move(xy), l);
    if (t == 0) {
      rev(y);
    } else {
      printf("%lld\n", sum(y));
    }
    xy = merge(std::move(x), std::move(y));
    root = merge(std::move(xy), std::move(z));
  }
}
