#include <vector>
#include <cstdio>

using namespace std;


int main() {
    using ll = long long;

    int N;
    scanf("%d", &N);

    vector<ll> X(N), Y(N);
    for(int i=0; i<N; i++){
        int x, y; scanf("%d%d", &x, &y);
        X[i] = x;
        Y[i] = y;
    }

    auto weight = [&](int a, int b){
        ll dx = X[a] - X[b];
        ll dy = Y[a] - Y[b];
        return dx * dx + dy * dy;
    };

    vector<pair<ll, int>> nx(N, { ll(1) << 60, -1 });
    vector<int> vis(N);
    vector<pair<int,int>> ans;

    vis[0] = 1;
    for(int i=1; i<N; i++) nx[i] = { weight(0,i), 0 };

    for(int t=0; t<N-1; t++){
        int v = -1;
        for(int w=0; w<N; w++) if(vis[w] == 0){
            if(v == -1 || nx[w] < nx[v]) v = w;
        }
        vis[v] = 1;
        ans.push_back({ v, nx[v].second });

        for(int w=0; w<N; w++){
            auto d = make_pair(weight(v,w), v);
            if(d < nx[w]) nx[w] = d;
        }
    }

    for(auto a : ans){
        printf("%d %d\n", a.first, a.second);
    }

    return 0;
}
