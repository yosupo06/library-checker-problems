#include <cstdio>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>
#include <utility>
#include <cstdint>
#include "random.h"
using namespace std;
#define ll long long
#define out(x) cout<<x<<'\n'
#define all(v) v.begin(),v.end()

namespace data_structure {

auto gen = Random(0);

template <typename S, typename F>
struct Node {
    Node *l = nullptr, *r = nullptr;
    uint32_t priority;
    int size = 1;
    S value;
    S sum;
    F lazy;
    bool rev = false;
    Node() = default;
    Node(S v, F f) : priority(gen.uniform(-1e9, 1e9)), value(v), sum(v), lazy(f) {}
};

template <
    typename S, typename F,
    S (*op)(S, S),
    S (*e)(),
    S (*mapping)(F, S),
    F (*composition)(F, F),
    F (*id)()
>
class ImplicitTreap {
private:
    using T = Node<S, F>;
    T* root = nullptr;
    std::vector<T> node_pool;
    int pool_ptr = 0;

    T* create_node(S val) {
        assert(pool_ptr < (int)node_pool.size());
        return new (&node_pool[pool_ptr++]) T(val, id());
    }

    inline int size(T* t) const { return t ? t->size : 0; }
    inline S sum(T* t) const { return t ? t->sum : e(); }

    inline void push(T* t) {
        if (!t) return;
        if (t->rev) {
            std::swap(t->l, t->r);
            if (t->l) t->l->rev ^= true;
            if (t->r) t->r->rev ^= true;
            t->rev = false;
        }
        if (t->lazy != id()) {
            if (t->l) {
                t->l->lazy = composition(t->lazy, t->l->lazy);
                t->l->sum = mapping(t->lazy, t->l->sum);
            }
            if (t->r) {
                t->r->lazy = composition(t->lazy, t->r->lazy);
                t->r->sum = mapping(t->lazy, t->r->sum);
            }
            t->value = mapping(t->lazy, t->value);
            t->lazy = id();
        }
    }

    inline T* update(T* t) {
        if (t) {
            t->size = 1 + size(t->l) + size(t->r);
            t->sum = op(op(sum(t->l), t->value), sum(t->r));
        }
        return t;
    }

    std::pair<T*, T*> split(T* t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        int left_size = size(t->l);
        if (k <= left_size) {
            auto s = split(t->l, k);
            t->l = s.second;
            return {s.first, update(t)};
        } else {
            auto s = split(t->r, k - left_size - 1);
            t->r = s.first;
            return {update(t), s.second};
        }
    }

    T* merge(T* l, T* r) {
        if (!l || !r) return l ? l : r;
        push(l);
        push(r);
        if (l->priority > r->priority) {
            l->r = merge(l->r, r);
            return update(l);
        } else {
            r->l = merge(l, r->l);
            return update(r);
        }
    }

    T* build_recursive(const std::vector<S>& v, int l, int r) {
        if (l >= r) return nullptr;
        int mid = l + (r - l) / 2;
        T* t = create_node(v[mid]);
        t->l = build_recursive(v, l, mid);
        t->r = build_recursive(v, mid + 1, r);
        return update(t);
    }

public:
    ImplicitTreap(int max_nodes) {
        node_pool.resize(max_nodes);
    }

    void build(const std::vector<S>& v) {
        if (v.empty()) {
            root = nullptr;
            return;
        }
        root = build_recursive(v, 0, (int)v.size());
    }

    int size() const { return size(root); }
    bool empty() const { return !root; }

    S get(int k) {
        auto s1 = split(root, k);
        auto s2 = split(s1.second, 1);
        S res = s2.first->value;
        root = merge(merge(s1.first, s2.first), s2.second);
        return res;
    }

    void set(int k, S val) {
        auto s1 = split(root, k);
        auto s2 = split(s1.second, 1);
        s2.first->value = val;
        update(s2.first);
        root = merge(merge(s1.first, s2.first), s2.second);
    }

    void insert(int k, S val) {
        auto s = split(root, k);
        T* new_node = create_node(val);
        root = merge(merge(s.first, new_node), s.second);
    }

    void erase(int k) {
        auto s1 = split(root, k);
        auto s2 = split(s1.second, 1);
        root = merge(s1.first, s2.second);
    }

    void update(int l, int r, F f) {
        if (l >= r) return;
        auto s1 = split(root, l);
        auto s2 = split(s1.second, r - l);
        s2.first->lazy = composition(f, s2.first->lazy);
        s2.first->sum = mapping(f, s2.first->sum);
        root = merge(merge(s1.first, s2.first), s2.second);
    }

    S query(int l, int r) {
        if (l >= r) return e();
        auto s1 = split(root, l);
        auto s2 = split(s1.second, r - l);
        S res = sum(s2.first);
        root = merge(merge(s1.first, s2.first), s2.second);
        return res;
    }

    void reverse(int l, int r) {
        if (l >= r) return;
        auto s1 = split(root, l);
        auto s2 = split(s1.second, r - l);
        s2.first->rev ^= true;
        root = merge(merge(s1.first, s2.first), s2.second);
    }

    void dump(std::ostream& os) {
        std::vector<S> v;
        std::function<void(T*)> rec =
            [&](T* t) {
            if (!t) return;
            push(t);
            rec(t->l);
            v.push_back(t->value);
            rec(t->r);
        };
        rec(root);
        os << "[ ";
        for(size_t i = 0; i < v.size(); ++i) {
            os << v[i] << (i == v.size() - 1 ? "" : ", ");
        }
        os << " ]" << std::endl;
    }
};

} 

const ll INF = (1LL<<60);
namespace Monoid {
    using S = ll;
    using F = ll;
    Monoid::S e() { return INF; }
    Monoid::F id() { return 0; }
    Monoid::S op(Monoid::S a, Monoid::S b) { return std::min(a, b); }
    Monoid::S mapping(Monoid::F f, Monoid::S x) { return x + f; }
    Monoid::F composition(Monoid::F f, Monoid::F g) { return f + g; }
}

using Treap = data_structure::ImplicitTreap<Monoid::S, Monoid::F, Monoid::op, Monoid::e, Monoid::mapping, Monoid::composition, Monoid::id>;

int main() {
    ll n, q;
    scanf("%lld%lld", &n, &q);
    Treap treap(n + q);
    vector<Monoid::S> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    treap.build(a);
    while (q--) {
        ll type;scanf("%lld", &type);
        if (type == 0) {
            ll l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            treap.update(l, r, x);
        } else {
            ll l, r;scanf("%lld%lld", &l, &r);
            printf("%lld\n", treap.query(l, r));
        }
    }
}
