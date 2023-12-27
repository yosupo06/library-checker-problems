#include "fastio.hpp"
#include <vector>
#include <algorithm>
using i64 = long long;
#define rep(i,n) for(int i=0; i<(int)(n); i++)

int main(){
    using namespace std;
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    vector<i64> Ax(N), Ay(N);
    rep(i,N) cin >> Ax[i] >> Ay[i];
    int M; cin >> M;
    vector<i64> Bx(M), By(M);
    rep(i,M) cin >> Bx[i] >> By[i];

    int Q; cin >> Q;
    rep(qi, Q){
        int a,b,c; cin >> a >> b >> c;
        i64 xab = Ax[b] - Ax[a];
        i64 yab = Ay[b] - Ay[a];
        i64 xac = Ax[c] - Ax[a];
        i64 yac = Ay[c] - Ay[a];
        if(xab * yac - yab * xac == 0){
            cout << "0\n";
            continue;
        }
        if(xab * yac - yab * xac < 0){
            swap(xab, xac);
            swap(yab, yac);
            swap(b, c);
        }
        //     c
        // 
        // a -----> b
        int ans = 0;
        rep(m,M){
            bool ok = true;
            rep(t,3){
                i64 xV = Ax[b] - Ax[a];
                i64 yV = Ay[b] - Ay[a];
                i64 xW = Bx[m] - Ax[a];
                i64 yW = By[m] - Ay[a];
                if(xV * yW - yV * xW <= 0){
                    // a ---V--> b
                    //  -_
                    //    W-_
                    //       ->x     (border ng)
                    ok = false;
                }
                swap(a,b); swap(b,c);
            }
            if(ok) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
