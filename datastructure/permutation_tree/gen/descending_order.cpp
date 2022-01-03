#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include<iostream>

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);
    const int n = gen.uniform(N_MIN,N_SMALL_MAX);
    std::cout<<n<<'\n';
    for(int i=0;i<n;++i){
        if(i)std::cout<<" ";
        std::cout<<n-1-i;
    }
    std::cout<<'\n';
}
