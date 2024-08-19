#include <cstdio>
#include <memory>
#include <utility>
#include <vector>

struct node;
using ptr = std::shared_ptr<const node>;

struct node {
  int x;
  ptr next;

  node(int x, ptr next) : x(x), next(std::move(next)) {}
};

struct p_queue {
  using Self = p_queue;

  ptr f;
  ptr b;

  p_queue() = default;
  p_queue(ptr f, ptr b) : f(std::move(f)), b(std::move(b)) {}

  int front() const { return f->x; }
  Self push(int x) const {
    if (!f)
      return Self(std::make_shared<const node>(x, nullptr), nullptr);
    else
      return Self(f, std::make_shared<const node>(x, b));
  }
  Self pop() const {
    ptr f_ = f->next;
    ptr b_ = b;
    if (!f_) {
      while (b_) {
        f_ = std::make_shared<const node>(b_->x, std::move(f_));
        b_ = b_->next;
      }
    }
    return Self(std::move(f_), std::move(b_));
  }
};

int main() {
  int q;
  std::scanf("%d", &q);

  std::vector<p_queue> s_(q + 1);
  const auto s = s_.begin() + 1;

  for (int i = 0; i != q; i += 1) {
    int c;
    std::scanf("%d", &c);
    switch (c) {
    case 0: {
      int t, x;
      std::scanf("%d%d", &t, &x);
      s[i] = s[t].push(x);
    } break;
    case 1: {
      int t;
      std::scanf("%d", &t);
      std::printf("%d\n", s[t].front());
      s[i] = s[t].pop();
    }
    }
  }
}
