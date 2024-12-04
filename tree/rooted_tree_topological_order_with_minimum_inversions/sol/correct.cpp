#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

namespace nachia {

struct Dsu{
private:
    int N;
    std::vector<int> P;
    std::vector<int> H;
public:
    Dsu() : N(0) {}
    Dsu(int n) : N(n), P(n, -1), H(n) {
        for(int i=0; i<n; i++) H[i] = i;
    }
    int leader(int u){
        if(P[u] < 0) return u;
        int v = P[u];
        while(P[v] >= 0){ P[u] = P[v]; u = v; v = P[v]; }
        return P[u];
    }
    int operator[](int u){ return H[leader(u)]; }
    void merge(int u, int v, int newLabel){
        u = leader(u);
        v = leader(v);
        if(u == v){ H[u] = newLabel; return; }
        N--;
        if(-P[u] < -P[v]) std::swap(u, v);
        P[u] += P[v];
        H[P[v] = u] = newLabel;
    }
};

} // namespace nachia


template<class Weight>
std::vector<int> TreeSearchMinimumInversion(
    int n,
    std::vector<int> par,
    std::vector<Weight> deltaT,
    std::vector<Weight> A,
    int start
){
    struct Frac {
        Weight t;
        Weight a;
        int root;
        int c;
        bool operator<(const Frac& r) const {
            return a * r.t < t * r.a;
        }
        Frac& operator+=(const Frac& r){
            a += r.a; t += r.t; return *this;
        }
    };
    std::priority_queue<Frac> que;
    nachia::Dsu dsu(n);
    for(int v=0; v<n; v++) if(par[v] != -1){
        que.push({ deltaT[v], A[v], v, 0 });
    }
    std::vector<int> linkA(n);
    for(int i=0; i<n; i++) linkA[i] = i;
    std::vector<int> tag(n, 0);
    while(que.size()){
        auto q = que.top(); que.pop();
        int v = q.root;
        if(tag[v] != q.c) continue;
        int w = dsu[par[v]];
        deltaT[w] = deltaT[w] + deltaT[v];
        A[w] = A[w] + A[v];
        dsu.merge(v, w, w);
        if(par[w] != -1) que.push({ deltaT[w], A[w], w, ++tag[w] });
        std::swap(linkA[v], linkA[w]);
    }
    std::vector<int> ans;
    ans.push_back(linkA[start]);
    while(ans.back() != start) ans.push_back(linkA[ans.back()]);
    std::reverse(ans.begin(), ans.end());
    return ans;
}

using namespace std;

int main(){
    using i64 = long long;
    int N; scanf("%d", &N);
    vector<int> par(N, -1);
    for(int i=1; i<N; i++) scanf("%d", &par[i]);
    vector<i64> C(N), D(N);
    for(int i=0; i<N; i++){ int x; scanf("%d", &x); C[i] = x; }
    for(int i=0; i<N; i++){ int x; scanf("%d", &x); D[i] = x; }

    auto P = TreeSearchMinimumInversion<i64>(N, par, D, C, 0);

    i64 X = 0;
    i64 sumD = 0;
    for(int v : P){
        X += sumD * C[v];
        sumD += D[v];
    }

    printf("%lld\n", X);

    for(int i=0; i<N; i++){
        if(i) printf(" ");
        printf("%d", P[i]);
    }
    printf("\n");
    return 0;
}
