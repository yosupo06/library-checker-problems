#pragma once
#include "gcd.hpp"
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>


class SbtOperators {
public:
    using Int = long long;
    using Path = std::vector<std::pair<char, Int>>;
    struct Fraction {
        Int a;
        Int b;
    };

    static Path encode(Fraction f){
        Path ans;
        Int a = f.a;
        Int b = f.b;
        while(a != 1 || b != 1){
            if(a > b){
                Int k = (a - 1) / b;
                ans.emplace_back('R', k);
                a -= k * b;
            }
            else{
                Int k = (b - 1) / a;
                ans.emplace_back('L', k);
                b -= k * a;
            }
        }
        return ans;
    }

    static Fraction decode(Path f, Int a=1, Int b=1){
        std::reverse(f.begin(), f.end());
        for(auto [c,k] : f){
            if(c == 'L') b += a * k;
            else a += b * k;
        }
        return { a, b };
    }

    static std::pair<Fraction, Fraction> range(Fraction f){
        auto path = encode(f);
        return { decode(path, 0, 1), decode(path, 1, 0) };
    }

    static std::pair<Fraction, Fraction> child(Fraction f){
        auto path = encode(f);
        return { decode(path, 1, 2), decode(path, 2, 1) };
    }

    // if invalid , returns (0,0)
    static Fraction ancestor(Int k, Fraction f){
        auto path = encode(f);
        Path ans;
        for(auto [c,n] : path){
            if(k <= n){
                ans.push_back({c, k});
                return decode(ans);
            }
            ans.push_back({c, n});
            k -= n;
        }
        return {0,0};
    }

    static Fraction lca(Fraction f, Fraction g){
        auto path1 = encode(f);
        auto path2 = encode(g);
        Path ans;
        for(std::size_t i=0; i<std::min(path1.size(), path2.size()); i++){
            auto [c1, n1] = path1[i];
            auto [c2, n2] = path2[i];
            if(c1 != c2) break;
            ans.push_back({c1, std::min(n1, n2)});
            if(n1 != n2) break;
        }
        return decode(ans);
    }

    static Fraction parent(Fraction f){
        auto [l, r] = range(f);
        if(l.a + l.b > r.a + r.b) return l;
        return r;
    }

    static Int depth(Fraction f){
        auto path = encode(f);
        Int res = 0;
        for(auto c : path) res += c.second;
        return res;
    }
};

void output_path(const SbtOperators::Path& path) {
    printf("%d", (int)path.size());
    for(auto [c, n] : path){
        printf(" %c %lld", c, n);
    }
}

SbtOperators::Path input_path() {
    int k; scanf("%d", &k);
    SbtOperators::Path path;
    for(int i=0; i<k; i++){
        char c; scanf(" %c", &c);
        long long n; scanf("%lld", &n);
        path.push_back({ c, n });
    }
    return path;
}
