#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
using namespace std;

//template
#define rrep(i,a,b) for(int i=(a);i>(b);i--)
#define ALL(v) (v).begin(),(v).end()
typedef long long int ll;
const int inf = 0x3fffffff; const ll INF = 0x1fffffffffffffff; const double eps=1e-12;
template<class T> inline bool chmax(T& a,T b){ if(a<b){a=b;return 1;}return 0; }
template<class T> inline bool chmin(T& a,T b){ if(a>b){a=b;return 1;}return 0; }
//end

struct BIT{
   int n; vector<int> val;
   BIT(int _n):n(_n),val(_n+1,0){}
   void add(int i,int x){for(i++;i<=n;i+=i&-i)val[i]+=x;}
   int sum(int i){int res=0; for(i++;i;i-=i&-i)res+=val[i]; return res;}
};

constexpr int R=1010101;
constexpr int C=10101;
bitset<R> isp; vector<int> ps,cs;

void init(int c){
   ps.clear(); cs.clear(); isp[0]=isp[1]=1;
   for(int p=2;p*p<=R;p++)if(!isp[p]){
      for(int q=p*p;q<=R;q+=p)isp[q]=1;
   }
   for(int i=2;i<R+1;++i)if(!isp[i]){
      ps.push_back(i);
      if(i<=c)cs.push_back(i);
   }
}

ll phi(ll x,ll a,ll cnt){
   ll res=0;
   vector<int> mu(a+1,1),minp(a+1,a);
   for(int i=1;i<a+1;++i){
      if(!isp[i]){
         for(ll j=i;j<=a;j+=i){mu[j]*=-1; chmin(minp[j],i);}
         for(ll j=i*i,k=j;k<=a;k+=j)mu[k]=0;
      } res+=mu[i]*(x/i);
   }
   vector<ll> sum(cnt,0);
   for(ll lo=1;lo<x/a;lo+=a){
      ll hi=min(lo+a,x/a);
      BIT bit(a); bitset<C> is_one;
      for(int b=0;b<cnt;++b){
         int p=cs[b],mi=max(x/p/hi,a/p),ma=min(x/p/lo,a);
         if(p<ma){
            rrep(m,ma,mi)if(mu[m]!=0 and minp[m]>p){
               res-=mu[m]*(sum[b]+x/p/m-lo+1-bit.sum(x/p/m-lo));
            }
         } sum[b]+=a-bit.sum(a-1);
         for(int q=(p-lo%p)%p;q<a;q+=p)if(!is_one[q]){
            bit.add(q,1); is_one[q]=1;
         }
      }
   } return res;
}

ll pi(ll x){
   int r=sqrt(x),c=cbrt(x); init(c);
   if(x<=R)return upper_bound(ALL(ps),x)-ps.begin();
   ll a=upper_bound(ALL(ps),c)-ps.begin(),b=upper_bound(ALL(ps),r)-ps.begin();
   ll res=phi(x,c,a)+(b+a-2)*(b-a+1)/2; int idx=b-1;
   for(int s=r;s<=x and idx>=a;s+=c){
     vector<ll> cur(c+1,0); bitset<C> val; cur[0]=b; for(int i=0;i<C;++i)val[i]=1;
      for(int p:cs)for(int q=(p-s%p)%p;q<=c;q+=p)val[q]=0;
      for(int i=1;i<c+1;++i) cur[i]=cur[i-1]+val[i];
      b=cur[c];
      while(s<=x/ps[idx] and x/ps[idx]<s+c and idx>=a){res-=cur[x/ps[idx]-s]; idx--;}
   } return res;
}

int main(){
   ll n; scanf("%lld",&n);
   printf("%lld\n",pi(n));
   return 0;
}
