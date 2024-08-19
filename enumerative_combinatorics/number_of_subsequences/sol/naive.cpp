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
    map<string, int> mp;
    long long ans = 0;
    if(n > 30){
        printf("%lld", ans % mod);
        return 0;
    }
    for(int bit = 1; bit < (1 << (int)n); bit++){
        string s = "";
        for(int i = 0; i < n; i++){
            if(1 & (bit >> i)){
                s += to_string(a[i]) + ",";
            }
        }
        if (mp.find(s) == mp.end()){
            mp[s] = 1;
            ans++;
        }
    }
    printf("%lld", ans % mod);
    return 0;
}