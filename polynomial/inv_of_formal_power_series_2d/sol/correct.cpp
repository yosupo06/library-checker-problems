#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <deque>
#include <cstring>
#include <time.h>
#include <cstdio>
#include <tuple>

template<typename T = int>inline T get() {
    char c = getchar(); bool neg = (c == '-');
    T res = neg ? 0 : c - '0'; while (isdigit(c = getchar()))res = res * 10 + (c - '0');
    return neg ? -res : res;
}

template<typename T = int>inline void put(T x, char c = '\n') {
    if (x == 0)putchar('0');
    else {
        if (x < 0) std::putchar('-'), x *= -1;
        int d[20], i = 0;
        while (x)d[i++] = x % 10, x /= 10;
        while (i--) std::putchar('0' + d[i]);
    } putchar(c);
}


constexpr long long     p = 998244353;
constexpr long long  root = 3;
constexpr long long iroot = 332748118;
inline int ADD(const int a, const int b) {
    return a + b >= p ? a + b - p : a + b;
}

inline int SUB(const int a, const int b) {
    return a - b < 0 ? a - b + p : a - b;
}

int deg(const std::vector<int>& a) {
    int ret = a.size() - 1;
    while (ret >= 0 && a[ret] == 0) --ret;
    return ret;
}

std::vector<int> trim(std::vector<int> a, const int n) {
    int asize = a.size();
    a.resize(n);
    for (int i = asize; i < n; ++i) a[i] = 0;
    return a;
}

void norm(std::vector<int>& a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

//f->fx^(shift)
std::vector<int> shift(std::vector<int>& a, const int shift) {
    std::vector<int> b(std::max(0, (int)a.size() + shift), 0);
    for (int i = 0; i < (int)b.size(); ++i) b[i] = (0 <= i - shift && i - shift < (int)a.size()) ? a[i - shift] : 0;
    return b;
}

inline long long pow_mod(long long a, long long n) {
    long long ret = 1;
    for (; n > 0; n >>= 1, a = a * a % p) if (n % 2 == 1) ret = ret * a % p;
    return ret;
}

inline int inv(int a) {
    a %= p;
    if (a < 0) a += p;
    int u = p;
    int v = a;
    int s = 0;
    int t = 1;
    // sa=u
    // ta=v
    while (v != 0) {
        int q = u / v;
        s -= q * t; u -= q * v;
        std::swap(s, t);
        std::swap(u, v);
    }
    assert((long long)a * (s + p) % p == 1);
    return s >= 0 ? s : s + p;
}

void monic(std::vector<int>& a) {
    norm(a);
    long long coe = inv(a[a.size() - 1]);
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] = (int)(coe * a[i] % p);
    }
}

std::vector<int> add(std::vector<int> a, std::vector<int> b) {
    int n = std::max(a.size(), b.size());
    a.resize(n); b.resize(n);
    for (int i = 0; i < n; ++i) a[i] = ADD(a[i], b[i]);
    return a;
}

std::vector<int> subtract(std::vector<int> a, std::vector<int> b) {
    int n = std::max(a.size(), b.size());
    a.resize(n); b.resize(n);
    for (int i = 0; i < n; ++i) a[i] = ADD(a[i], p - b[i]);
    return a;
}

std::vector<int> mul_naive(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> ret(a.size() + b.size() - 1, 0);
    if (a.size() < b.size()) {
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = 0; j < (int)b.size(); ++j) {
                ret[i + j] = (int)((ret[i + j] + 1LL * a[i] * b[j]) % p);
            }
        }
    }
    else {
        for (int j = 0; j < (int)b.size(); ++j) {
            for (int i = 0; i < (int)a.size(); ++i) {
                ret[i + j] = (int)((ret[i + j] + 1LL * a[i] * b[j]) % p);
            }
        }
    }
    norm(ret);
    return ret;
}

void fft_(int n, int g, int stride, std::vector<int>& from, std::vector<int>& to, bool flag) {
    if (n == 1) {
        if (flag) for (int i = 0; i < stride; ++i) to[i] = from[i];
        return;
    }
    else {
        int w = pow_mod(g, (p - 1) / n);
        int mul = 1;
        for (int i = 0; i < n / 2; ++i) {
            for (int src = 0; src < stride; ++src) {
                int A = from[src + stride * (i + 0)];
                int B = from[src + stride * (i + n / 2)];
                to[src + stride * (2 * i + 0)] = ADD(A, B);
                to[src + stride * (2 * i + 1)] = 1LL * SUB(A, B) * mul % p;
            }
            mul = 1LL * mul * w % p;
        }
        fft_(n / 2, g, 2 * stride, to, from, !flag);
    }
}

