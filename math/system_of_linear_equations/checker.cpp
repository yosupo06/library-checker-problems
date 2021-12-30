#include <algorithm>
#include <vector>
#include <string>
#include "testlib.h"

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
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
const int MD = 998244353;
using Mint = ModInt<MD>;
// template<> const Mint Mint::G = Mint(3);

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
    V<D> operator*(const V<D>& r) const {
        V<D> res(h());
        for (int i = 0; i < h(); i++) {
            for (int j = 0; j < w(); j++) {
                res[i] += (*this)[i][j] * r[j];
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

template <class Mint> int calc_rank(Mat<Mint> a) {
    int h = a.h(), w = a.w();
    int r = 0;
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
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[r][x];
            for (int k = x; k < w; k++) a[y][k] -= freq * a[r][k];
        }
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    return r;
}

using Vec = V<Mint>;
using M = Mat<Mint>;

int n, m;
M a;
Vec b;

#include <iostream>
// return rank of answer
int read_ans(InStream& stream) {
    int r = stream.readInt(-1, m);

    if (r == -1) return -1;

    Vec c(m);
    for (int i = 0; i < m; i++) {
        c[i].v = stream.readInt(0, MD - 1);
    }

    if (a * c != b) stream.quitf(_wa, "a * c != b");

    if(r == 0) return 0;

    M ds(r);
    for (int ph = 0; ph < r; ph++) {
        Vec d(m);
        for (int i = 0; i < m; i++) {
            d[i] = stream.readInt(0, MD - 1);
        }
        ds[ph] = d;
        Vec cd(m);
        for (int i = 0; i < m; i++) {
            cd[i] = c[i] + d[i];
        }
        if (a * cd != b) stream.quitf(_wa, "a * (c + d) != b");
    }

    if (calc_rank(ds) != r) {
        stream.quitf(_wa, "d is not linearly independent");
    }

    return r;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    n = inf.readInt();
    m = inf.readInt();

    a = M(n, Vec(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = inf.readInt();
        }
    }

    b = Vec(n);
    for (int i = 0; i < n; i++) {
        b[i] = inf.readInt();
    }

    int k_ans = read_ans(ans);
    int k_ouf = read_ans(ouf);

    if (k_ans == -1 && k_ouf == -1) {
        quitf(_ok, "OK No solution");
    }
    if (k_ans != -1 && k_ouf == -1) {
        quitf(_wa, "WA you cannot find solution");
    }
    if (k_ans == -1 && k_ouf != -1) {
        quitf(_fail, "Judge cannot find solution");
    }
    if (k_ans > k_ouf) {
        quitf(_wa, "There are more solutions");
    }
    if (k_ans < k_ouf) {
        quitf(_fail, "What happened?");
    }
    quitf(_ok, "OK");
}
