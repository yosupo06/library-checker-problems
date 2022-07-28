#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int N;
    int INF = 1e9 + 1;
    scanf("%d", &N);
    vector<int> A(N);
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }
    vector<int> dp(N, INF);
    vector<int> inddp(N, -1);

    for(int i = 0; i < N; i++){
        int ind = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), A[i]));
        dp[ind] = A[i];
        inddp[i] = ind;
    }
    int now = *max_element(inddp.begin(), inddp.end());
    vector<int> LIS(now + 1, 0);
    for(int i = N - 1; i >= 0; i--){
        if(inddp[i] == now){
            LIS[now] = i;
            now--;
        }
    }
    printf("%d\n", (int)LIS.size());
    for(int i = 0; i < (int)LIS.size() - 1; i++){
        printf("%d ", LIS[i]);
    }
    printf("%d\n", LIS[(int)LIS.size() - 1]);
    return 0;
}