void fft4_(int n, int g, int j, int stride, std::vector<int>& from, std::vector<int>& to, bool flag) {
    int w = pow_mod(g, (p - 1) / n);
    long long w1, w2, w3;
    int i, src, n0, n1, n2, n3, A, B, C, D, apc, amc, bpd, jbmd;

    while (n > 2) {
        n0 = 0;
        n1 = n / 4;
        n2 = n1 + n1;
        n3 = n1 + n2;
        w1 = 1;
        for (i = 0; i < n1; ++i) {
            w2 = w1 * w1 % p;
            w3 = w1 * w2 % p;
            for (src = 0; src < stride; ++src) {
                A = from[src + stride * (i + n0)];
                B = from[src + stride * (i + n1)];
                C = from[src + stride * (i + n2)];
                D = from[src + stride * (i + n3)];
                apc = ADD(A, C);
                amc = SUB(A, C);
                bpd = ADD(B, D);
                jbmd = 1LL * j * SUB(B, D) % p;
                to[src + stride * (4 * i + 0)] = ADD(apc, bpd);
                to[src + stride * (4 * i + 1)] = w1 * (amc + p - jbmd) % p;
                to[src + stride * (4 * i + 2)] = w2 * (A + C + p - bpd) % p;
                to[src + stride * (4 * i + 3)] = w3 * (A + p - C + jbmd) % p;
            }
            w1 = 1LL * w1 * w % p;
        }
        n /= 4;
        stride *= 4;
        flag = !flag;
        w = 1LL * w * w % p;
        w = 1LL * w * w % p;
        std::swap(to, from);
    }
    if (n <= 2) fft_(n, g, stride, from, to, flag);
    if (from.size() > to.size()) std::swap(from, to);
}

std::vector<int> tmp_fft(1 << 22);
void fft(std::vector<int>& a, int g) {
    fft4_(a.size(), g, pow_mod(g, (p - 1) / 4 * 3), 1, a, tmp_fft, false);
}

//  (sx^p+u)(tx^p+v)
// =stx^(2p)+(sv+ut)x^p+uv
// =stx^(2p)+((s+u)(t+v)-(st-uv))x^p+uv
void mul_karatsuba(int a[], int b[], int c[], int res[], int n) {
    if (n <= 8) {
        for (int i = 0; i < 2 * n; ++i) res[i] = 0;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) res[i + j] = ADD(res[i + j], (int)(1LL * a[i] * b[j] % p));
        return;
    }
    int* x0 = res;
    int* x1 = res + n;
    int* x2 = res + n * 2;
    int* a0 = a;
    int* a1 = a + n / 2;
    int* b0 = b;
    int* b1 = b + n / 2;
    int* c0 = c;
    int* c1 = c + n / 2;
    mul_karatsuba(a0, b0, c + n * 2, x0, n / 2);
    mul_karatsuba(a1, b1, c + n * 2, x1, n / 2);
    for (int i = 0; i < n / 2; ++i) {
        c0[i] = ADD(a0[i], a1[i]);
        c1[i] = ADD(b0[i], b1[i]);
    }
    mul_karatsuba(c0, c1, c + n * 2, x2, n / 2);
    for (int i = 0; i < n; ++i) {
        x2[i] = SUB(SUB(x2[i], x0[i]), x1[i]);
    }
    for (int i = 0; i < n; ++i) {
        res[i + n / 2] = ADD(res[i + n / 2], x2[i]);
    }
}

std::vector<int> mul_fft(std::vector<int> a, std::vector<int> b) {
    int n = 1;
    int need = a.size() + b.size() - 1;
    while (n < need) n *= 2;
    a.resize(n);
    b.resize(n);
    fft(a, root);
    fft(b, root);
    int inv_n = inv(n);
    for (int i = 0; i < n; ++i) a[i] = (int)(1LL * a[i] * b[i] % p * inv_n % p);
    fft(a, iroot);
    a.resize(need);
    return a;
}

