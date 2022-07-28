#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main(void){
    long long mod = 998244353ll;
    int n;
    scanf("%d", &n);
    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        scanf("%lld", &a[i]);
    }
    
    vector<long long> dp(n + 1);
    dp[0] = 1ll;
    for(int i = 1; i < n + 1; i++){
        dp[i] = 0ll;
    }

    map<long long, long long> count;

    for(int i = 0; i < n; i++){
        dp[i + 1] += 2ll * dp[i] - count[a[i]] + mod;
        dp[i + 1] %= mod;
        count[a[i]] += dp[i] - count[a[i]] + mod;
        count[a[i]] %= mod;
    }
    printf("%lld\n", (dp[n] - 1 + mod) % mod);

    return 0;
}