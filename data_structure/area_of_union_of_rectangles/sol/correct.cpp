#line 1 "sol.cpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#line 1 "library/Template/template.hpp"
using namespace std;

#define rep(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define ALL(v) (v).begin(),(v).end()
using ll=long long int;
const ll INF = 0x1fffffffffffffff;
#line 5 "sol.cpp"

#line 2 "library/DataStructure/lazysegtree.hpp"

template<typename M,typename N,M (*f)(M,M),M (*g)(M,N),N (*h)(N,N),M (*m1)(),N (*n1)()>
    class LazySegmentTree{
    int sz,height;
    vector<M> data;
    vector<N> lazy;
    void update(int k){data[k]=f(data[k*2],data[k*2+1]);}
    void apply(int k,N x){
        data[k]=g(data[k],x);
        if(k<sz)lazy[k]=h(lazy[k],x);
    }
    void down(int k){
        apply(k*2,lazy[k]);
        apply(k*2+1,lazy[k]);
        lazy[k]=n1();
    }
public:
    LazySegmentTree(int n=0):LazySegmentTree(vector<M>(n,m1())){}
    LazySegmentTree(const vector<M>& a){
        sz=1,height=0;
        while(sz<(int)a.size())sz<<=1,height++;
        data.assign(2*sz,m1());
        lazy.assign(sz,n1());
        rep(i,0,a.size())data[sz+i]=a[i];
        for(int i=sz-1;i;i--)update(i);
    }
    void set(int k,M x){
        k+=sz;
        for(int i=height;i;i--)down(k>>i);
        data[k]=x;
        for(int i=1;i<=height;i++)update(k>>i);
    }
    void update(int L,int R,N x){
        if(L>=R)return;
        L+=sz,R+=sz;
        for(int i=height;i;i--){
            if(((L>>i)<<i)!=L)down(L>>i);
            if(((R>>i)<<i)!=R)down((R-1)>>i);
        }
        int lb=L,rb=R;
        while(L<R){
            if(L&1)apply(L++,x);
            if(R&1)apply(--R,x);
            L>>=1;
            R>>=1;
        }
        L=lb,R=rb;
        for(int i=1;i<=height;i++){
            if(((L>>i)<<i)!=L)update(L>>i);
            if(((R>>i)<<i)!=R)update((R-1)>>i);
        }
    }
    M query(int L,int R){
        if(L>=R)return m1();
        L+=sz,R+=sz;
        for(int i=height;i;i--){
            if(((L>>i)<<i)!=L)down(L>>i);
            if(((R>>i)<<i)!=R)down((R-1)>>i);
        }
        M lb=m1(),rb=m1();
        while(L<R){
            if(L&1)lb=f(lb,data[L++]);
            if(R&1)rb=f(data[--R],rb);
            L>>=1;
            R>>=1;
        }
        return f(lb,rb);
    }
};

/**
 * @brief Lazy Segment Tree
 */
#line 3 "library/DataStructure/unionrect.hpp"

struct UnionInterval{
    struct M{
        ll len,mi,cnt;
    };
    static M f(M a,M b){
        if(a.mi<b.mi)return {a.len+b.len,a.mi,a.cnt};
        else if(a.mi>b.mi)return {a.len+b.len,b.mi,b.cnt};
        else return {a.len+b.len,a.mi,a.cnt+b.cnt};
    }
    static M g(M a,int b){
        return M{a.len,min(INF,a.mi+b),a.cnt};
    }
    static int h(int a,int b){
        return a+b;
    }
    static M m1(){
        return M{0,INF,0};
    }
    static int m2(){return 0;}

    const int n=0;
    LazySegmentTree<M,int,f,g,h,m1,m2> seg;
    UnionInterval(){}
    UnionInterval(vector<int>& xs):n(xs.size()-1){
        vector<M> init(n);
        rep(i,0,n){
            init[i]=M{xs[i+1]-xs[i],0,xs[i+1]-xs[i]};
        }
        seg=LazySegmentTree<M,int,f,g,h,m1,m2>(init);
    }
    void add(int L,int R){
        seg.update(L,R,1);
    }
    void erase(int L,int R){
        seg.update(L,R,-1);
    }
    ll run(){
        auto [len,mi,cnt]=seg.query(0,n);
        if(mi==0)len-=cnt;
        return len;
    }
};

struct UnionRect{
    vector<int> L,R,D,U;
    UnionRect(){}
    void add(int lb,int rb,int db,int ub){
        L.push_back(lb);
        R.push_back(rb);
        D.push_back(db);
        U.push_back(ub);
    }
    ll run(){
        int n=L.size();
        vector<int> xs=L,ys=D;
        xs.insert(xs.end(),ALL(R));
        ys.insert(ys.end(),ALL(U));
        sort(ALL(xs));
        xs.erase(unique(ALL(xs)),xs.end());
        sort(ALL(ys));
        ys.erase(unique(ALL(ys)),ys.end());

        UnionInterval buf=UnionInterval(ys);
        using P=pair<int,int>;
        vector in(xs.size(),vector<P>()),out(xs.size(),vector<P>());
        rep(i,0,n){
            L[i]=lower_bound(ALL(xs),L[i])-xs.begin();
            R[i]=lower_bound(ALL(xs),R[i])-xs.begin();
            D[i]=lower_bound(ALL(ys),D[i])-ys.begin();
            U[i]=lower_bound(ALL(ys),U[i])-ys.begin();
            in[L[i]].push_back({D[i],U[i]});
            out[R[i]].push_back({D[i],U[i]});
        }
        ll ret=0;
        rep(i,0,xs.size()-1){
            for(auto& [d,u]:in[i])buf.add(d,u);
            for(auto& [d,u]:out[i])buf.erase(d,u);
            ret+=buf.run()*(xs[i+1]-xs[i]);
        }
        return ret;
    }
};

/**
 * @brief Area of Union of Rectangles
 */
#line 7 "sol.cpp"

int main(){
    int n;
    scanf("%d",&n);
    UnionRect buf;
    for (int i = 0; i < n; i++) {
        int L,D,R,U;
        scanf("%d%d%d%d",&L,&D,&R,&U);
        buf.add(L,R,D,U);
    }
    printf("%lld\n",buf.run());
    return 0;
}