std::vector<int> karatsuba(std::vector<int>& a, std::vector<int>& b) {
    int need = std::max(a.size(), b.size());
    int n = 1;
    while (n < need) n *= 2;
    std::vector<int> a_ = trim(a, n);
    std::vector<int> b_ = trim(b, n);
    std::vector<int> c(4 * n);
    std::vector<int> res(4 * n);
    mul_karatsuba(a_.data(), b_.data(), c.data(), res.data(), n);
    res.resize(a.size() + b.size() - 1);
    return res;
}






std::vector<int> mul(std::vector<int>& a, std::vector<int>& b) {
    if (std::min(a.size(), b.size()) <= 2) {
        return mul_naive(a, b);
    }
    else if (std::max(a.size(), b.size()) <= 64) {
        return karatsuba(a, b);
    }
    else {
        std::vector<int> ret = mul_fft(a, b);
        norm(ret);
        return ret;
    }
}

std::vector<int> mul(std::vector<int>& a, int b) {
    int n = a.size();
    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = (int)(1LL * a[i] * (p + b) % p);
    return c;
}


std::vector<std::vector<int>> mul(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    int m0 = 1, m1 = 1;

    for (int i = 0; i < (int)a.size(); i++) {
        m0 = std::max(m0, (int)a[i].size());
    }
    for (int i = 0; i < (int)b.size(); i++) {
        m1 = std::max(m1, (int)b[i].size());
    }

    int W = m0 + m1 - 1;

    std::vector<int> f(W * a.size(), 0);
    std::vector<int> g(W * b.size(), 0);

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)a[i].size(); j++) {
            f[i * W + j] = a[i][j];
        }
    }
    for (int i = 0; i < (int)b.size(); i++) {
        for (int j = 0; j < (int)b[i].size(); j++) {
            g[i * W + j] = b[i][j];
        }
    }

    std::vector<int> h = mul(f, g);

    std::vector<std::vector<int>> c(a.size() + b.size() - 1, std::vector<int>(W, 0));

    for (int i = 0; i < (int)h.size(); i++) {
        if (h[i] != 0) {
            c[i / W][i % W] = h[i];
        }
    }
    return c;
}




std::vector<std::vector<int>>mulNaive(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b)
{
    int m0 = 1, m1 = 1;

    for (int i = 0; i < (int)a.size(); i++) {
        m0 = std::max(m0, (int)a[i].size());
    }
    for (int i = 0; i < (int)b.size(); i++) {
        m1 = std::max(m1, (int)b[i].size());
    }

    std::vector<std::vector<int>> c(
        a.size() + b.size() - 1,
        std::vector<int>(m0 + m1 - 1, 0)
    );

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)a[i].size(); j++) {
            for (int k = 0; k < (int)b.size(); k++) {
                for (int l = 0; l < (int)b[k].size(); l++) {
                    c[i + k][j + l] = (int)((c[i + k][j + l] + 1L * a[i][j] * b[k][l]) % p);
                }
            }
        }
    }
    return c;
}


std::vector<std::vector<std::vector<int>>> mul(std::vector<std::vector<std::vector<int>>>& a, std::vector<std::vector<std::vector<int>>>& b) {
    std::vector<std::vector<std::vector<int>>> ret(a.size(), std::vector<std::vector<int>>(b[0].size(), std::vector<int>()));

    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b[i].size(); ++j) {
            for (int k = 0; k < (int)a[i].size(); ++k) {
                std::vector<int> prd = mul(a[i][k], b[k][j]);
                if (ret[i][j].size() < prd.size()) ret[i][j].resize(prd.size());
                for (int l = 0; l < (int)prd.size(); ++l) {
                    ret[i][j][l] = ADD(ret[i][j][l], prd[l]);
                }
            }
        }
    }
    return ret;
}

