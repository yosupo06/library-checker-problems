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
    long long n = LargestIf([&](long long x){ return (5ll<<x) <= max_count; });
    std::vector<long long> A, B;
    for(long long x=0; x<(1ll<<n); x++){
        long long la = 0, lb = 1, ra = 1, rb = 0;
        for(long long i=0; i<n; i++){
            if((x >> i) & 1ll){ la += ra; lb += rb; }
            else{ ra += la; rb += lb; }
        }

        // a + t * b <= upper , c + t * d <= upper
        auto MaxMove = [upper](long long a, long long b, long long c, long long d){
            long long t = upper;
            if(b != 0) t = std::min(t, (upper - a) / b);
            if(d != 0) t = std::min(t, (upper - c) / d);
            return t;
        };

        A.push_back(la + ra); B.push_back(lb + rb);

        long long t1 = MaxMove(ra, la, rb, lb);
        A.push_back(la * t1 + ra); B.push_back(lb * t1 + rb);
        B.push_back(la * t1 + ra); A.push_back(lb * t1 + rb);

        long long t2 = MaxMove(la, lb, ra, rb);
        A.push_back(la + lb * t2); B.push_back(ra + rb * t2);
        B.push_back(la + lb * t2); A.push_back(ra + rb * t2);
    }
    return std::make_pair(std::move(A), std::move(B));
}
