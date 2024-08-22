#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int main(void){
    long long mod = 998244353ll;
    int n;
    scanf("%d", &n);
    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        scanf("%lld", &a[i]);
    }
    map<long long, int> mp;
    vector<long long> dp(n + 1);
    vector<long long> sumdp(n + 1);
    for(int i = 0; i < n + 1; i++){
        dp[i] = 0;
        sumdp[i] = 0;
    }
    dp[0] = 1;
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        sumdp[i] += sumdp[i - 1] + dp[i - 1];
        sumdp[i] %= mod; 
        if(mp.find(a[i - 1]) == mp.end()){
            dp[i] = sumdp[i];
        }
        else{
            dp[i] = sumdp[i] - sumdp[mp[a[i - 1]]] + mod;
        }
        dp[i] %= mod;
        ans += dp[i];
        ans %= mod;
        mp[a[i - 1]] = i;
    }
    printf("%lld", ans);
    return 0;
}