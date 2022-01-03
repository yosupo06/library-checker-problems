#include<vector>
#include<stack>
#include<algorithm>

#include"lazysegtree.hpp"

namespace permutation_tree{
    template<typename T>
    T op(T x,T y){
        return max(x,y);
    }
    template<typename T>
    T e(){
        return -T(1<<30);
    }
    template<typename T,typename F>
    T mapping(F x,T y){
        return x+y;
    }
    template<typename F>
    F composition(F x,F y){
        return x+y;
    }
    template<typename F>
    F id(){
        return F();
    }
    template<typename T>
    struct perm_tree{
        struct node;
        using np=node*;
        struct node{
            //両方とも半開区間で保存
            int l,r;
            T mn,mx;
            bool is_join;
            std::vector<np>ch;
            node(){}
            node(int idx,T x):l(idx),r(idx+1),mn(x),mx(x+1),is_join(1){};
        };
        std::stack<int>mn_stk,mx_stk;
        std::vector<T>x;
        using F=T;
        atcoder::lazy_segtree<T,op,e,F,mapping,composition,id>seg;
        stack<np>stk;
        perm_tree(const std::vector<T>&x):x(x),seg(x.size()){
            for(int i=0;i<(int)x.size();++i)insert(i);
        }
        np get(){
            assert((int)stk.size()==1);
            return stk.top();
        }
        void insert(int idx){
            {
                int r=idx;
                while(!mn_stk.empty()&&x[mn_stk.top()]>x[idx]){
                    mn_stk.pop();
                    int l=(mn_stk.empty()?0:mn_stk.top()+1);
                    seg.apply(l,r,x[idx]-x[r-1]);
                    r=l;
                }
                mn_stk.emplace(idx);
            }
            {
                int r=idx;
                while(!mx_stk.empty()&&x[mx_stk.top()]<x[idx]){
                    mx_stk.pop();
                    int l=(mx_stk.empty()?0:mx_stk.top()+1);
                    seg.apply(l,r,-x[idx]+x[r-1]);
                    r=l;
                }
                mx_stk.emplace(idx);
            }
            seg.apply(0,idx,1);
            np nw=new node(idx,x[idx]);
            
            while(1){
                if(!stk.empty()&&!stk.top()->ch.empty()&&stk.top()->is_join&&(nw->mn==stk.top()->ch.back()->mx||nw->mx==stk.top()->ch.back()->mn)){
                    stk.top()->ch.emplace_back(nw);
                    stk.top()->mx=max(stk.top()->mx,nw->mx);
                    stk.top()->mn=min(stk.top()->mn,nw->mn);
                    stk.top()->r=idx+1;
                    nw=stk.top();
                    stk.pop();
                    continue;
                }
                if(!stk.empty()&&(stk.top()->mx==nw->mn||stk.top()->mn==nw->mx)){
                    np nw2=new node();
                    auto top=stk.top();
                    stk.pop();
                    nw2->is_join=1;
                    nw2->l=top->l;
                    nw2->r=nw->r;
                    nw2->mn=min(top->mn,nw->mn);
                    nw2->mx=max(top->mx,nw->mx);
                    nw2->ch.emplace_back(top);
                    nw2->ch.emplace_back(nw);
                    nw=nw2;
                    continue;
                }
                stk.emplace(nw);
                if((int)stk.size()==1)break;
                T mx=seg.prod(0,stk.top()->l);
                if(mx!=0)break;
                nw=new node();
                *nw=*stk.top();
                nw->is_join=0;
                nw->ch.clear();
                nw->ch.emplace_back(stk.top());
                stk.pop();
                while(1){
                    auto top=stk.top();
                    nw->ch.emplace_back(top);
                    stk.pop();
                    nw->l=min(nw->l,top->l);
                    nw->r=max(nw->r,top->r);
                    nw->mn=min(nw->mn,top->mn);
                    nw->mx=max(nw->mx,top->mx);
                    if(nw->r-nw->l==nw->mx-nw->mn){
                        break;
                    }
                }
                std::reverse(nw->ch.begin(),nw->ch.end());
            }
            seg.set(idx,T());
        }
    };
};
using namespace permutation_tree;