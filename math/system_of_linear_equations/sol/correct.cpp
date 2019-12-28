#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;
template<> const Mint Mint::G = Mint(3);

template <class D> struct Mat : VV<D> {
    using VV<D>::VV;
    using VV<D>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
    Mat operator*(const Mat& r) const {
        assert(w() == r.h());
        Mat res(h(), V<D>(r.w()));
        for (int i = 0; i < h(); i++) {
            for (int j = 0; j < r.w(); j++) {
                for (int k = 0; k < w(); k++) {
                    res[i][j] += (*this)[i][k] * r[k][j];
                }
            }
        }
        return res;
    }
    Mat& operator*=(const Mat& r) { return *this = *this * r; }
    Mat pow(ll n) const {
        assert(h() == w());
        Mat x = *this, r(h(), V<D>(w()));
        for (int i = 0; i < h(); i++) r[i][i] = D(1);
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

template <class Mint> VV<Mint> solve_linear(Mat<Mint> a, V<Mint> b) {
    int h = a.h(), w = a.w();
    assert(int(b.size()) == h);
    int r = 0;
    V<bool> used(w);
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = r; y < h; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (r != my) swap(a[r], a[my]);
        swap(b[r], b[my]);
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[r][x];
            for (int k = x; k < w; k++) a[y][k] -= freq * a[r][k];
            b[y] -= freq * b[r];
        }
        r++;
        used[x] = true;
        idxs.push_back(x);
        if (r == h) break;
    }
    for (int y = r; y < h; y++) {
        if (b[y]) return {};
    }
    VV<Mint> sols;
    {
        V<Mint> v(w);
        for (int y = r - 1; y >= 0; y--) {
            int f = idxs[y];
            v[f] = b[y];
            for (int x = f + 1; x < w; x++) {
                v[f] -= a[y][x] * v[x];
            }
            v[f] /= a[y][f];
        }
        sols.push_back(v);
    }
    for (int s = 0; s < w; s++) {
        if (used[s]) continue;
        V<Mint> v(w);
        v[s] = Mint(1);
        for (int y = r - 1; y >= 0; y--) {
            int f = idxs[y];
            for (int x = f + 1; x < w; x++) {
                v[f] -= a[y][x] * v[x];
            }
            v[f] /= a[y][f];
        }
        sols.push_back(v);
    }
    return sols;
}

int main() {


    int n, m;
    cin >> n >> m;
    Mat<Mint> mat(n, V<Mint>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j].v;
        }
    }
    V<Mint> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].v;
    }
    auto answer = solve_linear(mat, vec);
    if (answer.empty()) {
        cout << -1 << endl;
        return 0;
    }

    cout << answer.size() - 1 << endl;

    for (auto v: answer) {
        assert(int(v.size()) == m);
        for (int i = 0; i < m; i++) {
            cout << v[i];
            if (i != m - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
