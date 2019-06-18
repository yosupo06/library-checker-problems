#include <bits/stdc++.h>

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

template <class Mint> Mint calc_det(Mat<Mint> a) {
    assert(a.h() == a.w());
    int n = a.h();

    bool flip = false;
    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) return 0;
        if (x != my) {
            swap(a[x], a[my]);
            if ((x - my) % 2) flip = !flip;
        }
        for (int y = x + 1; y < n; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[x][x];
            for (int k = x; k < n; k++) a[y][k] -= freq * a[x][k];
        }
    }
    Mint det = (!flip ? 1 : -1);
    for (int i = 0; i < n; i++) {
        det *= a[i][i];
    }
    return det;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    int n;
    cin >> n;
    Mat<Mint> mat(n, V<Mint>(n, n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j].v;
        }
    }
    auto answer = calc_det(mat);
    cerr << "ANSWER: " << answer << endl;
    cout << answer << endl;
    return 0;
}
