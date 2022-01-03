#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include<iostream>

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);
    const int n = N_MAX;
    std::vector<int>p(n);
    auto dfs=[&](auto dfs,int l,int r,int mn,int mx)->void{
        if(r-l<7){
            // std::cerr<<l<<" "<<r<<std::endl;
            // assert(r>l);
            auto tmp=gen.perm<int>(r-l);
            for(int i=0;i<r-l;++i)p[l+i]=tmp[i]+mn;
        }else{
            auto sep=gen.choice(4,mn+1,mx-1);
            sep.insert(sep.begin(),mn);
            sep.emplace_back(mx);
            // std::cerr<<sep.size()<<std::endl;
            // for(int i=0;i<4;++i){
            //     assert(sep[i+1]>sep[i]);
            // }
            // std::cerr<<sep[0]<<sep[2]<<sep[4]<<std::endl;
            const int type=gen.uniform(0,3);
            if(type==0){
                //cut node
                std::array<int,5>v={4,2,0,3,1};
                int m=l;
                for(int i=0;i<5;++i){
                    dfs(dfs,m,m+sep[v[i]+1]-sep[v[i]],sep[v[i]],sep[v[i]+1]);
                    m+=sep[v[i]+1]-sep[v[i]];
                }
                assert(m==r);
            }else if(type==1){
                //cut node
                std::array<int,5>v={0,3,1,4,2};
                int m=l;
                for(int i=0;i<5;++i){
                    dfs(dfs,m,m+sep[v[i]+1]-sep[v[i]],sep[v[i]],sep[v[i]+1]);
                    m+=sep[v[i]+1]-sep[v[i]];
                }
                assert(m==r);
            }else{
                // join node
                const int sep_size=gen.uniform(2,5);
                auto sep=gen.choice(sep_size-1,mn+1,mx-1);
                sep.insert(sep.begin(),mn);
                sep.emplace_back(mx);
                int m=l;
                for(int i=0;i<sep_size;++i){
                    dfs(dfs,m,m+sep[i+1]-sep[i],sep[i],sep[i+1]);
                    m+=sep[i+1]-sep[i];
                }
                assert(m==r);
            }
        }
    };
    dfs(dfs,0,n,0,n);
    std::cout<<n<<'\n';
    for(int i=0;i<n;++i){
        if(i)std::cout<<" ";
        std::cout<<p[i];
    }
    std::cout<<'\n';
}
