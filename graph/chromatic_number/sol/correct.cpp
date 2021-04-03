#include <iostream>
using namespace std;

int es[20],dp[1<<20];

int main(){
   int n,m;
   scanf("%d%d",&n,&m);
   for (int _ = 0; _ < m; _++){
      int u,v;
      scanf("%d%d",&u,&v);
      es[u]|=1<<v;
      es[v]|=1<<u;
   }
   
   for (int i = 0; i < (1<<n); i++){
      dp[i]=1<<30;
   }
   dp[0]=1;
   for (int i = 0; i < n; i++){
      for (int mask = 0; mask < (1<<n); mask++){
         if(dp[mask]==1 and (mask&es[i])==0){
            dp[mask|(1<<i)]=1;
         }
      }
   }
   for (int mask = 0; mask < (1<<n); mask++){
      for (int sub = mask; --sub&=mask; ){
         dp[mask]=min(dp[mask],dp[mask^sub]+dp[sub]);
      }
   }
   printf("%d\n",dp[(1<<n)-1]);
   return 0;
}