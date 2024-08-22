#include <cassert>
#include <memory>
#include <type_traits>
#include <utility>

template <class T> class persistent_queue {
  using Self = persistent_queue<T>;
  class node_type;
  using node_ptr = std::shared_ptr<node_type>;
  using raw_ptr = node_type *;
  class stream_type;
  using stream_ptr = std::shared_ptr<stream_type>;

  template <class... Args> static node_ptr make_node(Args &&... args) {
    return std::make_shared<node_type>(std::forward<Args>(args)...);
  }

  template <class... Args> static stream_ptr make_stream(Args &&... args) {
    return std::make_shared<stream_type>(std::forward<Args>(args)...);
  }

  class node_type {
  public:
    T value;
    node_ptr next;

    template <class Nptr>
    node_type(T value, Nptr &&n)
        : value(std::move(value)), next(std::forward<Nptr>(n)) {}
  };

  class stream_type {
  public:
    node_ptr scan;
    node_ptr rotate;

    template <class Rptr>
    stream_type(const node_ptr &s, Rptr &&r)
        : scan(s), rotate(std::forward<Rptr>(r)) {}

    node_ptr next() {
      node_ptr ret;
      if (scan) {
        ret = make_node(scan->value, nullptr);
        scan = scan->next;
      } else {
        while (rotate) {
          ret = make_node(rotate->value, std::move(ret));
          rotate = rotate->next;
        }
      }
      return ret;
    }
  };

  node_ptr f_st;
  raw_ptr proc;
  stream_ptr stream;
  node_ptr b_st;

  explicit persistent_queue(stream_ptr &&st)
      : f_st(st->next()), proc(f_st.get()), stream(std::move(st)), b_st() {}

  template <class Bptr>
  explicit persistent_queue(const node_ptr &f, const raw_ptr &p,
                            const stream_ptr &s, Bptr &&b)
      : f_st(f), proc(p), stream(s), b_st(std::forward<Bptr>(b)) {}

public:
  persistent_queue() : f_st(), proc(nullptr), stream(), b_st() {}

  const T &front() const { return f_st->value; }

  Self push(T x) const {
    if (!proc)
      return Self(make_stream(f_st, make_node(std::move(x), b_st)));
    if (!proc->next)
      proc->next = stream->next();
    return Self(f_st, proc->next.get(), stream, make_node(std::move(x), b_st));
  }

  Self pop() const {
    if (!proc)
      return Self(make_stream(f_st->next, b_st));
    if (!proc->next)
      proc->next = stream->next();
    return Self(f_st->next, proc->next.get(), stream, b_st);
  }
};

#include <cstdio>
#include <vector>

int main() {
  int q;
  std::scanf("%d", &q);

  std::vector<persistent_queue<int>> s_(q + 1);
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
