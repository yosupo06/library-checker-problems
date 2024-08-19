#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

long long pow(long long a, long long n, long long p) {
    long long r=1;
    for (;n>0;n>>=1,a=a*a%p)if(n%2==1)r=r*a%p;
    return r;
}

int cnt(long long a,long long base,long long p) {
    int ret=0;
    while (a!=1) {
        a=pow(a,base,p);
        ++ret;
    }
    return ret;
}

long long inv(long long a, long long p) {
    a%=p;
    long long u=1, v=0;
    long long b=p;
    while (b>0) {
        long long q=a/b;
        a%=b;
        u-=v*q%p;
        u=(u%p+p)%p;
        {
            u^=v;v^=u;u^=v;
            a^=b;b^=a;a^=b;
        }
    }
    return u<0?u+p:u;
}

long long gcd(long long a,long long b) {
    return a==0?b:gcd(b%a,a);
}
    
long long peth_root(long long a,long long p,int e,long long mod) {
    long long q=mod-1;
    int s=0;
    while (q%p==0) {
        q/=p;
        ++s;
    }
    long long pe=pow(p,e,mod);
    long long ans=pow(a,((pe-1)*inv(q,pe)%pe*q+1)/pe,mod);
    long long c=2;
    while (pow(c,(mod-1)/p,mod)==1)
        ++c;
    c=pow(c,q,mod);
    std::map<long long,int> map;
    long long add=1;
    int v=(int)std::sqrt((double)(s-e)*p)+1;
    long long mul=pow(c,v*pow(p,s-1,mod-1)%(mod-1),mod);
    for (int i=0;i<=v;++i) {
        map[add]=i;
        add=add*mul%mod;
    }
    mul=inv(pow(c,pow(p,s-1,mod-1),mod),mod);
    for (int i=e;i<s;++i) {
        long long err=inv(pow(ans,pe,mod),mod)*a%mod;
        long long target=pow(err,pow(p,s-1-i,mod-1),mod);
        for (int j=0; j<=v; ++j) {
            if (map.find(target)!=map.end()) {
                int x=map[target];
                ans=ans*pow(c,(j+v*x)*pow(p,i-e,mod-1)%(mod-1),mod)%mod;
                break;
            }
            target=target*mul%mod;
            assert(j!=v);
        }
    }
    return ans;
}
    
long long kth_root(long long a,long long k,long long p) {
    if(k>0&&a%p==0)return 0;
    k%=p-1;
    long long g=gcd(k,p-1);
    if (pow(a,(p-1)/g,p)!=1)
        return -1;
    a=pow(a,inv(k/g,(p-1)/g),p);
    for (long long div=2;div*div<=g;++div) {
        int sz=0;
        while (g%div==0) {
            g/=div;
            ++sz;
        }
        if (sz>0) {
            long long b=peth_root(a,div,sz,p);
            a=b;
        }
    }
    if (g>1)
        a=peth_root(a,g,1,p);
    return a;
}

int main() {
    int T;
    scanf("%d",&T);
    for(int t=0;t<T;++t){
        long long k,a,p;
        scanf("%lld%lld%lld",&k,&a,&p);
        printf("%lld\n",kth_root(a, k, p));
    }
}
