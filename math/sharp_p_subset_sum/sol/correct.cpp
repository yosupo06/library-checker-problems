#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <functional>
using namespace std;

//template
#define ALL(v) (v).begin(),(v).end()
typedef long long int ll;
void tostr(ll x,string& res){while(x)res+=('0'+(x%10)),x/=10; reverse(ALL(res)); return;}
template<class T> inline bool chmax(T& a,T b){ if(a<b){a=b;return 1;}return 0; }
template<class T> inline bool chmin(T& a,T b){ if(a>b){a=b;return 1;}return 0; }
//end

template<unsigned mod=998244353>struct mint {
   unsigned val;
   static unsigned get_mod(){return mod;}
   unsigned inv() const{
      int tmp,a=val,b=mod,x=1,y=0;
      while(b)tmp=a/b,a-=tmp*b,swap(a,b),x-=tmp*y,swap(x,y);
      if(x<0)x+=mod;
      return x;
   }
   mint():val(0){}
   mint(ll x):val(x>=0?x%mod:mod+(x%mod)){}
   mint pow(ll t){mint res=1,b=*this; while(t){if(t&1)res*=b;b*=b;t>>=1;}return res;}
   mint& operator+=(const mint& x){if((val+=x.val)>=mod)val-=mod;return *this;}
   mint& operator-=(const mint& x){if((val+=mod-x.val)>=mod)val-=mod; return *this;}
   mint& operator*=(const mint& x){val=ll(val)*x.val%mod; return *this;}
   mint& operator/=(const mint& x){val=ll(val)*x.inv()%mod; return *this;}
   mint operator+(const mint& x)const{return mint(*this)+=x;}
   mint operator-(const mint& x)const{return mint(*this)-=x;}
   mint operator*(const mint& x)const{return mint(*this)*=x;}
   mint operator/(const mint& x)const{return mint(*this)/=x;}
   bool operator==(const mint& x)const{return val==x.val;}
   bool operator!=(const mint& x)const{return val!=x.val;}
}; using Mint=mint<>;
struct factorial {
   vector<Mint> Fact,Finv,Inv;
   factorial(int maxx){
      Fact.resize(maxx); Finv.resize(maxx); Inv.resize(maxx);
      Fact[0]=Fact[1]=Finv[0]=Finv[1]=Inv[1]=1; unsigned mod=Mint::get_mod();
      for(int i=2;i<maxx;i++){
         Fact[i]=Fact[i-1]*i;
         Inv[i]=Inv[mod%i]*(mod-mod/i);
         Finv[i]=Finv[i-1]*Inv[i];
      }
   }
   Mint fact(int n,bool inv=0){if(inv)return Finv[n];else return Fact[n];}
   Mint inv(int n){return Inv[n];}
   Mint nPr(int n,int r){if(n<0||n<r||r<0)return Mint(0);else return Fact[n]*Finv[n-r];}
   Mint nCr(int n,int r){if(n<0||n<r||r<0)return Mint(0);else return Fact[n]*Finv[r]*Finv[n-r];}
};

template<typename T,unsigned p>struct NTT{
   vector<T> rt,irt;
   NTT(int lg=21){
      unsigned mod=T::get_mod();
      T prt=p; rt.resize(1<<lg,1); irt.resize(1<<lg,1);
      for(int w=0;w<lg;w++){
         int mask=(1<<w)-1,t=(mod-1)>>w;
         T g=prt.pow(t),ig=prt.pow(mod-1-t);
         for(int i=0;i<mask;i++){
            rt[mask+i+1]=g*rt[mask+i];
            irt[mask+i+1]=ig*irt[mask+i];
         }
      }
   }
   void ntt(vector<T>& f,bool inv=0){
      int n=f.size();
      if(inv){
         for(int i=1;i<n;i<<=1)for(int j=0;j<n;j+=i*2)for(int k=0;k<i;k++){
            f[i+j+k]*=irt[i*2-1+k]; const T tmp=f[j+k]-f[i+j+k];
            f[j+k]+=f[i+j+k]; f[i+j+k]=tmp;
         }
         T mul=T(n).inv(); for(int i=0;i<n;i++)f[i]*=mul;
      }else{
         for(int i=n>>1;i;i>>=1)for(int j=0;j<n;j+=i*2)for(int k=0;k<i;k++){
            const T tmp=f[j+k]-f[i+j+k];
            f[j+k]+=f[i+j+k]; f[i+j+k]=tmp*rt[i*2-1+k];
         }
      }
   }
   vector<T> conv(vector<T> a,vector<T> b){
      int n=a.size()+b.size()-1,m=(n&(n-1)?1<<(32-__builtin_clz(n)):n);
      a.resize(m); b.resize(m); ntt(a); ntt(b);
      for(int i=0;i<m;i++)a[i]*=b[i];
      ntt(a,1); a.resize(n); return a; 
   }
};
NTT<Mint,3> ntt;
vector<Mint> multiply(vector<Mint> a,vector<Mint> b){return ntt.conv(a,b);};