// f  <- -f(fg-1)+f
std::vector<int> inv(std::vector<int> g) {
    int n = g.size();
    std::vector<int> f = { inv(g[0]) };
    long long root = 3;
    long long iroot = inv(3);
    for (int len = 1; len < n; len *= 2) {
        std::vector<int> f_fft = trim(f, 2 * len);
        std::vector<int> g_fft = trim(g, 2 * len);
        fft(f_fft, root);
        fft(g_fft, root);
        long long isize = inv(2 * len);
        for (int i = 0; i < 2 * len; ++i) g_fft[i] = (int)(1LL * g_fft[i] * f_fft[i] % p * isize % p);
        fft(g_fft, iroot);
        for (int i = 0; i < len; ++i) g_fft[i] = 0;
        fft(g_fft, root);
        for (int i = 0; i < 2 * len; ++i) g_fft[i] = (int)(1LL * g_fft[i] * f_fft[i] % p * isize % p);
        fft(g_fft, iroot);
        for (int i = 0; i < len; ++i) g_fft[i] = 0;
        f.resize(std::min(n, 2 * len));
        for (int i = 0; i < 2 * len; ++i) {
            f[i] = ADD(f[i], p - g_fft[i]);
        }
    }
    return f;
}

std::vector<int> divide_naive(std::vector<int> a, std::vector<int>& b) {
    int n = a.size() - b.size() + 1;
    std::vector<int> ret(n, 0);
    norm(b);
    assert(deg(b) >= 0);
    int ib = inv(b.back());
    for (int i = n - 1; i >= 0; --i) {
        if (a[i + b.size() - 1] == 0) continue;
        ret[i] = 1LL * ib * a[i + b.size() - 1] % p;
        for (int j = 0; j < (int)b.size(); ++j) {
            a[i + j] = (a[i + j] + 1LL * b[j] * (p - ret[i])) % p;
        }
    }
    return ret;
}

std::vector<int> divide_newton(std::vector<int> a, std::vector<int> b) {
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int n = a.size() - b.size() + 1;
    b = inv(b);
    a = mul(a, b);
    a.resize(n);
    std::reverse(a.begin(), a.end());
    return a;
}

std::vector<int> divide(std::vector<int>& a, std::vector<int>& b) {
    norm(a);
    norm(b);
    if (a.size() < b.size()) {
        std::vector<int> ret(1, 0);
        return ret;
    }
    if (a.size() == b.size()) {
        return { (int)(1LL * inv(b.back()) * a.back() % p) };
    }
    else if (a.size() - b.size() < b.size() && a.size() >= 32) {
        int del = a.size() - 2 * (a.size() - b.size());
        std::vector<int> na = shift(a, -del);
        std::vector<int> nb = shift(b, -del);
        return divide(na, nb);
    }
    else if (a.size() < 32) {
        return divide_naive(a, b);
    }
    else {
        return divide_newton(a, b);
    }
}

std::vector<int> mod(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> q = divide(a, b);
    return subtract(a, mul(b, q));
}


std::vector<std::vector<int>>
copyOf(const std::vector<std::vector<int>>& a, int nx, int ny) {
    std::vector<std::vector<int>> r(nx, std::vector<int>(ny, 0));
    for (int i = 0; i < nx && i < (int)a.size(); i++) {
        for (int j = 0; j < ny && j < (int)a[i].size(); j++) {
            r[i][j] = a[i][j];
        }
    }
    return r;
}



std::vector<std::vector<int>>
inv(const std::vector<std::vector<int>>& f) {
    if (f.empty() || f[0].empty() || f[0][0] == 0) {
        throw std::runtime_error("f[0][0] == 0");
    }

    int maxlenX = (int)f.size();
    int maxlenY = 0;
    for (int i = 0; i < (int)f.size(); i++) {
        maxlenY = std::max(maxlenY, (int)f[i].size());
    }

    // g = 1 / f[0][0]
    std::vector<std::vector<int>> g(1, std::vector<int>(1));
    g[0][0] = inv(f[0][0]);

    for (int len = 1; len < maxlenX + maxlenY - 1; len <<= 1) {
        int nlenX = std::min(maxlenX, 2 * len);
        int nlenY = std::min(maxlenY, 2 * len);

        auto truncatedF = copyOf(f, nlenX, nlenY);

        auto gg  = mul(g, g);
        gg = copyOf(gg, nlenX, nlenY);

        auto ggf = mul(gg, truncatedF);

        g = copyOf(g, nlenX, nlenY);

        // g ← 2g − g²f  
        for (int i = 0; i < nlenX; i++) {
            for (int j = 0; j < nlenY; j++) {
                if (i + j < len) {
                    // keep g[i][j]
                } else if (i + j >= 2 * len) {
                    g[i][j] = 0;
                } else {
                    if (i < (int)ggf.size() && j < (int)ggf[i].size() && ggf[i][j] != 0)
                        g[i][j] = (p - ggf[i][j]) % p;
                    else
                        g[i][j] = 0;
                }
            }
        }
    }
    return g;
}


