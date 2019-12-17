#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
T totient(T n){
  T res=n;
  for(T i=2;i*i<=n;i++){
    if(n%i==0){
      res=res/i*(i-1);
      for(;n%i==0;n/=i);
    }
  }
  if(n!=1) res=res/n*(n-1);
  return res;
}

template<typename T>
T mpow(T a,T n,T m,T &f){
  using ull = unsigned long long;
  if(a==1||n==0) return 1;
  ull v=1,x=a,z=m;
  f|=x>=z;
  x%=m;
  while(1){
    if(n&1) v*=x;
    if(v>=z) f=1,v%=m;
    n>>=1;
    if(!n) break;
    x=x*x;
    if(x>=z) f=1,x%=m;
  }
  return v;
}

template<typename T>
T tetration(T a,T n,T m,T &f){
  if(a==0) return ~n&1;
  if(m==1) return f=1;
  if(a==1||n==0) return 1;
  if(n==1){
    f|=a>=m;
    return a%m+f*m;
  }
  T z=tetration(a,n-1,totient(m),f);
  T r=mpow(a,z,m,f);
  return r+f*m;
}

// https://judge.yosupo.jp/problem/tetration_mod
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int numCases;
  cin >> numCases;
  for (int caseId = 0; caseId < numCases; ++caseId) {
    long long A, B, M, F;
    cin >> A >> B >> M;
    cout << tetration(A, B, M, F) % M << "\n";
  }
  return 0;
}
