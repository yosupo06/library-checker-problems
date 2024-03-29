/*

O( N^2 M + Q ) time solution

too slow at N,M = 1000

*/

#include "fastio.hpp"
#include <vector>
#include <algorithm>
#include <cassert>

template<class Int = long long, class Int2 = long long>
struct VecI2 {
    Int x, y;
    VecI2() : x(0), y(0) {}
    VecI2(Int _x, Int _y) : x(_x), y(_y) {}
    VecI2 operator+(VecI2 r) const { return VecI2(x+r.x, y+r.y); }
    VecI2 operator-(VecI2 r) const { return VecI2(x-r.x, y-r.y); }
    VecI2 operator-() const { return VecI2(-x, -y); }
    Int2 operator*(VecI2 r) const { return Int2(x) * Int2(r.x) + Int2(y) * Int2(r.y); }
    Int2 operator^(VecI2 r) const { return Int2(x) * Int2(r.y) - Int2(y) * Int2(r.x); }
    static bool compareYX(VecI2 a, VecI2 b){ return a.y < b.y || (!(b.y < a.y) && a.x < b.x); }
    static bool compareXY(VecI2 a, VecI2 b){ return a.x < b.x || (!(b.x < a.x) && a.y < b.y); }
};


using i64 = long long;
using namespace std;
using Vec = VecI2<i64>;
#define rep(i,n) for(int i=0; i<(int)(n); i++)

int main(){
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    vector<Vec> A(N);
    rep(i,N) cin >> A[i].x >> A[i].y;
    int M; cin >> M;
    vector<Vec> B(M);
    rep(i,M) cin >> B[i].x >> B[i].y;

    auto pointL = vector<int>(N); // bx < Ax
    auto pointM = vector<int>(N); // bx = Ax
    rep(i,N) rep(j,M) if(A[i].y == B[j].y){
        if(B[j].x < A[i].x) pointL[i]++;
        if(B[j].x == A[i].x) pointM[i]++;
    }

    auto edgeL = vector<vector<int>>(N, vector<int>(N)); // bx < lerp(Ax, Bx)
    auto edgeM = vector<vector<int>>(N, vector<int>(N)); // bx = lerp(Ax, Bx)
    rep(a,N) rep(b,N) if(A[a].y < A[b].y){
        rep(i,M) if(A[a].y < B[i].y && B[i].y < A[b].y){
            auto det = (A[a] - A[b]) ^ (B[i] - A[b]);
            if(det < 0) edgeL[a][b]++;
            if(det == 0) edgeM[a][b]++;
        }
    }

    int Q; cin >> Q;
    rep(qi, Q){
        int a,b,c; cin >> a >> b >> c;
        if(Vec::compareYX(A[b], A[a])) swap(a, b);
        if(Vec::compareYX(A[c], A[b])) swap(b, c);
        if(Vec::compareYX(A[b], A[a])) swap(a, b);
        // c   ^y
        // b   |
        // a   +---> x

        //      c
        // nega |
        //      v posi
        //      a
        auto det = (A[a] - A[c]) ^ (A[b] - A[c]);
        int ans = 0;
        if(det != 0){
            if(A[a].y == A[b].y){ // A[a].x < A[b].x
                //   c
                // a   b
                ans = edgeL[b][c] - (edgeL[a][c] + edgeM[a][c]);
            } else if(A[b].y == A[c].y){ // A[b].x < A[c].x
                // b   c
                //   a
                ans = edgeL[a][c] - (edgeL[a][b] + edgeM[a][b]);
            } else if(det < 0){
                //    c
                // b
                //    a
                ans += edgeL[a][c];
                ans -= edgeL[b][c] + edgeM[b][c];
                ans -= edgeL[a][b] + edgeM[a][b];
                ans -= pointL[b] + pointM[b];
            } else {
                // c
                //    b
                // a
                ans += edgeL[a][b];
                ans += edgeL[b][c];
                ans += pointL[b];
                ans -= edgeL[a][c] + edgeM[a][c];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
