#include<vector>
#include<algorithm>
#include<iostream>
#include<assert.h>
using namespace std;
using ll=long long;
template<int Mod> struct ModInt{
    static constexpr int mod=Mod;
    int x;
    constexpr ModInt() : x(0) {}
    constexpr ModInt(ll X) : x(X%mod) { if(x<0) x+=mod; }
    ModInt &operator+=(const ModInt &a) { x += a.x; if (x >= mod) x -= mod; return *this; }
    ModInt &operator-=(const ModInt &a) { x -= a.x; if (x < 0) x += mod; return *this; }
    ModInt &operator*=(const ModInt &a) { x = static_cast<int>((static_cast<ll>(x) * a.x) % mod); return *this; }
    ModInt &operator/=(const ModInt &a) { return *this = *this * a.inv(); }
    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
    ModInt operator-() const { return ModInt(-x); }
    ModInt pow(ll e) const {
        ModInt X=x,ret=1;
        for(;e;e>>=1){
            if(e&1) ret*=X;
            X*=X;
        }
        return ret;
    }
    ModInt inv() const {
        int a=x,b=mod,y=1,z=0,t;
        for(;;){
            t=a/b;
            a-=t*b;
            if(a==0){
                assert(b==1||b==-1);
                return ModInt(b*z);
            }
            y-=t*z;
            t=b/a;
            b-=t*a;
            if(b==0){
                assert(a==1||a==-1);
                return ModInt(a*y);
            }
            z-=t*y;
        }
    }
    friend ModInt operator+(ll a, const ModInt &b) { return (ModInt(a) += b); }
    friend ModInt operator-(ll a, const ModInt &b) { return (ModInt(a) -= b); }
    friend ModInt operator*(ll a, const ModInt &b) { return (ModInt(a) *= b); }
    friend bool operator==(const ModInt &a, const ModInt &b) {
        return a.x == b.x;
    }
    friend bool operator!=(const ModInt &a, const ModInt &b) {
        return a.x != b.x;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};
template<int Mod,int G,int lg> struct NTT{
    using mint=ModInt<Mod>;
    mint g[1<<(lg-1)];
    constexpr NTT() : g(){
        static_assert(lg>=2);
        static_assert(!((Mod-1)&((1<<lg)-1)));
        g[0]=1;
        g[1<<(lg-2)]=mint(G).pow((Mod-1)>>lg);
        for(int l=1<<(lg-2);l>=2;l>>=1){
            g[l>>1]=g[l]*g[l];
        }
        assert((g[1]*g[1]).x==Mod-1);
        for(int l=2;l<=1<<(lg-2);l<<=1){
            for(int i=1;i<l;i++){
                g[l+i]=g[l]*g[i];
            }
        }
    }
    void fft(vector<mint> &x) const {
        const int n=x.size();
        assert(!(n&(n-1)) && n<=1<<lg);
        for(int l=n;l>>=1;){
            for(int i=0;i<(n>>1)/l;i++){
                for(int j=(i<<1)*l;j<(i<<1|1)*l;j++){
                    const mint t=g[i]*x[j+l];
                    x[j+l]=x[j]-t;
                    x[j]+=t;
                }
            }
        }
        for(int i=0,j=0;i<n;i++){
            if(i<j) swap(x[i], x[j]);
            for(int l=n;(l>>=1) && !((j^=l)&l);){}
        }
    }
    vector<mint> convolution(const vector<mint> &a,const vector<mint> &b) const {
        const int na=a.size(),nb=b.size();
        int n=1,invN=1;
        for(;n<na+nb-1;n<<=1) invN=((invN&1) ? (invN+Mod) : invN)>>1;
        vector<mint> x(n),y(n);
        copy(a.begin(),a.end(),x.begin());
        copy(b.begin(),b.end(),y.begin());
        fft(x),fft(y);
        for(int i=0;i<n;i++) x[i]=x[i]*y[i]*invN;
        reverse(x.begin()+1,x.end());
        fft(x);
        x.resize(na+nb-1);
        return x;
    }
};
template<typename T> struct FormalPowerSeries : vector<T>{
    using vector<T>::vector;
    template<class...Args>
    FormalPowerSeries(Args...args) : vector<T>(args...){}
    FormalPowerSeries operator*(const FormalPowerSeries &b) const;
    FormalPowerSeries operator+(const FormalPowerSeries &b) const;
    FormalPowerSeries operator*(T c) const;
    FormalPowerSeries operator+(T c) const;
    FormalPowerSeries operator-(const FormalPowerSeries &b) const;
    FormalPowerSeries operator<<(int x) const;
    FormalPowerSeries operator>>(int x) const;
};
NTT<998244353,3,20> ntt;
template<typename T>
FormalPowerSeries<T> pre(const FormalPowerSeries<T> &f,int deg){
    return FormalPowerSeries<T>(begin(f),begin(f)+min((int)f.size(),deg));
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator*(const FormalPowerSeries<T> &b) const {
    return ntt.convolution((*this),b);
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator*(T c) const {
    FormalPowerSeries<T> res(this->size());
    for(int i=0;i<(int)this->size();i++) res[i]=(*this)[i]*c;
    return res;
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator+(const FormalPowerSeries<T> &b) const {
    FormalPowerSeries<T> res=(*this);
    if(b.size()>this->size()) res.resize(b.size());
    for(int i=0;i<(int)b.size();i++) res[i]+=b[i];
    return res;
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator+(T c) const {
    FormalPowerSeries<T> res=(*this);
    res[0]+=c;
    return res;
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator-(const FormalPowerSeries<T> &b) const {
    FormalPowerSeries<T> res=(*this);
    if(b.size()>this->size()) res.resize(b.size());
    for(int i=0;i<(int)b.size();i++) res[i]-=b[i];
    return res;
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator<<(int x) const {
    FormalPowerSeries<T> res(x,0);
    res.insert(res.end(),begin(*this),end(*this));
    return res;
}
template<typename T>
FormalPowerSeries<T> FormalPowerSeries<T>::operator>>(int x) const {
    FormalPowerSeries<T> res;
    res.insert(res.end(),begin(*this)+x,end(*this));
    return res;
}
template<typename T>
FormalPowerSeries<T>  integral(const FormalPowerSeries<T> &f){
    int n=(int)f.size();
    FormalPowerSeries<T> res(n+1,0);
    for(int i=0;i<n;i++) res[i+1]=f[i]/(i+1);
    return res;
}
template<typename T>
FormalPowerSeries<T> diff(const FormalPowerSeries<T> &f){
    int n=(int)f.size();
    FormalPowerSeries<T> res(n-1,0);
    for(int i=1;i<n;i++) res[i-1]=f[i]*i;
    return res;
}
template<typename T>
FormalPowerSeries<T> inv(const FormalPowerSeries<T> &f,int deg=-1){
    assert(f[0]!=0);
    if(deg<0) deg=(int)f.size();
    FormalPowerSeries<T> res({T(1)/f[0]});
    for(int i=1;i<deg;i<<=1){
        res=pre(res+res-res*res*pre(f,i<<1),i<<1);
    }
    return pre(res,deg);
}
template<typename T>
FormalPowerSeries<T> log(const FormalPowerSeries<T> &f,int deg=-1){
    assert(f[0]==1);
    if(deg<0) deg=(int)f.size();
    FormalPowerSeries<T> res=integral(pre(diff(f)*inv(f,deg),deg-1));
    return res;
}
template<typename T>
FormalPowerSeries<T> exp(const FormalPowerSeries<T> &f,int deg=-1){
    assert(f[0]==0);
    if(deg<0) deg=(int)f.size();
    FormalPowerSeries<T> res(1,1);
    for(int i=1;i<deg;i<<=1){
        res=res*pre(pre(f,i<<1)-log(res,i<<1)+T(1),i<<1);
        res.resize(i<<1);
    }
    return pre(res,deg);
}
template<typename T>
FormalPowerSeries<T> pow(const FormalPowerSeries<T> &f,ll e,int deg=-1){
    if(deg<0) deg=(int)f.size();
    ll i=0;
    if(e==0){
        FormalPowerSeries<T> res(deg);
        res[0]=1;
        return res;
    }
    while(i<(int)f.size()&&f[i]==0&&i*e<deg) i++;
    if(i==(int)f.size()) return FormalPowerSeries<T>(deg,0);
    if(i*e>=deg) return FormalPowerSeries<T>(deg,0);
    T k=f[i];
    FormalPowerSeries<T> res=exp(log((f>>i)*k.inv())*T(e),deg)*k.pow(e)<<(e*i);
    return pre(res,deg);
}
using mint=ModInt<998244353>;
using fps=FormalPowerSeries<mint>;
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    vector<mint> fac(500500),ifac(500500);
    fac[0]=1;
    for(int i=1;i<500500;i++) fac[i]=fac[i-1]*i;
    ifac[500499]=fac[500499].inv();
    for(int i=500498;i>=0;i--) ifac[i]=ifac[i+1]*(i+1);
    fps f(n+1);
    for(int i=1;i<=n;i++){
        f[i]=ifac[i]*fac[i-1];
    }
    f=pow(f,k);
    mint ik=ifac[k];
    for(int N=k;N<=n;N++){
        mint ans=f[N]*fac[N]*ik;
        if((N+k)&1) ans=-ans;
        if(N<n) printf("%d ",ans.x);
        else printf("%d\n",ans.x);
    }
}
