#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// number of permutations with p_i != i
template<typename T>
struct Montmort{
  using ll = long long;
  vector<T> dp;

  Montmort(int n,int mod):dp(n+1,0){
    for(int k=2;k<=n;k++){
      dp[k]=(ll)dp[k-1]*k%mod;
      if(~k&1) dp[k]+=1;
      else dp[k]+=mod-1;
      if(dp[k]>=mod) dp[k]-=mod;
    }
  }

  T operator[](int n){return dp[n];}
};

// https://judge.yosupo.jp/problem/montmort_number_mod
int main() {

  int N, M;
  cin >> N >> M;

  Montmort<int> mm(N, M);
  for(int i=1;i<=N;i++){
    if(i) cout << " ";
    cout << mm[i];
  }
  printf("\n");
  return 0;
}
