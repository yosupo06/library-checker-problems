#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <deque>
#include <cstring>
#include <time.h>
#include <tuple>
#include "random.h"
#include "../params.h"

constexpr int root=3;
constexpr int iroot=332748118;

inline int ADD(const int a,const int b) {
  return a+b>=MOD?a+b-MOD:a+b;
}

inline int SUB(const int a,const int b) {
  return a-b<0?a-b+MOD:a-b;
}

void norm(std::vector<int> &a) {
  while (a.size()>1 && a.back()==0) a.pop_back();
}

inline long long pow_mod(long long a,long long n) {
  long long ret=1;
  for (;n>0;n>>=1,a=a*a%MOD) if(n%2==1) ret=ret*a%MOD;
  return ret;
}

inline int inv(int a) {
  a%=MOD;
  if (a<0) a+=MOD;
  int u=MOD;
  int v=a;
  int s=0;
  int t=1;
  // sa=u
  // ta=v
  while (v!=0) {
    int q=u/v;
    s-=q*t;u-=q*v;
    std::swap(s,t);
    std::swap(u,v);
  }
  return s>=0?s:s+MOD;
}

std::vector<int> add(std::vector<int> a,std::vector<int> b) {
  int n=std::max(a.size(),b.size());
  a.resize(n);b.resize(n);
  for (int i=0;i<n;++i) a[i]=ADD(a[i],b[i]);
  return a;
}

std::vector<int> trim(std::vector<int> a,const int n) {
  int asize=a.size();
  a.resize(n);
  for (int i=asize;i<n;++i) a[i]=0;
  return a;
}

std::vector<int> mul_naive(std::vector<int> &a,std::vector<int> &b) {
  std::vector<int> ret(a.size()+b.size()-1,0);
  if (a.size()<b.size()) {
    for (int i=0;i<(int)a.size();++i) {
      for (int j=0;j<(int)b.size();++j) {
        ret[i+j]=(int)((ret[i+j]+1LL*a[i]*b[j])%MOD);
      }
    }
  }else {
    for (int j=0;j<(int)b.size();++j) {
      for (int i=0;i<(int)a.size();++i) {
        ret[i+j]=(int)((ret[i+j]+1LL*a[i]*b[j])%MOD);
      }
    }
  }
  norm(ret);
  return ret;
}

void fft_(int n,int g,int stride,std::vector<int> &from,std::vector<int> &to,bool flag){
  if (n==1) {
    if (flag) for (int i=0;i<stride;++i) to[i]=from[i];
    return;
  } else {
    int w=pow_mod(g,(MOD-1)/n);
    int mul=1;
    for (int i=0;i<n/2;++i) {
      for (int src=0;src<stride;++src) {
        int A=from[src+stride*(i+  0)];
        int B=from[src+stride*(i+n/2)];
        to[src+stride*(2*i+0)]=ADD(A,B);
        to[src+stride*(2*i+1)]=1LL*SUB(A,B)*mul%MOD;
      }
      mul=1LL*mul*w%MOD;
    }
    fft_(n/2,g,2*stride,to,from,!flag);
  }
}

void fft4_(int n,int g,int j,int stride,std::vector<int> &from,std::vector<int> &to,bool flag){
  int w=pow_mod(g,(MOD-1)/n);
  long long w1,w2,w3;
  int i,src,n0,n1,n2,n3,A,B,C,D,apc,amc,bpd,jbmd;
  
  while (n>2) {
    n0=0;
    n1=n/4;
    n2=n1+n1;
    n3=n1+n2;
    w1=1;
    for (i=0;i<n1;++i) {
      w2=w1*w1%MOD;
      w3=w1*w2%MOD;
      for (src=0;src<stride;++src) {
        A=from[src+stride*(i+n0)];
        B=from[src+stride*(i+n1)];
        C=from[src+stride*(i+n2)];
        D=from[src+stride*(i+n3)];
        apc=ADD(A,C);
        amc=SUB(A,C);
        bpd=ADD(B,D);
        jbmd=1LL*j*SUB(B,D)%MOD;
        to[src+stride*(4*i+0)]=ADD(apc,bpd);
        to[src+stride*(4*i+1)]=w1*(amc+MOD-jbmd)%MOD;
        to[src+stride*(4*i+2)]=w2*(A+C+MOD-bpd)%MOD;
        to[src+stride*(4*i+3)]=w3*(A+MOD-C+jbmd)%MOD;
      }
      w1=1LL*w1*w%MOD;
    }
    n/=4;
    stride*=4;
    flag=!flag;
    w=1LL*w*w%MOD;
    w=1LL*w*w%MOD;
    std::swap(to,from);
  }
  if (n<=2) fft_(n,g,stride,from,to,flag);
  if (from.size()>to.size()) std::swap(from,to);
}

