#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n,q;
    scanf("%d %d",&n,&q);

    vector<int> a(n);
    for(int i = 0;i < n;i++) scanf("%d",&a[i]);

    for(int query = 0;query < q;query++){
        int t,l,r,x;
        scanf("%d %d %d %d",&t,&l,&r,&x);
        if(t == 0){
            int ans = 0;
            for(int i = 0;i < n;i++){
                if(a[i] <= x) ans++;
            }
            printf("%d\n",ans);
        }else{
            long long ans = 0;
            for(int i = 0;i < n;i++){
                if(a[i] <= x) ans += a[i];
            }
            printf("%lld\n",ans);
        }
    }

    return 0;
}