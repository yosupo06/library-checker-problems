#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include<iostream>
#include<utility>
#include<algorithm>
#include <array>

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);
    const int n = gen.uniform(N_MIN,N_MAX);
    std::cout<<n<<'\n';
    std::vector<int>p(n);
    std::iota(p.begin(),p.end(),0);
    if(gen.uniform_bool())std::reverse(p.begin(),p.end());
    int q = gen.uniform(0,n);
    while(q--){
        auto [s,t]=gen.uniform_pair<int>(P_MIN,n-1);
        std::swap(p[s],p[t]);
    }
    for(int i=0;i<n;++i){
        if(i)std::cout<<" ";
        std::cout<<p[i];
    }
    std::cout<<'\n';
}
