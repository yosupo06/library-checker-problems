#include <iostream>
#include <vector>
#include <chrono>
#include <bitset>
#include <tuple>
#include <algorithm>
#include <utility>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
using namespace std;
#define ll long long int
#define endl "\n"

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#endif

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct customHash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(__uint128_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        uint64_t low = (uint64_t)x;
        uint64_t high = (uint64_t)(x >> 64);
        return splitmix64(low + FIXED_RANDOM) ^ splitmix64(high + FIXED_RANDOM);
    }
};

// Fast I/O for 128-bit integers
using int128 = signed __int128;
using uint128 = unsigned __int128;

inline uint128 fastRead() {
    uint128 x = 0;
    int c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x * 10) + (c - '0');
        c = getchar();
    }
    return x;
}

inline void fastWrite(uint128 x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    char buf[40];
    int p = 0;
    while (x) {
        buf[p++] = (char)('0' + (x % 10));
        x /= 10;
    }
    while (p--) putchar(buf[p]);
}

// Use type u128
namespace Montgomery128
{
    using u128 = __uint128_t;
    // ---------- 64-bit limb helpers (fast) ----------
    static inline void mult64(uint64_t a, uint64_t b, uint64_t &lo, uint64_t &hi)
    {
        unsigned long long tHi;
        lo = _mulx_u64(static_cast<unsigned long long>(a), static_cast<unsigned long long>(b), &tHi);
        hi = tHi;
    }
    static inline uint64_t add64(uint64_t a, uint64_t b, uint64_t &carry)
    {
        unsigned long long tS;
        carry = _addcarry_u64(static_cast<unsigned char>(carry), static_cast<unsigned long long>(a),
                              static_cast<unsigned long long>(b), &tS);
        return tS;
    }
    // Fallback generic (slow): kept for setup (e.g., computing R^2 mod N once)
    u128 mult128(u128 a, u128 b, u128 mod)
    {
        u128 result = 0;
        for (a %= mod; b > 0; a <<= 1, b >>= 1)
        {
            a >= mod ? a -= mod : 0;
            if (b & 1)
                result += a, result >= mod ? result -= mod : 0;
        }
        return result;
    }
    // ---------- Montgomery (CIOS, 2x64-bit limbs) ----------
    // Compute n0' = -N^{-1} mod 2^64 (low limb only)
    static inline uint64_t inv64_2k(uint64_t n0)
    {
        uint64_t x = 1; // initial approx
        for (int i = 6; i > 0; --i)
            x = (__uint128_t)x * (2 - (__uint128_t)n0 * x);
        return x; // x ≡ n0^{-1}
    }

    inline pair<u128, u128> montModInv(u128 N) { return {0, (u128)(0 - inv64_2k(N))}; }

    // Fast Montgomery multiplication: returns a*b*R^{-1} mod N, where R=2^128
    inline u128 montMult(u128 a, u128 b, u128 N, u128 N_n0prime)
    {
        uint64_t n0 = (uint64_t)N, n1 = (uint64_t)(N >> 64);
        uint64_t a0 = (uint64_t)a, a1 = (uint64_t)(a >> 64);
        uint64_t b0 = (uint64_t)b, b1 = (uint64_t)(b >> 64);
        uint64_t n0p = (uint64_t)N_n0prime;
        uint64_t t0 = 0, t1 = 0, t2 = 0, t3 = 0;

        auto roundStep = [&](uint64_t ai) __attribute__((always_inline))
        {
            uint64_t lo, hi, carry = 0;
            // t += ai * b
            mult64(ai, b0, lo, hi);
            t0 = add64(t0, lo, carry);
            t1 = add64(t1, hi, carry);
            t2 = add64(t2, 0, carry);
            mult64(ai, b1, lo, hi);
            carry = 0;
            t1 = add64(t1, lo, carry);
            t2 = add64(t2, hi, carry);
            t3 = add64(t3, 0, carry);
            // m = t0 * n0' (mod 2^64)
            uint64_t m = (uint64_t)((__uint128_t)t0 * n0p);
            // t += m * N
            mult64(m, n0, lo, hi);
            carry = (t0 != 0); // Mathematically exact replacement for t0 = add64(t0, lo, carry);
            t1 = add64(t1, hi, carry);
            t2 = add64(t2, 0, carry);
            t3 = add64(t3, 0, carry);

            mult64(m, n1, lo, hi);
            carry = 0;
            t1 = add64(t1, lo, carry);
            t2 = add64(t2, hi, carry);
            t3 = add64(t3, 0, carry);

            // shift by one limb
            t0 = t1;
            t1 = t2;
            t2 = t3;
            t3 = 0;
        };

        roundStep(a0);
        roundStep(a1);

        __uint128_t res = (((__uint128_t)t1 << 64) | t0);
        if (t2 || res >= N)
            res -= N;
        return (u128)res;
    }
}
using namespace Montgomery128;

