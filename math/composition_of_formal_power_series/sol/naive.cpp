#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <cstdint>

#define MOD 998244353LL
using namespace::std;

template<typename T,typename F>
struct FPS_BASE:vector<T>{
    using vector<T>::vector;
    using P=FPS_BASE<T,F>;
    F fft;
    FPS_BASE(){}
    inline P operator +(T x)const noexcept{return P(*this)+=x;}
    inline P operator -(T x)const noexcept{return P(*this)-=x;}
    inline P operator *(T x)const noexcept{return P(*this)*=x;}
    inline P operator /(T x)const noexcept{return P(*this)/=x;}
    inline P operator <<(int x)noexcept{return P(*this)<<=x;}
    inline P operator >>(int x)noexcept{return P(*this)>>=x;}
    inline P operator +(const P& x)const noexcept{return P(*this)+=x;}
    inline P operator -(const P& x)const noexcept{return P(*this)-=x;}
    inline P operator -()const noexcept{return P(1,T(0))-=P(*this);}
    inline P operator *(const P& x)const noexcept{return P(*this)*=x;}
    inline P operator /(const P& x)const noexcept{return P(*this)/=x;}
    inline P operator %(const P& x)const noexcept{return P(*this)%=x;}
    bool operator ==(P x){
        for(int i=0;i<(int)max((*this).size(),x.size());++i){
            if(i>=(int)(*this).size()&&x[i]!=T())return 0;
            if(i>=(int)x.size()&&(*this)[i]!=T())return 0;
            if(i<(int)min((*this).size(),x.size()))if((*this)[i]!=x[i])return 0;
        }
        return 1;
    }
    P &operator +=(T x){
        if(this->size()==0)this->resize(1,T(0));
        (*this)[0]+=x;
        return (*this);
    }
    P &operator -=(T x){
        if(this->size()==0)this->resize(1,T(0));
        (*this)[0]-=x;
        return (*this);
    }
    P &operator *=(T x){
        for(int i=0;i<(int)this->size();++i){
            (*this)[i]*=x;
        }
        return (*this);
    }
    P &operator /=(T x){
        return (*this)*=(T(1)/x);
    }
    P &operator <<=(int x){
        P ret(x,T(0));
        ret.insert(ret.end(),begin(*this),end(*this));
        return (*this)=ret;
    }
    P &operator >>=(int x){
        P ret;
        ret.insert(ret.end(),begin(*this)+x,end(*this));
        return (*this)=ret;
    }
    P &operator +=(const P& x){
        if(this->size()<x.size())this->resize(x.size(),T(0));
        for(int i=0;i<(int)x.size();++i){
            (*this)[i]+=x[i];
        }
        return (*this);
    }
    P &operator -=(const P& x){
        if(this->size()<x.size())this->resize(x.size(),T(0));
        for(int i=0;i<(int)x.size();++i){
            (*this)[i]-=x[i];
        }
        return (*this);
    }
    P &operator *=(const P& x){
        return (*this)=F()(*this,x);
    }
    P &operator /=(P x){
        if(this->size()<x.size()) {
            this->clear();
            return (*this);
        }
        const int n=this->size()-x.size()+1;
        return (*this) = (rev().pre(n)*x.rev().inv(n)).pre(n).rev(n);
    }
    P &operator %=(const P& x){
        return ((*this)-=*this/x*x);
    }
    inline void print(){
        for(int i=0;i<(int)(*this).size();++i)cerr<<(*this)[i]<<" \n"[i==(int)(*this).size()-1];
        if((int)(*this).size()==0)cerr<<endl;
    }
    inline P& shrink(){while((*this).back()==0)(*this).pop_back();return (*this);}
    inline P pre(int sz)const{
        return P(begin(*this),begin(*this)+min((int)this->size(),sz));
    }
    P rev(int deg=-1){
        P ret(*this);
        if(deg!=-1)ret.resize(deg,T(0));
        reverse(begin(ret),end(ret));
        return ret;
    }
    P inv(int deg=-1){
        assert((*this)[0]!=T(0));
        const int n=deg==-1?this->size():deg;
        P ret({T(1)/(*this)[0]});
        for(int i=1;i<n;i<<=1){
            ret*=(-ret*pre(i<<1)+2).pre(i<<1);
        }
        return ret.pre(n);
    }
    inline P dot(const P& x){
        P ret(*this);
        for(int i=0;i<int(min(this->size(),x.size()));++i){
            ret[i]*=x[i];
        }
        return ret;
    }
    P diff(){
        if((int)(*this).size()<=1)return P();
        P ret(*this);
        for(int i=0;i<(int)ret.size();i++){
            ret[i]*=i;
        }
        return ret>>1;
    }
    P integral(){
        P ret(*this);
        for(int i=0;i<(int)ret.size();i++){
            ret[i]/=i+1;
        }
        return ret<<1;
    }
    P log(int deg=-1){
        assert((*this)[0]==T(1));
        const int n=deg==-1?this->size():deg;
        return (diff()*inv(n)).pre(n-1).integral();
    }
    P exp(int deg=-1){
        assert((*this)[0]==T(0));
        const int n=deg==-1?this->size():deg;
        P ret({T(1)});
        for(int i=1;i<n;i<<=1){
            ret=ret*(pre(i<<1)+1-ret.log(i<<1)).pre(i<<1);
        }
        return ret.pre(n);
    }
    P pow(int c,int deg=-1){
        // const int n=deg==-1?this->size():deg;
        // long long i=0;
        // P ret(*this);
        // while(i!=(int)this->size()&&ret[i]==0)i++;
        // if(i==(int)this->size())return P(n,0);
        // if(i*c>=n)return P(n,0);
        // T k=ret[i];
        // return ((((ret>>i)/k).log()*c).exp()*(k.pow(c))<<(i*c)).pre(n);
        P x(*this);
        P ret(1,1);
        while(c) {
            if(c&1){
                ret*=x;
                if(~deg)ret=ret.pre(deg);
            }
            x*=x;
            if(~deg)x=x.pre(deg);
            c>>=1;
        }
        return ret;
    }
    P sqrt(int deg=-1){
        const int n=deg==-1?this->size():deg;
        if((*this)[0]==T(0)) {
            for(int i=1;i<(int)this->size();i++) {
                if((*this)[i]!=T(0)) {
                    if(i&1)return{};
                    if(n-i/2<=0)break;
                    auto ret=(*this>>i).sqrt(n-i/2)<<(i/2);
                    if((int)ret.size()<n)ret.resize(n,T(0));
                    return ret;
                }
            }
            return P(n,0);
        }
        P ret({T(1)});
        for(int i=1;i<n;i<<=1){
            ret=(ret+pre(i<<1)*ret.inv(i<<1)).pre(i<<1)/T(2);
        }
        return ret.pre(n);
    }
    P shift(int c){
        const int n=this->size();
        P f(*this),g(n,0);
        for(int i=0;i<n;++i)f[i]*=T(i).fact();
        for(int i=0;i<n;++i)g[i]=T(c).pow(i)/T(i).fact();
        g=g.rev();
        f*=g;
        f>>=n-1;
        for(int i=0;i<n;++i)f[i]/=T(i).fact();
        return f;
    }
    T eval(T x){
        T res=0;
        for(int i=(int)this->size()-1;i>=0;--i){
            res*=x;
            res+=(*this)[i];
        }
        return res;
    }
    vector<T> multipoint_eval(const vector<T>&x){
        const int n=x.size();
        P* v=new P[2*n-1];
        for(int i=0;i<n;i++)v[i+n-1]={T()-x[i],T(1)};
        for(int i=n-2;i>=0;i--){v[i]=v[i*2+1]*v[i*2+2];}
        v[0]=P(*this)%v[0];v[0].shrink();
        for(int i=1;i<n*2-1;i++){
            v[i]=v[(i-1)/2]%v[i];
            v[i].shrink();
        }
        vector<T>res(n);
        for(int i=0;i<n;i++)res[i]=v[i+n-1][0];
        return res;
    }
    P slice(int s,int e,int k){
        P res;
        for(int i=s;i<e;i+=k)res.push_back((*this)[i]);
        return res;
    }
    T nth_term(P q,int64_t x){
        if(x==0)return (*this)[0]/q[0];
        P p(*this);
        P q2=q;
        for(int i=1;i<(int)q2.size();i+=2)q2[i]*=-1;
        q*=q2;
        p*=q2;
        return p.slice(x%2,p.size(),2).nth_term(q.slice(0,q.size(),2),x/2);
    }
    
