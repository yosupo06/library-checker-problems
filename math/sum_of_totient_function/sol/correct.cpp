
// Φ(n):=Sum[i=1..n]φ(i)

#include <iostream>
#include <cassert>
#include <cmath>
#include <map>


long long m=998244353; // mod m
long long N=(long long)1e10;
const int L1=(int)1e6;
const int L2=(int)1e4+1;

long long Phi1[L1]; //  Phi1[n] = Φ(n) 
long long Phi2[L2]; //  Phi2[n] = Φ([N/n])

long long pow(long long a,long long n){
  long long r=1;
  for(;n>0;n>>=1,a=a*a%m)if(n%2==1)r=r*a%m;
  return r;
}

long long inv(long long a){
  return pow(a,m-2);
}

long long gcd(long long a,long long b){
  return a==0?b:gcd(b%a,a);
}

long long phi(long long a) {
  int r=0;
  for(int i=1;i<=a;++i)if(gcd(i,a)==1)++r;
  return r;
}

long long Phi(long long a){
  return a<L1?Phi1[(int)a]:Phi2[(int)(N/a)];
}


void build(){
  for(int i=0;i<L1;++i)Phi1[i]=i;
  for(int i=1;i<L2;++i)Phi2[i]=(N/i)%m*((N/i)%m+1)%m*inv(2)%m;
  for(int i=2;i<L1;++i)if(Phi1[i]==i)for(int j=i;j<L1;j+=i)Phi1[j]-=Phi1[j]/i;
  for(int i=1;i<L1;++i)Phi1[i]=(Phi1[i]+Phi1[i-1])%m;
  for(int i=L2-1;i>=1;--i){
    int n=2;
    long long cur=N/i;
    for(;cur/n!=cur/(n+1)&&n<=cur;++n){
      Phi2[i]=Phi2[i]-((long long)i*n>=L2?Phi1[(int)(cur/n)]:Phi2[i*n]);
      while(Phi2[i]<0)Phi2[i]+=m;
    }
    for(int arg=(int)(cur/n);arg>=1;--arg){
      assert(cur/arg!=cur/(arg+1));
      Phi2[i]=Phi2[i]-(cur/arg-cur/(arg+1))%m*(arg<L1?Phi1[arg]:Phi2[(int)(N/arg)])%m;
      while(Phi2[i]<0)Phi2[i]+=m;
    }
  }
}



int main() {
  scanf("%lld",&N);
  build();
  printf("%lld\n", Phi2[1]);
}