std::vector<int> tmp_fft(1<<20);
void fft(std::vector<int> &a,int g) {
  fft4_(a.size(),g,pow_mod(g,(MOD-1)/4*3),1,a,tmp_fft,false);
}

//  (sx^p+u)(tx^p+v)
// =stx^(2p)+(sv+ut)x^p+uv
// =stx^(2p)+((s+u)(t+v)-(st-uv))x^p+uv
void mul_karatsuba(int a[],int b[],int c[],int res[],int n) {
  if (n<=8) {
    for (int i=0;i<2*n;++i) res[i]=0;
    for (int i=0;i<n;++i) for(int j=0;j<n;++j) res[i+j]=ADD(res[i+j],(int)(1LL*a[i]*b[j]%MOD));
    return;
  }
  int *x0=res;
  int *x1=res+n;
  int *x2=res+n*2;
  int *a0=a;
  int *a1=a+n/2;
  int *b0=b;
  int *b1=b+n/2;
  int *c0=c;
  int *c1=c+n/2;
  mul_karatsuba(a0,b0,c+n*2,x0,n/2);
  mul_karatsuba(a1,b1,c+n*2,x1,n/2);
  for (int i=0;i<n/2;++i) {
    c0[i]=ADD(a0[i],a1[i]);
    c1[i]=ADD(b0[i],b1[i]);
  }
  mul_karatsuba(c0,c1,c+n*2,x2,n/2);
  for (int i=0;i<n;++i) {
    x2[i]=SUB(SUB(x2[i],x0[i]),x1[i]);
  }
  for (int i=0;i<n;++i) {
    res[i+n/2]=ADD(res[i+n/2],x2[i]);
  }
}

std::vector<int> mul_fft(std::vector<int> a,std::vector<int> b) {
  int n=1;
  int need=a.size()+b.size()-1;
  while (n<need) n*=2;
  a.resize(n);
  b.resize(n);
  fft(a,root);
  fft(b,root);
  int inv_n=inv(n);
  for (int i=0;i<n;++i) a[i]=(int)(1LL*a[i]*b[i]%MOD*inv_n%MOD);
  fft(a,iroot);
  a.resize(need);
  return a;
}

std::vector<int> karatsuba(std::vector<int> &a,std::vector<int> &b) {
  int need=std::max(a.size(),b.size());
  int n=1;
  while (n<need) n*=2;
  std::vector<int> a_=trim(a,n);
  std::vector<int> b_=trim(b,n);
  std::vector<int> c(4*n);
  std::vector<int> res(4*n);
  mul_karatsuba(a_.data(),b_.data(),c.data(),res.data(),n);
  res.resize(a.size()+b.size()-1);
  return res;
}

std::vector<int> mul(std::vector<int> &a,std::vector<int> &b) {
  if (std::min(a.size(),b.size())<=2) {
    return mul_naive(a,b);
  }else if (std::max(a.size(),b.size())<=64) {
    return karatsuba(a,b);
  } else {
    std::vector<int> ret=mul_fft(a,b);
    norm(ret);
    return ret;
  } 
}












int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    
    std::vector<int> a(N_MAX,0),b(N_MAX,0);
    a[0]=1;
    
    int sz=1;
    while (2*sz<=N_MAX) {
      std::vector<int> multiplier(sz+1);
      for (int i=0;i<(int)multiplier.size();++i) multiplier[i]=gen.uniform(1, int(MOD - 1));
      multiplier=mul(a,multiplier);
      b=add(b,multiplier);
      std::swap(a,b);
      sz*=2;
    }
    
    while (a.back()==0) a.pop_back();
    while (b.back()==0) b.pop_back();
    int n=a.size();
    int m=b.size();

    assert(n>0 && m>0);
    
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
      printf("%d", a[i]);
      if (i != n - 1) printf(" ");
    }
    printf("\n");
    
    for (int i = 0; i < m; i++) {
      printf("%d", b[i]);
      if (i != m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