    //(*this)(t(x))
    P manipulate(P t,int deg){
        P s=P(*this);
        if(deg==0)return P();
        if((int)t.size()==1)return P{s.eval(t[0])};
        int k=min((int)::sqrt(deg/(::log2(deg)+1))+1,(int)t.size());
        int b=deg/k+1;
        P t2=t.pre(k);
        vector<P>table(s.size()/2+1,P{1});
        for(int i=1;i<(int)table.size();i++){
            table[i]=((table[i-1])*t2).pre(deg);
        }
        auto f=[&](auto f,auto l,auto r,int deg)->P{
            if(r-l==1)return P{*l};
            auto m=l+(r-l)/2;
            return f(f,l,m,deg)+(table[m-l]*f(f,m,r,deg)).pre(deg);
        };
        P ans=P();
        P tmp=f(f,s.begin(),s.end(),deg);
        P tmp2=P{1};
        T tmp3=T(1);
        P tmp4=t2.diff().inv(deg);
        for(int i=0;i<b;++i){
            ans+=(tmp*tmp2).pre(deg)/tmp3;
            tmp=(tmp.diff()*tmp4).pre(deg);
            tmp2=(tmp2*(t-t2)).pre(deg);
            tmp3*=T(i+1);
        }
        return ans;
    }
    //(*this)(t(x))
    P manipulate2(P t,int deg){
        P ans=P();
        P s=(*this).rev();
        for(int i=0;i<(int)s.size();++i){
            ans=(ans*t+s[i]).pre(deg);
        }
        return ans;
    }
};

