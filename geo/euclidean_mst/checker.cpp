#include <algorithm>
#include <vector>
#include <utility>
#include "testlib.h"

using namespace std;
using ll = long long;


struct DsuFast{
private:
    std::vector<int> w;
public:
    DsuFast(int n = 0) : w(n, -1) {}
    int leader(int u){
        if(w[u] < 0) return u;
        return w[u] = leader(w[u]);
    }
    int operator[](int u){ return leader(u); }
    int merge(int u, int v){
        u = leader(u);
        v = leader(v);
        if(u == v) return u;
        if(-w[u] < -w[v]) std::swap(u, v);
        w[u] += w[v];
        w[v] = u;
        return u;
    }
    int size(int u){ return -w[leader(u)]; }
    bool same(int u, int v){ return leader(u) == leader(v); }
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);


    int N = inf.readInt();

    vector<ll> X(N), Y(N);
    for(int i=0; i<N; i++){
        X[i] = inf.readInt();
        Y[i] = inf.readInt();
    }

    auto weight = [&](int a, int b){
        ll dx = X[a] - X[b];
        ll dy = Y[a] - Y[b];
        return dx * dx + dy * dy;
    };

    DsuFast dsu_ans(N);
    vector<ll> weights_ans;
    for(int i=0; i<N-1; i++){
        int a = ans.readInt(0, N - 1);
        int b = ans.readInt(0, N - 1);
        dsu_ans.merge(a, b);
        weights_ans.push_back(weight(a, b));
    }

    if(dsu_ans.size(0) != N){
        quit(_fail, "the output of writer\'s solution is not connected");
    }

    sort(weights_ans.begin(), weights_ans.end());

    DsuFast dsu_out(N);
    vector<ll> weights_out;
    for(int i=0; i<N-1; i++){
        int a = ouf.readInt(0, N - 1);
        int b = ouf.readInt(0, N - 1);
        dsu_out.merge(a, b);
        weights_out.push_back(weight(a, b));
    }

    if(dsu_out.size(0) != N){
        quit(_wa, "not connected");
    }

    sort(weights_out.begin(), weights_out.end());

    for(int i=0; i<N-1; i++){
        if(weights_ans[i] > weights_out[i]){
            quit(_fail, "your output showed the writer solution doesn\'t output the minumum spanning tree");
        }
        if(weights_ans[i] < weights_out[i]){
            quit(_wa, "not the minumum cost");
        }
    }
    
    quitf(_ok, "OK");
}
