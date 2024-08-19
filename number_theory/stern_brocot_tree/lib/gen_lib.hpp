#pragma once
#include "gcd.hpp"
#include <utility>
#include <vector>
#include <algorithm>

template<class F>
long long LargestIf(F f){
    long long x = 0;
    while(f(x)) x++;
    x--;
    return x;
}

template<class Gen>
std::pair<long long, long long> RandomCoprime(Gen& gen, long long upper){
    long long a = gen.template uniform<long long>(1, upper);
    long long b = gen.template uniform<long long>(1, upper);
    long long g_ab = Gcd(a, b);
    a /= g_ab; b /= g_ab;
    return std::make_pair(a, b);
}

std::pair<std::vector<long long>, std::vector<long long>> SmallCoprime(long long sqrt_count){
    std::vector<long long> A, B;
    for(int a=1; a<=sqrt_count; a++){
        int b = 1;
        for(int bi=1; bi<=sqrt_count; bi++){
            while(Gcd(a, b) != 1) b++;
            A.push_back(a);
            B.push_back(b);
            b++;
        }
    }
    return std::make_pair(std::move(A), std::move(B));
}

std::pair<std::vector<long long>, std::vector<long long>> EdgeCoprime(long long max_count, long long upper){
    long long n = LargestIf([&](long long x){ return (7ll<<x) <= max_count; });

    // a + t * b <= upper , c + t * d <= upper
    auto moveAs = [](long long& la, long long& lb, long long& ra, long long& rb, long long x, int n){
        for(long long i=0; i<n; i++){
            if((x >> i) & 1ll){ la += ra; lb += rb; }
            else{ ra += la; rb += lb; }
        }
    };

    // a + t * b <= upper , c + t * d <= upper
    auto MaxMove = [](long long a, long long b, long long c, long long d, long long upper){
        long long t = upper;
        if(b != 0) t = std::min(t, (upper - a) / b);
        if(d != 0) t = std::min(t, (upper - c) / d);
        return t;
    };

    // [any move]
    // [any move] + L*max
    // [any move] + R*max
    // L*max + [any move]
    // R*max + [any move]
    std::vector<long long> A, B;
    for(long long x=0; x<(1ll<<n); x++){
        long long la = 0, lb = 1, ra = 1, rb = 0;
        moveAs(la, lb, ra, rb, x, n);

        A.push_back(la + ra); B.push_back(lb + rb);

        long long t1 = MaxMove(ra, la, rb, lb, upper);
        A.push_back(la * t1 + ra); B.push_back(lb * t1 + rb);
        B.push_back(la * t1 + ra); A.push_back(lb * t1 + rb);

        long long t2 = MaxMove(la, lb, ra, rb, upper);
        A.push_back(la + lb * t2); B.push_back(ra + rb * t2);
        B.push_back(la + lb * t2); A.push_back(ra + rb * t2);
    }

    // [any move] + L*semimax + [any move]
    // [any move] + R*semimax + [any move]
    for(long long x=0; x<(1ll<<(n/2)); x++){
        long long n2 = (n+1)/2;
        long long la = 0, lb = 1, ra = 1, rb = 0;
        moveAs(la, lb, ra, rb, x, n);
        long long t = MaxMove(ra, la, rb, lb, upper >> n2);
        ra += la * t; rb += lb * t;
        for(long long y=0; y<(1ll<<n2); y++){
            long long la2 = la, lb2 = lb, ra2 = ra, rb2 = rb;
            moveAs(la2, lb2, ra2, rb2, y, n2);
            A.push_back(la2 + ra2); B.push_back(lb2 + rb2);
            B.push_back(la2 + ra2); A.push_back(lb2 + rb2);
        }
    }

    return std::make_pair(std::move(A), std::move(B));
}
