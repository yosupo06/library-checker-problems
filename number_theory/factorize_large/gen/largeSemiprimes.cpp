#include <iostream>
#include <string>
#include "testlib.h"
#include "../params.h"

using namespace std;
using u128 = __uint128_t;

ostream &operator<<(ostream &stream, u128 n) {
    if (n == 0) return stream.put('0');
    char buf[40];
    char *p = buf + 40;
    do {
        *--p = (char)('0' + (unsigned)(n % 10));
        n /= 10;
    } while (n);
    return stream.write(p, (buf + 40) - p);
}

using u128 = __uint128_t;
using int128 = __int128_t;
using ll = long long;

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
    T p = modPow((T)(a % N), d, N);
    T i = s;
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

constexpr inline uint32_t bitWidth128(u128 n)
{
    if (!n)
        return 0;
    uint64_t hi = (uint64_t)(n >> 64);
    uint64_t lo = (uint64_t)n;
    return hi ? 128 - __builtin_clzll(hi) : 64 - __builtin_clzll(lo);
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


u128 parseU128(const std::string &s) {
    u128 res = 0;
    for (char c : s) {
        res = res * 10 + (c - '0');
    }
    return res;
}

static u128 s = 0;
static inline u128 rand128()
{
    /*
     * LCG formula: X = (a * X + c) mod 2^128
     * 'a' is a 128-bit multiplier with strong spectral properties.
     * 'c' is an odd increment, ensuring a full period of 2^128.
     * Overflow of u128 natively handles the modulo 2^128.
     */
    const u128 a = ((u128)0x2360ED051FC65DA4ULL << 64) | 0x4385DF649FCCF645ULL;
    const u128 c = ((u128)0x5851F42D4C957F2DULL << 64) | 0x14057B7EF767814FULL;
    
    s = s * a + c;
    
    return s;
}

static inline u128 randRng(u128 lo, u128 hi)
{
    u128 m = -(lo > hi);
    u128 d = (lo ^ hi) & m;
    
    lo ^= d;
    hi ^= d;

    u128 r = rand128();
    u128 rng = hi - lo + 1;

    return (rng == 0 ? r : lo + (r % rng));
}

u128 genLargePrime(u128 lo, u128 hi) {
    static std::vector<u128> vc;
    while (true) {
        u128 p = randRng(lo, hi);
        p += !(p & 1);
        if (p > hi) continue;

        if (isBPSWPrime(p)) {
            bool unique = true;
            for (u128 prev : vc) {
                if (prev == p) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                vc.push_back(p);
                return p;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    s = ((u128)rnd.next() << 96) ^ ((u128)rnd.next() << 64) ^ ((u128)rnd.next() << 32) ^ (u128)rnd.next();
    
    int q = MAX_Q;
    u128 maxN = parseU128(MAX_N);
    vector<u128> semiPrimes{
        9986998694074992619ULL,
        9501540829148808241ULL,
        1553381999513383757ULL,
        3352240630789220717ULL,
        7241617205978236309ULL,
        534022786545143537ULL,
    };
    for (int i = 0; i < 20; i++) {
        semiPrimes.push_back(genLargePrime(1000000000000000000ULL, 10000000000000000000ULL));
    }
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int type = rnd.next(0, 3);
        
        if (type == 0)
        {
            // Balanced semiprime
            u128 root = iSqrt(maxN);
            u128 p1 = genLargePrime(root / 2, root);
            u128 p2 = genLargePrime(root / 2, maxN / p1);
            cout << p1 * p2 << "\n";
        }
        else if (type == 1)
        {
            // Pure prime near the upper limit.
            u128 p = genLargePrime(maxN - rnd.next(20000, 1000000), maxN);
            cout << p << "\n";
        }
        else if (type == 2)
        {
            // Asymmetric semiprime
            u128 limitP1 =  1000000000ULL;
            u128 p1 = genLargePrime(2, limitP1);
            u128 p2 = genLargePrime(maxN / (p1 * 10) + 1, maxN / p1);
            cout << p1 * p2 << "\n";
        }
        else
        {
            // Perfect square of a prime.
            u128 root = iSqrt(maxN);
            u128 p = genLargePrime(root / 2, root);
            cout << p * p << "\n";
        }
    }
    
    return 0;
}
