
#include <vector>
#include <cstdio>

using u32 = unsigned int;
using u64 = unsigned long long;

const u32 MOD = 998244353;

struct F{
    u32 a;
    u32 b;

    u32 operator()(u32 x) const { return ((u64)x * a + b) % MOD; }
};

F operator+(F l, F r){
    F res;
    res.a = (u64)l.a * r.a % MOD;
    res.b = ((u64)l.b * r.a + r.b) % MOD;
    return res;
}

std::vector<F> A[2];
std::vector<F> Prod[2];

void recalcProd(){
    Prod[0].resize(A[0].size() + 1);
    Prod[0][0] = { 1, 0 };
    for(size_t i=0; i<A[0].size(); i++) Prod[0][i+1] = A[0][i] + Prod[0][i];
    Prod[1].resize(A[1].size() + 1);
    Prod[1][0] = { 1, 0 };
    for(size_t i=0; i<A[1].size(); i++) Prod[1][i+1] = Prod[1][i] + A[1][i];
}

int main(){

    recalcProd();

    int Q; scanf("%d", &Q);
    for(int i=0; i<Q; i++){
        int ty; scanf("%d", &ty);
        if(ty == 0){
            u32 a, b; scanf("%d %d", &a, &b);
            A[0].push_back({ a, b });
            Prod[0].push_back(A[0].back() + Prod[0].back());
        }
        if(ty == 1){
            u32 a, b; scanf("%d %d", &a, &b);
            A[1].push_back({ a, b });
            Prod[1].push_back(Prod[1].back() + A[1].back());
        }
        if(ty == 2){
            if(A[0].empty()){
                int lessHalf = A[1].size() / 2;
                A[0] = std::vector<F>(A[1].rbegin() + lessHalf, A[1].rend());
                A[1] = std::vector<F>(A[1].end() - lessHalf, A[1].end());
                recalcProd();
            }
            A[0].pop_back();
            Prod[0].pop_back();
        }
        if(ty == 3){
            if(A[1].empty()){
                int lessHalf = A[0].size() / 2;
                A[1] = std::vector<F>(A[0].rbegin() + lessHalf, A[0].rend());
                A[0] = std::vector<F>(A[0].end() - lessHalf, A[0].end());
                recalcProd();
            }
            A[1].pop_back();
            Prod[1].pop_back();
        }
        if(ty == 4){
            u32 x; scanf("%d", &x);
            u32 ans = (Prod[0].back() + Prod[1].back()) (x);
            printf("%u\n", ans);
        }
    }
    return 0;
}
