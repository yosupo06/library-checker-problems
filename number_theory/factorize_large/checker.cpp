// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/wcmp.cpp

// The MIT License (MIT)

// Copyright (c) 2015 Mike Mirzayanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define ll long long int
#define endl "\n"

// Fast I/O for 128-bit integers
using int128 = signed __int128;
using uint128 = unsigned __int128;
ostream &operator<<(ostream &stream, int128 n)
{
    if (__builtin_expect(n == 0, 0))
        return stream.put('0');
    char buf[41];
    char *end = buf + 41;
    char *p = end;
    bool neg = (n < 0);
    uint128 u = neg ? -(uint128)n : (uint128)n;
    do
    {
        *--p = (char)('0' + (unsigned)(u % 10));
        u /= 10;
    } while (u);
    if (neg)
        *--p = '-';
    return stream.write(p, end - p);
}

ostream &operator<<(ostream &stream, uint128 n)
{
    if (__builtin_expect(n == 0, 0))
        return stream.put('0');
    char buf[40];
    char *end = buf + 40;
    char *p = end;
    do
    {
        *--p = (char)('0' + (unsigned)(n % 10));
        n /= 10;
    } while (n);
    return stream.write(p, end - p);
}

istream &operator>>(istream &stream, int128 &n)
{
    n = 0;
    char c;
    if (!(stream >> c))
        return stream;
    bool neg = (c == '-');
    if (neg && !stream.get(c))
        return stream;
    while (isdigit((unsigned char)c))
    {
        n = n * 10 + (c - '0');
        if (!stream.get(c))
            break;
    }
    if (neg)
        n = -n;
    return stream;
}

istream &operator>>(istream &stream, uint128 &n)
{
    n = 0;
    char c;
    if (!(stream >> c))
        return stream;
    while (isdigit((unsigned char)c))
    {
        n = n * 10 + (c - '0');
        if (!stream.get(c))
            break;
    }
    return stream;
}

using u128 = __uint128_t;
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

constexpr inline uint32_t bitWidth128(u128 x)
{
    if (x == 0)
        return 0;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t lo = (uint64_t)x;
    uint32_t bits = hi ? 128 - __builtin_clzll(hi) : 64 - __builtin_clzll(lo);
    return bits;
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

u128 parseU128(const string &s)
{
    u128 n = 0;
    for (char c : s)
        n = n * 10 + (c - '0');
    return n;
}

void readAns(InStream &stream, u128 target)
{
    int count = stream.readInt(0, 128, "count");
    u128 prod = 1;
    u128 limit = ~(u128)0;
    u128 prevP = 0;
    for (int i = 0; i < count; i++)
    {
        string pStr = stream.readToken("[0-9]+", "pStr");
        u128 p = parseU128(pStr);
        if (p < prevP)
            stream.quitf(_wa, "Factors are not in non-descending order");
        prevP = p;
        if (!isBPSWPrime(p))
            stream.quitf(_wa, "Factor is not prime");
        if (limit / prod < p)
            stream.quitf(_wa, "Product exceeds 128-bit limit");
        prod *= p;
    }
    if (prod != target)
        stream.quitf(_wa, "Product of factors does not equal the target number");
}

int main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);
    int t = 1;
    t = inf.readInt();
    for (int i = 0; i < t; i++)
    {
        setTestCase(i + 1);
        string nStr = inf.readToken("[0-9]+", "nStr");
        u128 target = parseU128(nStr);
        readAns(ouf, target);
    }
    quitf(_ok, "Correct prime factorization");
    return 0;
}