inline u128 addMod(u128 a, u128 b, u128 n)
{
    u128 res = a + b;
    u128 mask = -(u128)(res >= n || res < a);
    return res - (n & mask);
}

inline u128 subMod(u128 a, u128 b, u128 n)
{
    u128 res = a - b;
    u128 mask = -(u128)(a < b);
    return res + (n & mask);
}

constexpr inline uint32_t bitWidth128(u128 x)
{
    if (x == 0)
        return 0;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t lo = (uint64_t)x;
    return hi ? 128 - __builtin_clzll(hi) : 64 - __builtin_clzll(lo);
}

constexpr inline int ctz128(u128 x)
{
    if (x == 0)
        return 128;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t lo = (uint64_t)x;
    return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll(hi);
}

template <typename T>
T GCD(T a, T b)
{
    if (!a || !b)
        return a | b;
    int shift = ctz128(a | b);
    a >>= ctz128(a);
    do
    {
        b >>= ctz128(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

// Pollard-Rho function
template <typename T>
inline T F(T x, T c, T mod, T inv) { return addMod(montMult(x, x, mod, inv), c, mod); }

template <typename T>
inline T __abs(T N) { return N < 0 ? -N : N; }

template <typename T>
T pollardBrent(T N, int maxIters = 30000)
{
    if (!(N & 1))
        return 2;

    // Random Number Linear Congruential Generator MMIX from D.E. Knuth
    static u128 rng = 0xdeafbeefff;
    uint64_t a = rng * 6364136223846793005ULL + 1442695040888963407ULL;
    uint64_t b = a * 6364136223846793005ULL + 1442695040888963407ULL;
    rng = (a + b) ^ (a * b);

    T X0 = 1 + a % (N - 1);
    T C = 1 + b % (N - 1);
    T X = X0; // X1
    T gcdVal = 1;
    T q = 1;
    T Xs, Xt;
    T m = 128;
    u128 inv = montModInv(N).second;
    T L = 1;
    int iters = 0;
    while (gcdVal == 1)
    {
        Xt = X;
        for (size_t i = 1; i < L; ++i)
            X = F(X, C, N, inv);

        uint64_t k = 0;
        while (k < L && gcdVal == 1)
        {
            Xs = X;
            for (size_t i = 0; i < m && i + k < L; ++i)
            {
                X = F(X, C, N, inv);
                q = montMult(q, Xt > X ? Xt - X : X - Xt, N, inv);
            }
            gcdVal = GCD(q, N);
            k += m;
        }
        L += L;
        iters += L;
        if (iters > maxIters)
            return N;
    }
    if (gcdVal == N) // Failure
    {
        do
        {
            Xs = F(Xs, C, N, inv);
            gcdVal = GCD(Xs > Xt ? Xs - Xt : Xt - Xs, N);
        } while (gcdVal == 1);
    }
    return gcdVal;
}

static vector<uint32_t> primes;
void linearSieve(int N)
{
    bitset<250001> isPrime;
    isPrime.set();               // Initially Assuming all numbers to be primes
    isPrime[0] = isPrime[1] = 0; // 0 and 1 are NOT primes
    for (long long i{2}; i <= N; i++)
    {
        if (isPrime[i])
            primes.push_back(i);
        for (long long j = 0; j < (int)primes.size() && i * primes[j] <= N; j++)
        {
            isPrime[i * primes[j]] = 0;
            if (i % primes[j] == 0)
                break;
        }
    }
}
static int autoCall = (linearSieve(250000), 0);

struct Point
{
    u128 x, z;
};

Point doublePoint(Point p, u128 a24, u128 n, uint64_t n0p)
{
    u128 u = addMod(p.x, p.z, n);
    u128 v = subMod(p.x, p.z, n);
    u = Montgomery128::montMult(u, u, n, n0p);
    v = Montgomery128::montMult(v, v, n, n0p);
    u128 diff = subMod(u, v, n);
    Point res;
    res.x = Montgomery128::montMult(u, v, n, n0p);
    u128 t = Montgomery128::montMult(a24, diff, n, n0p);
    res.z = Montgomery128::montMult(diff, addMod(v, t, n), n, n0p);
    return res;
}

Point addPoint(Point p, u128 qPlus, u128 qMinus, Point diff, u128 n, uint64_t n0p)
{
    u128 u = Montgomery128::montMult(subMod(p.x, p.z, n), qPlus, n, n0p);
    u128 v = Montgomery128::montMult(addMod(p.x, p.z, n), qMinus, n, n0p);
    u128 sum = addMod(u, v, n);
    u128 dif = subMod(u, v, n);
    sum = Montgomery128::montMult(sum, sum, n, n0p);
    dif = Montgomery128::montMult(dif, dif, n, n0p);
    Point res;
    res.x = Montgomery128::montMult(sum, diff.z, n, n0p);
    res.z = Montgomery128::montMult(dif, diff.x, n, n0p);
    return res;
}

Point multiplyPoint(Point p, u128 k, u128 a24, u128 n, uint64_t n0p)
{
    if (k == 0)
        return {0, 1};
    if (k == 1)
        return p;

    u128 x0 = p.x, z0 = p.z;
    Point p2 = doublePoint(p, a24, n, n0p);
    u128 x1 = p2.x, z1 = p2.z;

    int bits = bitWidth128(k);
    uint32_t prevBit = 0;

    for (int i = bits - 2; i >= 0; --i)
    {
        uint32_t bit = (k >> i) & 1;
        uint32_t swap = bit ^ prevBit;
        prevBit = bit;

        u128 mask = -(u128)swap;
        u128 t;
        t = (x0 ^ x1) & mask;
        x0 ^= t;
        x1 ^= t;
        t = (z0 ^ z1) & mask;
        z0 ^= t;
        z1 ^= t;

        u128 u1 = addMod(x0, z0, n);
        u128 v1 = subMod(x0, z0, n);
        u128 u2 = addMod(x1, z1, n);
        u128 v2 = subMod(x1, z1, n);

        u128 t1 = Montgomery128::montMult(u1, v2, n, n0p);
        u128 t2 = Montgomery128::montMult(v1, u2, n, n0p);

        u128 t3 = addMod(t1, t2, n);
        u128 t4 = subMod(t1, t2, n);

        t3 = Montgomery128::montMult(t3, t3, n, n0p);
        t4 = Montgomery128::montMult(t4, t4, n, n0p);

        x1 = Montgomery128::montMult(t3, p.z, n, n0p);
        z1 = Montgomery128::montMult(t4, p.x, n, n0p);

        u128 u1sq = Montgomery128::montMult(u1, u1, n, n0p);
        u128 v1sq = Montgomery128::montMult(v1, v1, n, n0p);
        u128 diff = subMod(u1sq, v1sq, n);

        x0 = Montgomery128::montMult(u1sq, v1sq, n, n0p);
        u128 t5 = Montgomery128::montMult(a24, diff, n, n0p);
        t5 = addMod(v1sq, t5, n);
        z0 = Montgomery128::montMult(diff, t5, n, n0p);
    }

    u128 mask = -(u128)prevBit;
    u128 t;
    t = (x0 ^ x1) & mask;
    x0 ^= t;
    x1 ^= t;
    t = (z0 ^ z1) & mask;
    z0 ^= t;
    z1 ^= t;

    return {x0, z0};
}

u128 modInv(u128 a, u128 m)
{
    if (a == 0 || m <= 1)
        return 0;
    u128 u = a, v = m;
    u128 x1 = 1, x2 = 0;
    while (u != 0 && v != 0)
    {
        while ((u & 1) == 0)
        {
            u >>= 1;
            if (x1 & 1)
            {
                u128 c = (m > ~(u128)0 - x1) ? 1 : 0;
                x1 = (x1 + m) >> 1;
                if (c)
                    x1 |= ((u128)1 << 127);
            }
            else
                x1 >>= 1;
        }
        while ((v & 1) == 0)
        {
            v >>= 1;
            if (x2 & 1)
            {
                u128 c = (m > ~(u128)0 - x2) ? 1 : 0;
                x2 = (x2 + m) >> 1;
                if (c)
                    x2 |= ((u128)1 << 127);
            }
            else
                x2 >>= 1;
        }
        if (u >= v)
        {
            u -= v;
            x1 = (x1 < x2) ? x1 + m - x2 : x1 - x2;
        }
        else
        {
            v -= u;
            x2 = (x2 < x1) ? x2 + m - x1 : x2 - x1;
        }
    }
    if (u == 1)
        return x1;
    if (v == 1)
        return x2;
    return 0;
}

u128 ECM(u128 n)
{
    uint32_t m2 = -((n & 1) == 0);
    uint32_t m3 = -(n % 3 == 0) & ~m2;
    uint32_t m5 = -(n % 5 == 0) & ~m2 & ~m3;
    uint32_t spf = (m2 & 2) | (m3 & 3) | (m5 & 5);
    if (spf)
        return spf;

    uint64_t n0p = -Montgomery128::inv64_2k((uint64_t)n);
    u128 r = (~(u128)0 % n + 1) % n;
    u128 r2 = mult128(r, r, n);

    uint32_t B1 = 11000;
    uint32_t B2 = 1900000;
    uint32_t D = 975;

    uint64_t rngState = 0xdeafbeefff;
    auto rand64 = [&]() -> uint64_t
    {
        rngState += 0x9e3779b97f4a7c15ULL;
        uint64_t z = rngState;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    };

    alignas(64) Point baby[1 << 13];
    alignas(64) u128 bPfx[1 << 13];
    alignas(64) Point curBuf[16];
    alignas(64) u128 zPfx[16];
    static vector<uint32_t> powTab;
    static uint32_t copIdx[1 << 13];
    static uint32_t nCop = 0;
    static uint32_t lastB1 = 0, lastD = 0;

    int curveCount = 0;
    while (true)
    {
        curveCount++;
        if (curveCount > 30)
            tie(B1, B2, D) = tuple{50000, 13000000, 2550};
        if (curveCount > 100)
            tie(B1, B2, D) = tuple{250000, 84000000, 6480};
        if (B1 != lastB1 || D != lastD)
        {
            powTab.clear();
            for (const uint32_t &q : primes)
            {
                if (q > B1)
                    break;
                uint64_t pk = q;
                while (pk * q <= B1)
                    pk *= q;
                powTab.push_back((uint32_t)pk);
            }

            nCop = 0;
            for (uint32_t k = 0; k < D; ++k)
                if (GCD(k + 1, 2 * D) == 1)
                    copIdx[nCop++] = k;

            lastB1 = B1;
            lastD = D;
        }
        // Suyama parametrization — guarantees group order divisible by 12 (Z/12Z)
        u128 sigma = (rand64() % (n - 6)) + 6;
        u128 u = subMod(mult128(sigma, sigma, n), 5, n);
        u128 v = mult128(4, sigma, n);
        if (!u || !v || u == v)
            continue;
        u128 u3 = mult128(mult128(u, u, n), u, n);
        u128 v3 = mult128(mult128(v, v, n), v, n);

        u128 vMinusU = subMod(v, u, n);
        u128 num1 = mult128(mult128(vMinusU, vMinusU, n), vMinusU, n);
        u128 num2 = addMod(mult128(3, u, n), v, n);
        u128 a24Num = mult128(num1, num2, n);
        u128 a24Den = mult128(16, mult128(u3, v, n), n);

        u128 g = GCD(a24Den, n);
        if (g > 1 && g < n)
            return g;
        if (g == n)
            continue;

        u128 a24 = mult128(a24Num, modInv(a24Den, n), n);
        u128 bigA24 = Montgomery128::montMult(a24, r2, n, n0p);
        Point p = {Montgomery128::montMult(u3, r2, n, n0p),
                   Montgomery128::montMult(v3, r2, n, n0p)};

        // Stage 1: multiply P by all prime powers <= B1
        int step = 0;
        for (const uint32_t &pk : powTab)
        {
            p = multiplyPoint(p, pk, bigA24, n, n0p);
            if ((++step & 31) == 0)
            {
                g = GCD(p.z, n);
                if (g > 1 && g < n)
                    return g;
                if (g == n)
                    break;
            }
        }

        g = GCD(p.z, n);
        if (g > 1 && g < n)
            return g;
        if (g == n)
            continue;
        // Stage 2: ± BSGS
        baby[0] = p;
        baby[1] = doublePoint(p, bigA24, n, n0p);
        u128 pPlus = addMod(p.x, p.z, n);
        u128 pMinus = subMod(p.x, p.z, n);
        for (uint32_t i = 2; i < D; i++)
            baby[i] = addPoint(baby[i - 1], pPlus, pMinus, baby[i - 2], n, n0p);

        Point gPt = doublePoint(baby[D - 1], bigA24, n, n0p);
        bPfx[0] = baby[copIdx[0]].z;
        for (uint32_t i = 1; i < nCop; ++i)
            bPfx[i] = Montgomery128::montMult(bPfx[i - 1], baby[copIdx[i]].z, n, n0p);

        u128 bProd = Montgomery128::montMult(bPfx[nCop - 1], 1, n, n0p);
        g = GCD(bProd, n);
        if (g > 1 && g < n)
            return g;
        if (g == n)
            continue;

        u128 bInv = Montgomery128::montMult(modInv(bProd, n), r2, n, n0p);
        for (int i = (int)nCop - 1; i >= 1; --i)
        {
            u128 invZi = Montgomery128::montMult(bInv, bPfx[i - 1], n, n0p);
            bInv = Montgomery128::montMult(bInv, baby[copIdx[i]].z, n, n0p);
            baby[copIdx[i]].x = Montgomery128::montMult(baby[copIdx[i]].x, invZi, n, n0p);
            baby[copIdx[i]].z = r;
        }
        baby[copIdx[0]].x = Montgomery128::montMult(baby[copIdx[0]].x, bInv, n, n0p);
        baby[copIdx[0]].z = r;

        Point cur = gPt;
        Point nextCur = doublePoint(gPt, bigA24, n, n0p);
        u128 gPlus = addMod(gPt.x, gPt.z, n);
        u128 gMinus = subMod(gPt.x, gPt.z, n);
        u128 acc = r;
        uint32_t jMax = (uint32_t)((uint64_t)B2 / (2 * D));
        for (uint32_t jBase = 1; jBase <= jMax;)
        {
            uint32_t chunkSz = min(16u, jMax - jBase + 1);
            curBuf[0] = cur;
            if (chunkSz >= 2)
                curBuf[1] = nextCur;
            for (uint32_t c = 2; c < chunkSz; ++c)
                curBuf[c] = addPoint(curBuf[c - 1], gPlus, gMinus, curBuf[c - 2], n, n0p);

            if (jBase + chunkSz <= jMax)
            {
                if (chunkSz == 1)
                {
                    cur = nextCur;
                    nextCur = addPoint(nextCur, gPlus, gMinus, curBuf[0], n, n0p);
                }
                else
                {
                    cur = addPoint(curBuf[chunkSz - 1], gPlus, gMinus, curBuf[chunkSz - 2], n, n0p);
                    nextCur = addPoint(cur, gPlus, gMinus, curBuf[chunkSz - 1], n, n0p);
                }
            }

            zPfx[0] = curBuf[0].z;
            for (uint32_t c = 1; c < chunkSz; ++c)
                zPfx[c] = Montgomery128::montMult(zPfx[c - 1], curBuf[c].z, n, n0p);

            u128 zProd = Montgomery128::montMult(zPfx[chunkSz - 1], 1, n, n0p);
            g = GCD(zProd, n);
            if (g > 1 && g < n)
                return g;
            if (g == n)
            {
                acc = r;
                jBase += chunkSz;
                continue;
            }

            u128 zInv = Montgomery128::montMult(modInv(zProd, n), r2, n, n0p);
            for (int c = (int)chunkSz - 1; c >= 1; --c)
            {
                u128 invZc = Montgomery128::montMult(zInv, zPfx[c - 1], n, n0p);
                zInv = Montgomery128::montMult(zInv, curBuf[c].z, n, n0p);
                curBuf[c].x = Montgomery128::montMult(curBuf[c].x, invZc, n, n0p);
                curBuf[c].z = r;
            }
            curBuf[0].x = Montgomery128::montMult(curBuf[0].x, zInv, n, n0p);
            curBuf[0].z = r;

            for (uint32_t c = 0; c < chunkSz; ++c)
            {
                for (uint32_t i = 0; i < nCop; ++i)
                {
                    u128 diff = subMod(baby[copIdx[i]].x, curBuf[c].x, n);
                    acc = Montgomery128::montMult(acc, diff, n, n0p);
                }
            }

            g = GCD(acc, n);
            if (g > 1 && g < n)
                return g;
            if (g == n)
                acc = r;

            jBase += chunkSz;
        }
        g = GCD(acc, n);
        if (g > 1 && g < n)
            return g;
    }
    return n;
}

template <typename T>
T modPow(T N, T power, T mod)
{
    if (N % mod == 0 || N == 0)
        return 0;
    if (N == 1 || power == 0)
        return 1;
    T res{1};
    while (power)
    {
        if (power & 1)
            res = mult128(res, N, mod);
        N = mult128(N, N, mod);
        power >>= 1;
    }
    return res;
}

template <typename T>
bool millerRabin(T N)
{
    T d = N - 1;
    int s{};
    while (!(d & 1))
        d >>= 1, ++s;

    constexpr int a = 2;
    T p = modPow(a % N, d, N), i = s;
    while (p != 1 && p != N - 1 && a % N && i--)
        p = mult128(p, p, N);
    if (p != N - 1 && i != (T)s)
        return false;
    return true;
}

template <typename T>
int jacobi(T D, T n)
{
    int t = 1;
    D %= n;
    while (D != 0)
    {
        int r = 0;
        while (!(D & 1))
            D >>= 1, r++;
        if (r & 1)
        {
            T nm = n & 7;
            if (nm == 3 || nm == 5)
                t = -t;
        }
        swap(D, n);

        if ((D & 3) == 3 && (n & 3) == 3)
            t = -t;
        D %= n;
    }
    return (n == 1) ? t : 0;
}

constexpr u128 iSqrt(u128 n) // O(log(log(n)))
{
    if (n < 2)
        return n;
    u128 xk = (u128)1 << ((bitWidth128(n) + 1) >> 1);
    u128 nxt = (xk + n / xk) >> 1;
    while (nxt < xk)
    {
        xk = nxt;
        nxt = (xk + n / xk) >> 1;
    }
    return xk;
}

template <typename T>
bool isPerfectSquare(T n)
{
    if (n == 0 || n == 1)
        return true;

    static constexpr unsigned long long MASK =
        0x0202021202030213ULL;

    if (((MASK >> (n & 63)) & 1) == 0)
        return false;

    T r = iSqrt(n);
    return r * r == n;
}

void calcLucas(u128 k, u128 n, ll d, ll p, ll q, u128 &U, u128 &V, u128 &Qk)
{
    if (k == 0)
    {
        U = 0;
        V = 2;
        Qk = 1;
        return;
    }

    auto add = [&](u128 a, u128 b)
    { return (a + b >= n) ? a + b - n : a + b; };
    auto sub = [&](u128 a, u128 b)
    { return (a >= b) ? a - b : a + n - b; };
    auto div2 = [&](u128 a)
    { return (a & 1) ? (a + n) >> 1 : a >> 1; };

    u128 P = (p < 0) ? n - (u128)(-p) % n : (u128)p % n;
    u128 Q = (q < 0) ? n - (u128)(-q) % n : (u128)q % n;
    u128 D = (d < 0) ? n - (u128)(-d) % n : (u128)d % n;

    int bits = bitWidth128(k);
    U = 1;
    V = P;
    Qk = Q;

    for (int i = bits - 2; i >= 0; i--)
    {
        U = mult128(U, V, n);
        V = sub(mult128(V, V, n), add(Qk, Qk));
        Qk = mult128(Qk, Qk, n);

        if ((k >> i) & 1)
        {
            u128 nU = div2(add(mult128(P, U, n), V));
            u128 nV = div2(add(mult128(D, U, n), mult128(P, V, n)));
            U = nU;
            V = nV;
            Qk = mult128(Qk, Q, n);
        }
    }
}

bool strongLucasSelfridge(u128 n)
{
    ll D = 5, sign = 1;
    while (true)
    {
        ll curD = D * sign;
        u128 jacD = (curD < 0) ? (n - (u128)(-curD) % n) % n : ((u128)curD % n);
        int j = jacobi(jacD, n);
        if (j == -1)
        {
            D = curD;
            break;
        }

        if (j == 0)
            return n == (u128)(curD < 0 ? -curD : curD);
        D += 2;
        sign = -sign;
    }

    ll P = 1;
    ll Q = (1 - D) / 4;

    if (P == 1 && Q == -1)
        P = 5, Q = 5;

    u128 d = n + 1;
    int s = 0;
    while (!(d & 1))
        d >>= 1, s++;

    u128 U, V, Qk;
    calcLucas(d, n, D, P, Q, U, V, Qk);

    bool isSlprp = (U == 0 || V == 0);

    auto add = [&](u128 a, u128 b)
    { return (a + b >= n) ? a + b - n : a + b; };
    auto sub = [&](u128 a, u128 b)
    { return (a >= b) ? a - b : a + n - b; };

    for (int r = 1; r < s; r++)
    {
        V = sub(mult128(V, V, n), add(Qk, Qk));
        Qk = mult128(Qk, Qk, n);
        if (V == 0)
            isSlprp = true;
    }
    if (!isSlprp)
        return false;
    u128 vNext = sub(mult128(V, V, n), add(Qk, Qk));
    u128 expectedV = (Q < 0) ? (n - ((u128)(-(int128)Q) * 2) % n) % n : ((u128)Q * 2) % n;
    if (vNext != expectedV)
        return false;

    u128 qMod = (Q < 0) ? (n - (u128)(-Q) % n) % n : (u128)Q % n;
    int jacQ = jacobi(qMod, n);
    u128 expectedQ = (jacQ == -1) ? n - qMod : qMod;
    if (Qk != expectedQ)
        return false;

    return true;
}

template <typename T>
bool isBPSWPrime(T n)
{
    if (n < 64)
    {
        constexpr uint64_t MASK = 0x28208A20A08A28ACULL;
        return (MASK >> n) & 1;
    }

    uint32_t x = (uint32_t)(n % 30);
    constexpr uint32_t WHEEL30 = 0x208A2882;

    if (!((WHEEL30 >> x) & 1))
        return false;

    if (!millerRabin(n))
        return false;

    if (isPerfectSquare(n))
        return false;

    return strongLucasSelfridge(n);
}

gp_hash_table<u128, vector<u128>, customHash> cache;
template <typename T>
void primeFactorize(T N, vector<T> &primeFactors)
{
    if (N == 1)
        return;
    auto it = cache.find(N);
    if (it != cache.end())
        return void(primeFactors.insert(primeFactors.end(), it->second.begin(), it->second.end()));

    vector<T> result;
    if (isBPSWPrime(N))
        result.push_back(N);
    else if (isPerfectSquare(N))
    {
        T sq = iSqrt(N);
        primeFactorize(sq, result);
        primeFactorize(sq, result);
    }
    else
    {
        T Y = pollardBrent(N, 1 << 15);
        if (Y == N)
            Y = ECM(N);

        primeFactorize(Y, result);
        primeFactorize(N / Y, result);
    }
    cache[N] = result;
    primeFactors.insert(primeFactors.end(), result.begin(), result.end());
}

int main()
{
    int t = (int)fastRead();
    while (t--)
    {
        u128 N = fastRead();
        vector<u128> primeFactors;
        primeFactorize(N, primeFactors);
        sort(primeFactors.begin(), primeFactors.end());
        fastWrite(primeFactors.size());
        putchar(' ');
        for (const u128 &p : primeFactors) {
            fastWrite(p);
            putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}