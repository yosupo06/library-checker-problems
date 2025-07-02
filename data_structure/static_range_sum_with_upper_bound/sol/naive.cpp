#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n,q;
    scanf("%d %d",&n,&q);

    vector<long long> a(n);
    for(int i = 0;i < n;i++) scanf("%lld",&a[i]);

    for(int query = 0;query < q;query++){
        int l,r,x;
        scanf("%d %d %d",&l,&r,&x);
        int ans_cnt = 0;
        for(int i = l;i < r;i++){
            if(a[i] <= x) ans_cnt++;
        }
        long long ans_sum = 0LL;
        for(int i = l;i < r;i++){
            if(a[i] <= x) ans_sum += a[i];
        }
        printf("%d %lld\n",ans_cnt,ans_sum);
    }

    return 0;
}