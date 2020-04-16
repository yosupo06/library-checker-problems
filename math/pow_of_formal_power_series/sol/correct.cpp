#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>

constexpr long long p=998244353;

long long ADD(long long a,long long b) {
  return a+b>=p?a+b-p:a+b;
}

std::vector<long long> trim(std::vector<long long> a,int n) {
  std::vector<long long> b(n,0);
  for (int i=0;i<std::min(n,(int)a.size());++i) b[i]=a[i];
  return b;
}

std::vector<long long> shift(std::vector<long long> a,int shift) {
  std::vector<long long> b(a.size(),0);
  for (int i=0;i<(int)a.size();++i) b[i]=(0<=i-shift&&i-shift<(int)a.size())?a[i-shift]:0;
  return b;
}

long long pow_mod(long long a,long long n) {
  return n==0?1:(pow_mod(a*a%p,n/2)*(n%2==1?a:1))%p;
}

long long inv(long long a) {
  return pow_mod(a,p-2);
}

std::vector<long long> add(std::vector<long long> a,std::vector<long long> b) {
  int n=std::max(a.size(),b.size());
  std::vector<long long> c(n);
  a.resize(n);b.resize(n);
  for (int i=0;i<n;++i) c[i]=ADD(a[i],b[i]);
  return c;
}

std::vector<long long> subtract(std::vector<long long> a,std::vector<long long> b) {
  int n=std::max(a.size(),b.size());
  std::vector<long long> c(n);
  a.resize(n);b.resize(n);
  for (int i=0;i<n;++i) c[i]=ADD(a[i],p-b[i]);
  return c;
}

void fft(std::vector<long long> &a,long long g) {
  int n=a.size();
  g=pow_mod(g,(p-1)/n);
  {
    int i=0;
    for (int j=0;j<n;++j) {
      if (i>j) std::swap(a[i],a[j]);
      for (int k=n/2;k>(i^=k);k/=2) ;
    }
  }
  for (int len=1;len<=n/2;len*=2) {
    long mul=pow_mod(g,n/(2*len));
    for (int src=0;src<n;src+=2*len) {
      long long x=1;
      for (int pos=src;pos<src+len;++pos) {
        long long A=a[pos];
        long long B=a[pos+len]*x%p;
        a[pos]=ADD(A,B);
        a[pos+len]=ADD(A,p-B);
        x=x*mul%p;
      }
    }
  }
}

std::vector<long long> mul(std::vector<long long> a,std::vector<long long> b) {
  long long g=3;
  int n=1;
  while (n<(int)(a.size()+b.size()-1)) n*=2;
  a.resize(n);
  b.resize(n);
  fft(a,g);
  fft(b,g);
  long long inv_n=inv(n);
  for (int i=0;i<n;++i) a[i]=a[i]*b[i]%p*inv_n%p;
  fft(a,inv(g));
  return a;
}

std::vector<long long> mul(std::vector<long long> a,long long b) {
  int n=a.size();
  std::vector<long long> c(n);
  for (int i=0;i<n;++i) c[i]=a[i]*b%p;
  return c;
}

std::vector<long long> inv(std::vector<long long> a) {
  int n=a.size();
  std::vector<long long> b={inv(a[0])};
  for (int len=1;len<n;len*=2) {
    b=subtract(mul(b,2),trim(mul(mul(b,b),trim(a,2*len)),2*len));
  }
  return b;
}

std::vector<long long> differentiate(std::vector<long long> a) {
  int n=a.size();
  std::vector<long long> b(n,0);
  for (int i=0;i+1<n;++i) b[i]=(i+1)*a[i+1]%p;
  return b;
}

std::vector<long long> integrate(std::vector<long long> a) {
  int n=a.size();
  std::vector<long long> b(n,0);
  for (int i=1;i<n;++i) b[i]=inv(i)*a[i-1]%p;
  return b;
}

std::vector<long long> log(std::vector<long long> a) {
  assert(a[0]==1);
  return integrate(mul(differentiate(a),inv(a)));
}

std::vector<long long> exp(std::vector<long long> a) {
  assert(a[0]==0);
  int n=a.size();
  std::vector<long long> b={1};
  for (int len=1;len<n;len*=2) {
    std::vector<long long> tmp=subtract(trim(a,2*len),log(trim(b,2*len)));
    ++tmp[0];
    b=trim(mul(b,tmp),2*len);
  }
  return b;
}

std::vector<long long> pow(std::vector<long long> a,int n) {
  assert(n>=1);
  int s=0;
  while (s<(int)a.size() && a[s]==0) ++s;
  if (s==(int)a.size()) return a;
  a=shift(a,-s);
  long long b=inv(a[0]);
  for (int i=0;i<(int)a.size();++i) a[i]=b*a[i]%p;
  a=log(a);
  for (int i=0;i<(int)a.size();++i) a[i]=n*a[i]%p;
  a=exp(a);
  b=pow_mod(inv(b),n);
  for (int i=0;i<(int)a.size();++i) a[i]=b*a[i]%p;
  a=shift(a,s*n);
  return a;
}

std::vector<long long> pow_exact(std::vector<long long> a,int n) {
  std::vector<long long> b={1};
  for (int i=0;i<n;++i) b=trim(mul(b,a),a.size());
  return b;
}

void verify() {
  std::random_device seed_gen;
  std::mt19937_64 engine(seed_gen());
  for (int t=0;t<100000;++t) {
    int n=engine()%100+1;
    int k=engine()%100+1;;
    std::vector<long long> a(n);
    for (int i=0;i<n;++i) a[i]=engine()%p;
    std::vector<long long> u=pow(a,k);
    std::vector<long long> v=pow_exact(a,k);
    for (int i=0;i<n;++i) {
      assert(u[i]==v[i]);
    }
    std::cout << "case" << t << ":passed" << std::endl;
  }
}

int main() {
  int n,m;
  std::cin >> n >> m;
  std::vector<long long> a(n);
  for (int i=0;i<n;++i) scanf("%lld",&a[i]);
  a=pow(a,m);
  for (int i=0;i<n;++i) {
    printf("%lld",a[i]);
    if (i==n-1) printf("\n"); else printf(" ");
  }
}
