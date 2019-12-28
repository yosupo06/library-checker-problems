#include <iostream>
#include <deque>
#include <cassert>
#include <tuple>

using namespace std;
using ll = long long;

template <class D, class Op> struct SWAG {
    D e;
    Op op;
    deque<D> data;
    int front;
    D back;

    SWAG(D e_, Op op_) : e(e_), op(op_) {
        front = 0;
        back = e;
    }

    void push(D x) {
        data.push_back(x);
        back = op(back, x);
    }

    void pop() {
        assert (not data.empty());
        data.pop_front();
        if (front) {
            -- front;
        } else {
            for (int i = (int)data.size() - 2; i >= 0; i--) {
                data[i] = op(data[i], data[i + 1]);
            }
            front = data.size();
            back = e;
        }
    }

    D sum() const {
        return front ? op(data.front(), back) : back;
    }
};

const ll MOD = 998244353;

int main() {
    constexpr char endl = '\n';

    int q;
    cin >> q;

    struct F {
        ll a, b;
    };
    auto op = [&](F l, F r) -> F {
        ll na = l.a * r.a % MOD;
        ll nb = (l.b * r.a + r.b) % MOD;
        return F{na, nb};
    };
    SWAG<F, decltype(op)> swag({1, 0}, op);

    for (int i = 0; i < q; i++) {
        int ty;
        cin >> ty;
        if (ty == 0) {
            ll a, b;
            cin >> a >> b;
            swag.push({a, b});
        } else if (ty == 1) {
            swag.pop();
        } else {
            ll x;
            cin >> x;
            F f = swag.sum();
            cout << (f.a * x + f.b) % MOD << endl;
        }
    }
    return 0;
}
