#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <deque>
#include <cstring>
#include <time.h>
#include <cstdio>
#include <tuple>

constexpr long long     p=998244353;
constexpr long long  root=3;
constexpr long long iroot=332748118;
inline int ADD(const int a,const int b) {
  return a+b>=p?a+b-p:a+b;
}

inline int SUB(const int a,const int b) {
  return a-b<0?a-b+p:a-b;
}

void fail() {
  printf("-1\n");
  exit(0);
}

int deg(const std::vector<int> &a){
  int ret=a.size()-1;
  while (ret>=0 && a[ret]==0) --ret;
  return ret;
}

std::vector<int> trim(std::vector<int> a,const int n) {
  int asize=a.size();
  a.resize(n);
  for (int i=asize;i<n;++i) a[i]=0;
  return a;
}

void norm(std::vector<int> &a) {
  while (a.size()>1 && a.back()==0) a.pop_back();
}

//f->fx^(shift)
std::vector<int> shift(std::vector<int> &a,const int shift) {
  std::vector<int> b(std::max(0,(int)a.size()+shift),0);
  for (int i=0;i<(int)b.size();++i) b[i]=(0<=i-shift&&i-shift<(int)a.size())?a[i-shift]:0;
  return b;
}

inline long long pow_mod(long long a,long long n) {
  long long ret=1;
  for (;n>0;n>>=1,a=a*a%p) if(n%2==1) ret=ret*a%p;
  return ret;
}

inline int inv(int a) {
  a%=p;
  if (a<0) a+=p;
  int u=p;
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
  return s>=0?s:s+p;
}

void monic(std::vector<int> &a) {
  norm(a);
  long long coe=inv(a.back());
  for (int i=0;i<(int)a.size();++i) {
    a[i]=(int)(coe*a[i]%p);
  }
}

std::vector<int> add(std::vector<int> a,std::vector<int> b) {
  int n=std::max(a.size(),b.size());
  a.resize(n);b.resize(n);
  for (int i=0;i<n;++i) a[i]=ADD(a[i],b[i]);
  return a;
}

std::vector<int> subtract(std::vector<int> a,std::vector<int> b) {
  int n=std::max(a.size(),b.size());
  a.resize(n);b.resize(n);
  for (int i=0;i<n;++i) a[i]=ADD(a[i],p-b[i]);
  return a;
}

