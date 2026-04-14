#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 998244353;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

constexpr uint QUAD_NONRESIDUE = 3;
constexpr int LOG2_ORD         = __builtin_ctz(MOD - 1);
constexpr uint ZETA            = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
constexpr uint INV_ZETA        = InvMod(ZETA);

std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
    assert((n & (n - 1)) == 0);
    if (n / 2 == 0) return {};
    std::vector<uint> root(n / 2), inv_root(n / 2);
    root[0] = inv_root[0] = 1;
    for (int i = 0; (1 << i) < n / 2; ++i)
        root[1 << i]               = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
    for (int i = 1; i < n / 2; ++i)
        root[i]     = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
        inv_root[i] = (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
    return {root, inv_root};
}

void Butterfly(uint a[], int n, const uint root[]) {
    assert((n & (n - 1)) == 0);
    for (int i = n; i >= 2; i /= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) {
                const uint u = a[k];
                a[k + i / 2] = (ull)a[k + i / 2] * root[j / i] % MOD;
                if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
                if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;
            }
}

void InvButterfly(uint a[], int n, const uint root[]) {
    assert((n & (n - 1)) == 0);
    for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) {
                const uint u = a[k];
                if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
                a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
            }
}

int GetFFTSize(int n) {
    int len = 1;
    while (len < n) len *= 2;
    return len;
}

void FFT(uint a[], int n, const uint root[]) { Butterfly(a, n, root); }

void InvFFT(uint a[], int n, const uint root[]) {
    InvButterfly(a, n, root);
    const uint invN = InvMod(n);
    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;
}

std::vector<uint> Product(std::vector<uint> a, std::vector<uint> b) {
    if (empty(a) || empty(b)) return {};
    const int n           = size(a) + size(b) - 1;
    const int N           = GetFFTSize(n);
    auto [root, inv_root] = GetFFTRoot(N);
    a.resize(N);
    b.resize(N);
    FFT(data(a), N, data(root));
    FFT(data(b), N, data(root));
    for (int i = 0; i < N; ++i) a[i] = (ull)a[i] * b[i] % MOD;
    InvFFT(data(a), N, data(inv_root));
    a.resize(n);
    return a;
}

std::vector<uint> FPSInv(const std::vector<uint> &a, int n) {
    assert(!empty(a) && a[0] != 0);
    assert(n >= 0);
    if (n == 0) return {};
    const int N                 = GetFFTSize(n);
    const auto [root, inv_root] = GetFFTRoot(N);
    std::vector<uint> invA(N), shopA(N), shopB(N);
    invA[0] = InvMod(a[0]);
    for (int i = 2; i <= N; i *= 2) {
        std::memcpy(data(shopA), data(a), sizeof(uint) * std::min((int)size(a), i));
        if ((int)size(a) < i)
            std::memset(data(shopA) + (int)size(a), 0, sizeof(uint) * (i - (int)size(a)));
        std::memcpy(data(shopB), data(invA), sizeof(uint) * i);
        FFT(data(shopA), i, data(root));
        FFT(data(shopB), i, data(root));
        for (int j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;
        InvFFT(data(shopA), i, data(inv_root));
        std::memset(data(shopA), 0, sizeof(uint) * (i / 2));
        FFT(data(shopA), i, data(root));
        for (int j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;
        InvFFT(data(shopA), i, data(inv_root));
        for (int j = i / 2; j < i; ++j) invA[j] = shopA[j] != 0 ? MOD - shopA[j] : shopA[j];
    }
    invA.resize(n);
    return invA;
}

int main() {
    int n;
    std::scanf("%d", &n);
    assert(n > 0);

    std::vector<uint> f(n);
    for (int i = 0; i < n; ++i) std::scanf("%u", &f[i]);

    std::vector<uint> factorial(n + 1), inv_factorial(n + 1);
    factorial[0] = inv_factorial[0] = 1;
    for (int i = 1; i <= n; ++i) factorial[i] = (ull)factorial[i - 1] * i % MOD;
    inv_factorial[n] = InvMod(factorial[n]);
    for (int i = n - 1; i > 0; --i) inv_factorial[i] = (ull)inv_factorial[i + 1] * (i + 1) % MOD;

    std::vector<uint> A(n);
    for (int i = 0; i < n; ++i) A[i] = (ull)f[i] * factorial[i] % MOD;

    std::vector<uint> B(n);
    for (int i = 0; i < n; ++i) B[i] = inv_factorial[i + 1];
    B = FPSInv(B, n);
    // B[j] = B_j/j! where B_j is the j-th Bernoulli number

    // S_0(n) := Σ[1 <= k <= n] k^0 = n
    // S_1(n) := Σ[1 <= k <= n] k   = 1/2 * n * (n + 1)
    // S_2(n) := Σ[1 <= k <= n] k^2 = 1/6 * n * (n + 1) * (2n + 1)
    // ...
    // Faulhaber's formula:
    // S_k(n) := 1/(k+1) * Σ[1 <= j <= k+1] (-1)^delta(j, k) * binom(k+1, j) * B_(k+1-j) * n^j
    // see: 4乗の和，べき乗の和の公式|高校数学の美しい物語
    //      https://manabitimes.jp/math/645

    // g(n)       = -f(n) + Σ[0 <= j < n] f[j] S_j(n)
    // For t >= 1,
    // [n^t] g(n) = -f[t] + Σ[0 <= j < n] f[j] [n^t] S_j(n)
    //   = -f[t] + Σ[t-1 <= j < n] f[j]/(j+1) * (-1)^delta(t, j) * binom(j+1, t) * B_(j+1-t)
    //   = -f[t] +  1/t! * Σ[t-1 <= j < n] f[j] * (-1)^delta(t, j) * j! * B_(j+1-t)/(j+1-t)!
    //   = -f[t] + (1/t! * Σ[t-1 <= j < n] f[j] * j! * B_(j+1-t)/(j+1-t)!) - 2 * f[t] * B_1
    // since B_1 = -1/2, we have
    // [n^t] g(n) = 1/t! * Σ[t-1 <= j < n] f[j] * j! * B_(j+1-t)/(j+1-t)!

    // Let A(n) := Σ[0 <= j < n] f[j] * j! * n^j,
    //     B(n) := Σ[j >= 0] B_j/j! n^(-j)
    // Drop the terms of n^(<0)
    // [n^0] AB = Σ[0 <= j < n] f[j] * B_j                 = 1! * [n^1] g(n)
    // [n^1] AB = Σ[1 <= j < n] f[j] * j! * B_(j-1)/(j-1)! = 2! * [n^2] g(n)
    // ...

    reverse(begin(B), end(B));

    std::vector<uint> g = Product(std::move(A), std::move(B));
    g.erase(begin(g), begin(g) + n - 1);
    g.insert(begin(g), 0);

    for (int i = 0; i <= n; ++i) g[i] = (ull)g[i] * inv_factorial[i] % MOD;

    for (int i = 0; i <= n; ++i) {
        if (i) std::printf(" ");
        std::printf("%u", g[i]);
    }
    std::puts("");

    return 0;
}