template<typename Mint>
struct _FPS9{
    template<typename T>
    T operator()(T s,T t){
        if(s==decltype(s)())return decltype(s)();
        if(t==decltype(t)())return decltype(t)();
        auto ntt=[](auto v,const bool& inv){
            const int n=v.size();
            assert(Mint::get_mod()>=3&&Mint::get_mod()%2==1);
            decltype(v) tmp(n,Mint());
            Mint root=inv?Mint(Mint::root()).inv():Mint::root();
            for(int b=n>>1;b>=1;b>>=1,v.swap(tmp)){
                Mint w=root.pow((Mint::get_mod()-1)/(n/b)),p=1;
                for(int i=0;i<n;i+=b*2,p*=w)for(int j=0;j<b;++j){
                    v[i+j+b]*=p;
                    tmp[i/2+j]=v[i+j]+v[i+b+j];
                    tmp[n/2+i/2+j]=v[i+j]-v[i+b+j];
                }
            }
            if(inv)v/=n;
            return v;
        };
        const int n=s.size()+t.size()-1;
        int h=1;
        while((1<<h)<n)h++;
        s.resize((1<<h),Mint(0));
        t.resize((1<<h),Mint(0));
        return ntt(ntt(s,0).dot(ntt(t,0)),1).pre(n);
    }
};
template<typename Mint>using fps=FPS_BASE<Mint,_FPS9<Mint>>;

