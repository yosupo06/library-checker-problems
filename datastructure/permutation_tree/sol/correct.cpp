#include<bits/stdc++.h>
using namespace std;
#include"permutation_tree.hpp"

int main(){
    int n;
    cin>>n;
    vector<int>p(n);
    for(int i=0;i<n;++i)cin>>p[i];
    perm_tree<int>pt(p);
    auto root=pt.get();
    using np=decltype(root);
    auto dfs=[&](auto dfs,np t)->void{
        cout<<t->l<<" "<<t->r<<(t->l+1==t->r?"leaf":(t->is_join?"join":"cut"))<<endl;
        for(auto e:t->ch){
            dfs(dfs,e);
        }
    };
    dfs(dfs,root);
}