std::vector<std::vector<int>> randomPoly2D(int H, int W, int vmax = 5)
{
    std::vector<std::vector<int>> a(H);
    for (int i = 0; i < H; i++) {
        int w = rand() % (W + 1);
        a[i].resize(w);
        for (int j = 0; j < w; j++) {
            a[i][j] = rand() % vmax;
        }
    }
    return a;
}

void dumpMat(const std::vector<std::vector<int>>& v, const char* name) {
    std::cerr << name << " = {\n";
    for (int i = 0; i < (int)v.size(); i++) {
        std::cerr << "  [" << i << "] = { ";
        for (int j = 0; j < (int)v[i].size(); j++) {
            std::cerr << v[i][j];
            if (j + 1 < (int)v[i].size()) std::cerr << ", ";
        }
        std::cerr << " }\n";
    }
    std::cerr << "}\n";
}

void checkMul(const std::vector<std::vector<int>>& a,
    const std::vector<std::vector<int>>& b)
{
    auto c1 = mul(a, b);
    auto c2 = mulNaive(a, b);

    if (c1.size() != c2.size()) {
        std::cerr << "row size mismatch: "
            << c1.size() << " vs " << c2.size() << "\n";
        dumpMat(a, "a");
        dumpMat(b, "b");
        dumpMat(c1, "c1");
        dumpMat(c2, "c2");
        std::cerr.flush();
        abort();
    }

    for (int i = 0; i < (int)c1.size(); i++) {
        if (c1[i].size() != c2[i].size()) {
            std::cerr << "col size mismatch at row " << i << ": "
                << c1[i].size() << " vs " << c2[i].size() << "\n";
            dumpMat(a, "a");
            dumpMat(b, "b");
            dumpMat(c1, "c1");
            dumpMat(c2, "c2");
            std::cerr.flush();
            abort();
        }
        for (int j = 0; j < (int)c1[i].size(); j++) {
            long long x = (c1[i][j] % p + p) % p;
            long long y = (c2[i][j] % p + p) % p;
            if (x != y) {
                std::cerr << "mismatch at (" << i << "," << j << "): "
                    << x << " vs " << y << "\n";
                abort();
            }
        }
    }
}


void checkInvOnce(int H, int W) {
    static std::mt19937 rng(123456);
    auto f = randomPoly2D(H, W);
    f = copyOf(f, H, W);
    if(f[0].size()==0)return;
    if (f[0][0]==0)f[0][0]++;
    dumpMat(f, "f");
    auto g = inv(f);
    auto h = mul(g, f);
    dumpMat(g, "inv(f)");
    dumpMat(h, "f * inv(f)");
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            long long v = h[i][j] % p;
            if (v < 0) v += p;

            if (i == 0 && j == 0) {
                if (v != 1) {
                    std::cerr << "ERROR: constant term != 1\n";
                    abort();
                }
            } else {
                if (v != 0) {
                    std::cerr << "ERROR: non-zero term at (" << i << "," << j << ")\n";
                    abort();
                }
            }
        }
    }
}



void stressTestMul2D()
{
    for (int t = 0; t < 1000; t++) {
        int H1 = rand() % 5 + 1;
        int W1 = rand() % 5 + 1;
        int H2 = rand() % 5 + 1;
        int W2 = rand() % 5 + 1;

        auto a = randomPoly2D(H1, W1);
        auto b = randomPoly2D(H2, W2);

        checkMul(a, b);
    }
    std::cerr << "OK\n";
}


void stressTestInv2D()
{
    for (int t = 0; t < 1000; t++) {
        int H = rand() % 10 + 1;
        int W = rand() % 10 + 1;
        checkInvOnce(H, W);
    }
    std::cerr << "OK\n";
}





int main() {

    int N, M;
    scanf("%d %d", &N, &M);

    std::vector<std::vector<int>> f(N, std::vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &f[i][j]);
        }
    }

    auto g = inv(f);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v = 0;
            if (i < (int)g.size() && j < (int)g[i].size()) {
                v = g[i][j] % p;
                if (v < 0) v += p;
            }
            printf("%d", v);
            if (j + 1 < M) printf(" ");
        }
        printf("\n");
    }
    return 0;

}
