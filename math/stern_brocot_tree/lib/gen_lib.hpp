#pragma once
#include "gcd.hpp"
#include <utility>
#include <vector>

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