template<typename T>struct FPS{
   using V=vector<T>; V f;
   using func=function<V(V,V)>; func conv=multiply;
   FPS(){}
   FPS(func _conv,int _n=1):f(_n),conv(_conv){}
   FPS(func _conv,V _f):f(_f),conv(_conv){}
   T& operator[](const int i){return f[i];}
   T eval(Mint x){T res,w=1; for(T v:f)res+=w*v,w*=x; return res;}
   int size()const{return f.size();}
   FPS resize(int n){f.resize(n); return *this;}
   void shrink(){while(!f.empty() and f.back()==0)f.pop_back();}
   void set_conv(func _conv){conv=_conv;}
   FPS inv()const{
      assert(f[0]!=0);
      int n=f.size(); FPS res(conv,n); res[0]=f[0].inv();
      for(int k=1;k<n;k<<=1){
         FPS g(conv,k),h(conv,k*2);
         for(int i=0;i<min(k,n);i++)g[i]=res[i];
         for(int i=0;i<min(k*2,n);i++)h[i]=f[i];
         g*=g; g*=h; g.resize(k*2);
         for(int i=0;i<min(k*2,n);i++)res[i]=res[i]*2-g[i];
      } return res;
   }
   FPS operator+(const FPS& g)const{return FPS(*this)+=g;}
   FPS operator-(const FPS& g)const{return FPS(*this)-=g;}
   FPS operator*(const FPS& g)const{return FPS(*this)*=g;}
   FPS operator/(const FPS& g)const{return FPS(*this)/=g;}
   FPS operator%(const FPS& g)const{return FPS(*this)%=g;}
   FPS& operator+=(FPS g){
      if(g.size()>f.size())f.resize(g.size());
      for(int i=0;i<size();i++)f[i]+=g[i];
      shrink(); return *this;
   }
   FPS& operator-=(FPS g){
      if(g.size()>f.size())f.resize(g.size());
      for(int i=0;i<size();i++)f[i]-=g[i];
      shrink(); return *this;
   }
   FPS& operator*=(FPS g){f=conv(f,g.f); shrink(); return *this;}
   FPS& operator/=(FPS g){
      if(g.size()>f.size())return *this=FPS(conv);
      reverse(ALL(f)); reverse(ALL(g.f));
      int n=f.size()-g.size()+1;
      f.resize(n); g.resize(n);
      *this*=g.inv(); f.resize(n);
      reverse(ALL(f)); shrink(); return *this;
   }
   FPS& operator%=(FPS g){*this-=*this/g*g; shrink(); return *this;}
   FPS pow(ll k){
      int n=f.size(); FPS ff=*this,res(conv);
      while(k){
         if(k&1){res*=ff; res.resize(n);}
         ff*=ff; ff.resize(n); k>>=1;
      } return res;
   }
   FPS diff(){
      FPS res(conv,f.size()-1);
      for(int i=0;i<res.size();i++)res[i]=f[i+1]*(i+1);
      return res;
   }
   FPS inte(){
      FPS res(conv,f.size()+1);
      for(int i=res.size()-1;i>0;i--)res[i]=f[i-1]/i;
      return res;
   }
   FPS log(){
      assert(f[0]==1);
      int n=f.size(); FPS res(conv); res=diff()*inv(); 
      res=res.inte(); return res.resize(n);
   }
   FPS exp(){
      assert(f[0]==0);
      int m=f.size(),n=(m&(m-1)?1<<(32-__builtin_clz(m)):1);
      f.resize(n); FPS d(conv),res(conv,n); d=diff(); vector<FPS> pre;
      for(int k=n;k;k>>=1){d.resize(k); pre.push_back(d);}
      auto dfs=[&](auto dfs,int l,int r,int dep)->void{
         if(r-l==1){if(l)res[l]/=l; return;}
         int m=(l+r)>>1; dfs(dfs,l,m,dep+1);
         FPS g(conv,r-l);
         for(int i=0;i<m-l;i++)g[i]=res[l+i];
         g*=pre[dep];
         for(int i=m;i<r;i++)res[i]+=g[i-l-1];
         dfs(dfs,m,r,dep+1);
      }; res[0]=1; dfs(dfs,0,n,0); return res.resize(m);
   }
   FPS shift(int c){
      int n=size(); FPS res=*this,mul(conv,n);
      factorial fact(n+1); mul[1]=c; mul=mul.exp();
      for(int i=0;i<n;i++)res[i]*=fact.fact(i);
      reverse(ALL(res.f)); 
      res*=mul; res.resize(n); reverse(ALL(res.f));
      for(int i=0;i<n;i++)res[i]*=fact.fact(i,1);
      return res;
   }
};

constexpr int T=500010;
int cnt[T]={}; factorial fact(T);

int main(){
   int n,t; scanf("%d%d",&n,&t);
   vector<int> a(n);
   for(int i=0;i<n;i++)scanf("%d",&a[i]),cnt[a[i]]++;
   FPS<Mint> f(multiply,T);
   for(int k=1;k<=t;k++)for(int j=1;j<=t/k;j++){
      Mint add=fact.inv(j)*cnt[k];
      if(j&1)f[k*j]+=add; else f[k*j]-=add;
   } f=f.exp();
   for(int i=1;i<=t;i++)printf("%d ",f[i].val);
   printf("\n");
   return 0;
}