std::vector<int> mul_naive(std::vector<int> &a,std::vector<int> &b) {
  std::vector<int> ret(a.size()+b.size()-1,0);
  if (a.size()<b.size()) {
    for (int i=0;i<(int)a.size();++i) {
      for (int j=0;j<(int)b.size();++j) {
        ret[i+j]=(int)((ret[i+j]+1LL*a[i]*b[j])%p);
      }
    }
  }else {
    for (int j=0;j<(int)b.size();++j) {
      for (int i=0;i<(int)a.size();++i) {
        ret[i+j]=(int)((ret[i+j]+1LL*a[i]*b[j])%p);
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
    int w=pow_mod(g,(p-1)/n);
    int mul=1;
    for (int i=0;i<n/2;++i) {
      for (int src=0;src<stride;++src) {
        int A=from[src+stride*(i+  0)];
        int B=from[src+stride*(i+n/2)];
        to[src+stride*(2*i+0)]=ADD(A,B);
        to[src+stride*(2*i+1)]=1LL*SUB(A,B)*mul%p;
      }
      mul=1LL*mul*w%p;
    }
    fft_(n/2,g,2*stride,to,from,!flag);
  }
}

void fft4_(int n,int g,int j,int stride,std::vector<int> &from,std::vector<int> &to,bool flag){
  int w=pow_mod(g,(p-1)/n);
  long long w1,w2,w3;
  int i,src,n0,n1,n2,n3,A,B,C,D,apc,amc,bpd,jbmd;
  
  while (n>2) {
    n0=0;
    n1=n/4;
    n2=n1+n1;
    n3=n1+n2;
    w1=1;
    for (i=0;i<n1;++i) {
      w2=w1*w1%p;
      w3=w1*w2%p;
      for (src=0;src<stride;++src) {
        A=from[src+stride*(i+n0)];
        B=from[src+stride*(i+n1)];
        C=from[src+stride*(i+n2)];
        D=from[src+stride*(i+n3)];
        apc=ADD(A,C);
        amc=SUB(A,C);
        bpd=ADD(B,D);
        jbmd=1LL*j*SUB(B,D)%p;
        to[src+stride*(4*i+0)]=ADD(apc,bpd);
        to[src+stride*(4*i+1)]=w1*(amc+p-jbmd)%p;
        to[src+stride*(4*i+2)]=w2*(A+C+p-bpd)%p;
        to[src+stride*(4*i+3)]=w3*(A+p-C+jbmd)%p;
      }
      w1=1LL*w1*w%p;
    }
    n/=4;
    stride*=4;
    flag=!flag;
    w=1LL*w*w%p;
    w=1LL*w*w%p;
    std::swap(to,from);
  }
  if (n<=2) fft_(n,g,stride,from,to,flag);
  if (from.size()>to.size()) std::swap(from,to);
}

std::vector<int> tmp_fft(1<<20);
void fft(std::vector<int> &a,int g) {
  fft4_(a.size(),g,pow_mod(g,(p-1)/4*3),1,a,tmp_fft,false);
}

//  (sx^p+u)(tx^p+v)
// =stx^(2p)+(sv+ut)x^p+uv
// =stx^(2p)+((s+u)(t+v)-(st-uv))x^p+uv
void mul_karatsuba(int a[],int b[],int c[],int res[],int n) {
  if (n<=8) {
    for (int i=0;i<2*n;++i) res[i]=0;
    for (int i=0;i<n;++i) for(int j=0;j<n;++j) res[i+j]=ADD(res[i+j],(int)(1LL*a[i]*b[j]%p));
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
  for (int i=0;i<n;++i) a[i]=(int)(1LL*a[i]*b[i]%p*inv_n%p);
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

std::vector<int> mul(std::vector<int> &a,int b) {
  int n=a.size();
  std::vector<int> c(n);
  for (int i=0;i<n;++i) c[i]=(int)(1LL*a[i]*(p+b)%p);
  return c;
}

std::vector<std::vector<std::vector<int>>> mul(std::vector<std::vector<std::vector<int>>> &a,std::vector<std::vector<std::vector<int>>> &b) {
  std::vector<std::vector<std::vector<int>>> ret(a.size(),std::vector<std::vector<int>>(b[0].size(),std::vector<int>()));
  
  for (int i=0;i<(int)a.size();++i) {
    for (int j=0;j<(int)b[i].size();++j) {
      for (int k=0;k<(int)a[i].size();++k) {
        std::vector<int> prd=mul(a[i][k],b[k][j]);
        if (ret[i][j].size()<prd.size()) ret[i][j].resize(prd.size());
        for (int l=0;l<(int)prd.size();++l) {
          ret[i][j][l]=ADD(ret[i][j][l],prd[l]);
        }
      }
    }
  }
  return ret;
}

// f  <- -f(fg-1)+f
std::vector<int> inv(std::vector<int> &g) {
  int n=g.size();
  std::vector<int> f={inv(g[0])};
  long long root=3;
  long long iroot=inv(3);
  for (int len=1;len<n;len*=2) {
    std::vector<int> f_fft=trim(f,2*len);
    std::vector<int> g_fft=trim(g,2*len);
    fft(f_fft,root);
    fft(g_fft,root);
    long long isize=inv(2*len);
    for (int i=0;i<2*len;++i) g_fft[i]=(int)(1LL*g_fft[i]*f_fft[i]%p*isize%p);
    fft(g_fft,iroot);
    for (int i=0;i<len;++i) g_fft[i]=0;
    fft(g_fft,root);
    for (int i=0;i<2*len;++i) g_fft[i]=(int)(1LL*g_fft[i]*f_fft[i]%p*isize%p);
    fft(g_fft,iroot);
    for (int i=0;i<len;++i) g_fft[i]=0;
    f.resize(std::min(n,2*len));
    for (int i=0;i<2*len;++i) {
      f[i]=ADD(f[i],p-g_fft[i]);
    }
  }
  return f;
}

std::vector<int> divide_naive(std::vector<int> a,std::vector<int> &b) {
  if (a.size()<b.size()) return {0};
  int n=a.size()-b.size()+1;
  std::vector<int> ret(n,0);
  norm(b);
  assert(deg(b)>=0);
  int ib=inv(b.back());
  for (int i=n-1;i>=0;--i) {
    if (a[i+b.size()-1]==0) continue;
    ret[i]=1LL*ib*a[i+b.size()-1]%p;
    for (int j=0;j<(int)b.size();++j) {
      a[i+j]=(a[i+j]+1LL*b[j]*(p-ret[i]))%p;
    }
  }
  return ret;
}

std::vector<int> divide_newton(std::vector<int> a,std::vector<int> b) {  
  if (a.size()<b.size()) return {0};
  std::reverse(a.begin(),a.end());
  std::reverse(b.begin(),b.end());
  int n=a.size()-b.size()+1;
  a.resize(n);
  b.resize(n);
  b=inv(b);
  a=mul(a,b);
  a.resize(n);
  std::reverse(a.begin(),a.end());
  return a;
}

std::vector<int> divide(std::vector<int> &a,std::vector<int> &b) {
  norm(a);
  norm(b);
  if (a.size()<b.size()) {
    std::vector<int> ret(1,0);
    return ret;
  }
  
  if (a.size()==b.size()) {
    return {(int)(1LL*inv(b.back())*a.back()%p)};
  } else if (a.size()-b.size()<b.size()-1 && a.size()>=32) {
    int del=a.size()-2*(a.size()-b.size())-1;
    std::vector<int> na=shift(a,-del);
    std::vector<int> nb=shift(b,-del);
    return divide(na,nb);
  } else if (a.size()<32) {
    return divide_naive(a,b);
  } else {
    return divide_newton(a,b);
  }
}

std::vector<int> mod(std::vector<int> &a,std::vector<int> &b) {
  std::vector<int> q=divide(a,b);
  q=subtract(a,mul(b,q));
  norm(q);
  return q;
}

// deg(a)>=deg(b)を仮定
std::vector<int> gcd_naive(std::vector<int> &a,std::vector<int> &b) {
  while (deg(b)!=-1) {
    norm(a);norm(b);
    if (deg(a)<deg(b)) {
      std::swap(a,b);
      continue;
    }
    int n=a.size()-b.size()+1;
    std::vector<int> c(n,0);
    int ib=inv(b.back());
    for (int i=n-1;i>=0;--i) {
      if (a[i+b.size()-1]==0) continue;
      c[i]=1LL*(p-ib)*a[i+b.size()-1]%p;
      for (int j=0;j<(int)b.size();++j) {
        a[i+j]=(a[i+j]+1LL*b[j]*c[i])%p;
      }
    }
    std::swap(a,b);
  }
  return a;
}

std::vector<std::vector<std::vector<int>>> hgcd_naive(std::vector<int> a,std::vector<int> b) {
  norm(a);norm(b);
  assert(a.size()>=b.size());
  int lim=a.size()/2;
  std::vector<std::vector<std::vector<int>>> ans={{{1},{0}},{{0},{1}}};
  while (deg(b)!=-1&&(int)b.size()>lim) {
    assert(a.size()>=b.size());
    int n=a.size()-b.size()+1;
    std::vector<int> c(n,0);
    int ib=inv(b.back());
    for (int i=n-1;i>=0;--i) {
      if (a[i+b.size()-1]==0) continue;
      c[i]=1LL*(p-ib)*a[i+b.size()-1]%p;
      for (int j=0;j<(int)b.size();++j) {
        a[i+j]=(a[i+j]+1LL*b[j]*c[i])%p;
      }
    }
    ans[0][0]=add(ans[0][0],mul(ans[1][0],c));
    ans[0][1]=add(ans[0][1],mul(ans[1][1],c));
    std::swap(ans[0][0],ans[1][0]);
    std::swap(ans[0][1],ans[1][1]);
    norm(a);
    std::swap(a,b);
  }
  return ans;
}

// max(deg(a'),deg(b')) が 0.5*deg(a) より小さくなるところまで進める。
// deg(a) >= deg(b) を仮定。

std::vector<std::vector<std::vector<int>>> hgcd(std::vector<int> a,std::vector<int> b) {
  norm(a);norm(b);
  assert(a.size()>=b.size());
  if (deg(a)<=1024) return hgcd_naive(a,b);
  if ((deg(a)+1)-(deg(b)+1)>(deg(b)+1)) {
    return {{{1},{0}},{{0},{1}}};
  } else {
    std::vector<std::vector<std::vector<int>>> R={{{1},{0}},{{0},{1}}};
    std::vector<std::vector<std::vector<int>>> v={{a},{b}};
    int m=(deg(a)+1)/2;
    if (m>0) {// 行列とベクトルの積6400ms(n=1e5)
      R=hgcd(shift(a,-m),shift(b,-m));
      if (R[0][0].size()<=128&&v[0][0].size()<=128) {
        v=mul(R,v);
      } else {
        int need=0;
        int n=1;;
        for (int i=0;i<2;++i) {
          for (int j=0;j<2;++j) {
            need=std::max(need,(int)(R[i][j].size()+v[j][0].size()-1));
          }
        }
        while (n<need) n*=2;
        int in=inv(n);
        std::vector<std::vector<std::vector<int>>> R_fft={{{},{}},{{},{}}};
        std::vector<std::vector<std::vector<int>>> v_fft={{{}},{{}}};   
        for (int i=0;i<2;++i) {
          v_fft[i][0]=trim(v[i][0],n);
          fft(v_fft[i][0],root);
          for (int j=0;j<2;++j) {
            R_fft[i][j]=trim(R[i][j],n);
            fft(R_fft[i][j],root);
          }
        }
        v[0][0].resize(n);
        v[1][0].resize(n);
        for (int i=0;i<n;++i) {
          v[0][0][i]=(1LL*R_fft[0][0][i]*v_fft[0][0][i]+1LL*R_fft[0][1][i]*v_fft[1][0][i])%p*in%p;
          v[1][0][i]=(1LL*R_fft[1][0][i]*v_fft[0][0][i]+1LL*R_fft[1][1][i]*v_fft[1][0][i])%p*in%p;
        }
        for (int i=0;i<2;++i) {
          fft(v[i][0],iroot);
          norm(v[i][0]);
        }
      }
      if (deg(v[1][0])==-1) return R;
    }
    if (deg(v[1][0])>=1.5*m) { // このブロックの演算が950ms(n=1e5)
      
      std::vector<int> q=divide(v[0][0],v[1][0]); // 高確率でdeg(q)==1。その場合deg(v[0][0])=4,deg(v[1][1])=2にO(1)で帰着できる。
      
      { // このブロックの演算600ms
        v[0][0]=subtract(v[0][0],mul(q,v[1][0]));
        R[0][0]=subtract(R[0][0],mul(q,R[1][0]));
        R[0][1]=subtract(R[0][1],mul(q,R[1][1]));
        std::swap(v[0][0],v[1][0]);
        std::swap(R[0][0],R[1][0]);
        std::swap(R[0][1],R[1][1]);
      }
      
      
      if (deg(v[1][0])==-1) return R;
    }
    if (m/2>0) {
      std::vector<std::vector<std::vector<int>>> S=hgcd(shift(v[0][0],-m/2),shift(v[1][0],-m/2));
      R=mul(S,R); // 行列積6500ms(n=1e5)
    }
    return R;
  }
}

std::vector<int> gcd(std::vector<int> &a,std::vector<int> &b) {
  norm(a);norm(b);
  if (deg(a)>deg(b)) return gcd(b,a);
  if (deg(a)==-1) return b;
  if (deg(b)<=2048) return gcd_naive(a,b);
  std::vector<std::vector<std::vector<int>>> R=hgcd(b,a);
  std::vector<std::vector<std::vector<int>>> v={{b},{a}};
  
  //a,bの更新1100ms(n=1e5)
  if (R[0][0].size()<=128&&v[0][0].size()<=128) {
    v=mul(R,v);
  } else {
    int need=0;
    int n=1;;
    for (int i=0;i<2;++i) {
      for (int j=0;j<2;++j) {
        need=std::max(need,(int)(R[i][j].size()+v[j][0].size()-1));
      }
    }
    while (n<need) n*=2;
    int in=inv(n);
    std::vector<std::vector<std::vector<int>>> R_fft={{{},{}},{{},{}}};
    std::vector<std::vector<std::vector<int>>> v_fft={{{}},{{}}};   
    for (int i=0;i<2;++i) {
      v_fft[i][0]=trim(v[i][0],n);
      fft(v_fft[i][0],root);
      for (int j=0;j<2;++j) {
        R_fft[i][j]=trim(R[i][j],n);
        fft(R_fft[i][j],root);
      }
    }
    v[0][0].resize(n);
    v[1][0].resize(n);
    for (int i=0;i<n;++i) {
      v[0][0][i]=(1LL*R_fft[0][0][i]*v_fft[0][0][i]+1LL*R_fft[0][1][i]*v_fft[1][0][i])%p*in%p;
      v[1][0][i]=(1LL*R_fft[1][0][i]*v_fft[0][0][i]+1LL*R_fft[1][1][i]*v_fft[1][0][i])%p*in%p;
    }
    for (int i=0;i<2;++i) {
      fft(v[i][0],iroot);
      norm(v[i][0]);
    }
  }
  norm(v[0][0]);
  norm(v[1][0]);
  // 条件 deg(v[0][0])-deg(v[1][0])>deg(v[1][0]) の成立は稀
  if (deg(v[1][0])!=-1 && (std::max(deg(v[0][0]),deg(v[1][0]))<5 || deg(v[0][0])-deg(v[1][0])>deg(v[1][0]))) {
    v[0][0]=mod(v[0][0],v[1][0]);
    std::swap(v[0][0],v[1][0]);
  }
  return gcd(v[1][0],v[0][0]);
}

std::vector<std::vector<std::vector<int>>> inv_naive(std::vector<int> &a,std::vector<int> &m) {
  norm(a);norm(m);
  if (deg(a)>=deg(m)) a=mod(a,m);
  std::vector<std::vector<std::vector<int>>> R={{{1},{0}},{{0},{1}}};
  while (deg(a)!=-1) {
    norm(a);norm(m);
    int n=m.size()-a.size()+1;
    std::vector<int> q(n,0);
    int ia=inv(a.back());
    for (int i=n-1;i>=0;--i) {
      if (m[i+a.size()-1]==0) continue;
      q[i]=1LL*ia*m[i+a.size()-1]%p;
      for (int j=0;j<(int)a.size();++j) {
        m[i+j]=(m[i+j]+1LL*a[j]*(p-q[i]))%p;
      }
    }
    {
      R[0][0]=subtract(R[0][0],mul(q,R[1][0]));
      R[0][1]=subtract(R[0][1],mul(q,R[1][1]));
      std::swap(R[0][0],R[1][0]);
      std::swap(R[0][1],R[1][1]);
      std::swap(a,m);
    }
  }
  if (deg(m)!=0) fail();
  {
    int normalizer=inv(m[0]);
    for (int i=0;i<2;++i)
      for (int j=0;j<2;++j)
        for (int k=0;k<(int)R[i][j].size();++k)
          R[i][j][k]=1LL*R[i][j][k]*normalizer%p;
  }
  return R;
}

// a*x = 1 (mod m) なる x を返す。
std::vector<std::vector<std::vector<int>>> inv(std::vector<int> &a,std::vector<int> &m) {
  norm(a);norm(m);
  if (deg(a)>deg(m)) a=mod(a,m);
  if (deg(a)==-1) {
    if (deg(m)!=0) fail();
    int normalizer=inv(m[0]);
    return {{{normalizer},{0}},{{0},{normalizer}}};
  }
  if (deg(m)<=256) return inv_naive(a,m);
  std::vector<std::vector<std::vector<int>>> R=hgcd(m,a);
  std::vector<std::vector<std::vector<int>>> v={{m},{a}};
  
  //a,bの更新1100ms(n=1e5)
  if (R[0][0].size()<=128&&v[0][0].size()<=128) {
    v=mul(R,v);
  } else {
    int need=0;
    int n=1;
    for (int i=0;i<2;++i) {
      for (int j=0;j<2;++j) {
        need=std::max(need,(int)(R[i][j].size()+v[j][0].size()-1));
      }
    }
    while (n<need) n*=2;
    int in=inv(n);
    std::vector<std::vector<std::vector<int>>> R_fft={{{},{}},{{},{}}};
    std::vector<std::vector<std::vector<int>>> v_fft={{{}},{{}}};   
    for (int i=0;i<2;++i) {
      v_fft[i][0]=trim(v[i][0],n);
      fft(v_fft[i][0],root);
      for (int j=0;j<2;++j) {
        R_fft[i][j]=trim(R[i][j],n);
        fft(R_fft[i][j],root);
      }
    }
    v[0][0].resize(n);
    v[1][0].resize(n);
    for (int i=0;i<n;++i) {
      v[0][0][i]=(1LL*R_fft[0][0][i]*v_fft[0][0][i]+1LL*R_fft[0][1][i]*v_fft[1][0][i])%p*in%p;
      v[1][0][i]=(1LL*R_fft[1][0][i]*v_fft[0][0][i]+1LL*R_fft[1][1][i]*v_fft[1][0][i])%p*in%p;
    }
    for (int i=0;i<2;++i) {
      fft(v[i][0],iroot);
      norm(v[i][0]);
    }
  }
  norm(v[0][0]);
  norm(v[1][0]);
  // 条件 deg(v[0][0])-deg(v[1][0])>deg(v[1][0]) の成立は稀
  if (deg(v[1][0])!=-1 && (std::max(deg(v[0][0]),deg(v[1][0]))<5 || deg(v[0][0])-deg(v[1][0])>deg(v[1][0]))) {
    std::vector<int> q=divide(v[0][0],v[1][0]);
    v[0][0]=subtract(v[0][0],mul(q,v[1][0]));
    R[0][0]=subtract(R[0][0],mul(q,R[1][0]));
    R[0][1]=subtract(R[0][1],mul(q,R[1][1]));
    std::swap(v[0][0],v[1][0]);
    std::swap(R[0][0],R[1][0]);
    std::swap(R[0][1],R[1][1]);
  }
  std::vector<std::vector<std::vector<int>>> nextR=inv(v[1][0],v[0][0]);
  return mul(nextR,R);
}


void verify() {
  std::random_device seed_gen;
  std::mt19937_64 engine(seed_gen());
  for (int t=0;t<10000;++t) {
    
    int n=(int)2;
    std::vector<int> a(n,0);
    std::vector<int> b(n,0);
    for (int i=0;i<n;++i) a[i]=1LL*(p+engine())%p;
    for (int i=0;i<n;++i) b[i]=1LL*(p+engine())%p;
    norm(a);norm(b);
    std::vector<int> a_=trim(a,a.size());
    std::vector<int> b_=trim(b,b.size());
    if (deg(b)==-1) continue;
    a=mod(a,b);
    if (deg(a)==-1) continue;
    // for (int i=0;i<n;++i) {
    //   std::cout << i << " a:" << a[i] << " b:" << b[i] << std::endl;
    // }
    
    clock_t start = clock();
    std::vector<int> v=mul(inv(a,b)[0][1],a_);
    v=mod(v,b_);
    assert(deg(v)==0);
    assert(v[0]==1);
    clock_t end = clock();
    const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("%lf[ms]\n", time);
  }
}

void solve() {
  int n,m;
  scanf("%d %d",&n,&m);
  std::vector<int> a(n);
  std::vector<int> b(m);
  for (int i=0;i<n;++i) {
    scanf("%d",&a[i]);
  }
  for (int i=0;i<m;++i) {
    scanf("%d",&b[i]);
  }
  
  std::vector<int> c=inv(a,b)[0][1];
  norm(c);
  assert(deg(c)+1<m);
  if (c.back()==0) c.pop_back();
  printf("%d\n",(int)c.size());
  for (int i=0;i<(int)c.size();++i) {
    printf("%d",c[i]);
    if (i==(int)c.size()-1) printf("\n");
    else printf(" ");
  }
}

int main() {
  //verify();
  solve();
}