class mint {
  using u64 = std::uint_fast64_t;
    public:
    u64 a;
    constexpr mint(const long long x = 0)noexcept:a(x>=0?x%get_mod():get_mod()-(-x)%get_mod()){}
    constexpr u64 &value()noexcept{return a;}
    constexpr const u64 &value() const noexcept {return a;}
    constexpr mint operator+(const mint rhs)const noexcept{return mint(*this) += rhs;}
    constexpr mint operator-(const mint rhs)const noexcept{return mint(*this)-=rhs;}
    constexpr mint operator*(const mint rhs) const noexcept {return mint(*this) *= rhs;}
    constexpr mint operator/(const mint rhs) const noexcept {return mint(*this) /= rhs;}
    constexpr mint &operator+=(const mint rhs) noexcept {
        a += rhs.a;
        if (a >= get_mod())a -= get_mod();
        return *this;
    }
    constexpr mint &operator-=(const mint rhs) noexcept {
        if (a<rhs.a)a += get_mod();
        a -= rhs.a;
        return *this;
    }
    constexpr mint &operator*=(const mint rhs) noexcept {
        a = a * rhs.a % get_mod();
        return *this;
    }
    constexpr mint operator++(int) noexcept {
        a += 1;
        if (a >= get_mod())a -= get_mod();
        return *this;
    }
    constexpr mint operator--(int) noexcept {
        if (a<1)a += get_mod();
        a -= 1;
        return *this;
    }
    constexpr mint &operator/=(mint rhs) noexcept {
        u64 exp=get_mod()-2;
        while (exp) {
            if (exp % 2) {
                *this *= rhs;
            }
            rhs *= rhs;
            exp /= 2;
        }
        return *this;
    }
    constexpr bool operator==(mint x) noexcept {
        return a==x.a;
    }
    constexpr bool operator!=(mint x) noexcept {
        return a!=x.a;
    }
    constexpr bool operator<(mint x) noexcept {
        return a<x.a;
    }
    constexpr bool operator>(mint x) noexcept {
        return a>x.a;
    }
    constexpr bool operator<=(mint x) noexcept {
        return a<=x.a;
    }
    constexpr bool operator>=(mint x) noexcept {
        return a>=x.a;
    }
    constexpr static int root(){
        mint root = 2;
        while(root.pow((get_mod()-1)>>1).a==1)root++;
        return root.a;
    }
    constexpr mint pow(long long n){
        long long x=a;
        mint ret = 1;
        while(n>0) {
            if(n&1)(ret*=x);
            (x*=x)%=get_mod();
            n>>=1;
        }
        return ret;
    }
    constexpr mint inv(){
        return pow(get_mod()-2);
    }
    static vector<mint> fac,ifac;
    static bool init;
    constexpr static int mx=10000001;
    void build(){
        init=0;
        fac.resize(mx);
        ifac.resize(mx);
        fac[0]=1,ifac[0]=1;
        for(int i=1;i<mx;i++)fac[i]=fac[i-1]*i;
        ifac[mx-1]=fac[mx-1].inv();
        for(int i=mx-2;i>=0;i--)ifac[i]=ifac[i+1]*(i+1);
    }
    mint comb(long long b){
        if(init)build();
        if(a==0&&b==0)return 1;
        if((long long)a<b)return 0;
        return fac[a]*ifac[a-b]*ifac[b];
    }
    mint fact(){
        if(init)build();
        return fac[a];
    }
    mint fact_inv(){
        if(init)build();
        return ifac[a];
    }
    friend ostream& operator<<(ostream& lhs, const mint& rhs) noexcept {
        lhs << rhs.a;
        return lhs;
    }
    friend istream& operator>>(istream& lhs,mint& rhs) noexcept {
        lhs >> rhs.a;
        return lhs;
    }
    constexpr static u64 get_mod(){return MOD;}
};
vector<mint> mint::fac;
vector<mint> mint::ifac;
bool mint::init=1;

int main(){
    int n;
    cin>>n;
    fps<mint>f(n),g(n);
    for(int i=0;i<n;++i)cin>>f[i];
    for(int i=0;i<n;++i)cin>>g[i];
    auto h=f.manipulate2(g,n);
    h.resize(n,0);
    for(int i=0;i<n;++i)cout<<h[i]<<" \n"[i==n-1];
}