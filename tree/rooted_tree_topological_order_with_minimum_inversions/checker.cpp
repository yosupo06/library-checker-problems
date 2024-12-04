#include "testlib.h"

using namespace std;

long long EvalOutput(int N, const vector<int>& P, const vector<int>& C, const vector<int>& D, InStream& fs){
    long long x_out = fs.readLong();

    long long x = 0;
    long long sum_d = 0;
    vector<int> vis(N);
    
    for(int i=0; i<N; i++){
        int p = fs.readInt(0,N-1);
        if(P[p] >= 0 && vis[P[p]]) return -1;
        x += C[p] * sum_d;
        sum_d += D[p];
    }

    if(x != x_out) return -2;
    return x;
}

int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    vector<int> P(N,-1);
    for(int i=1; i<N; i++) P[i] = inf.readInt();
    vector<int> C(N,-1);
    for(int i=0; i<N; i++) C[i] = inf.readInt();
    vector<int> D(N,-1);
    for(int i=0; i<N; i++) D[i] = inf.readInt();

    long long ans_eval = EvalOutput(N, P, C, D, ans);
    long long out_eval = EvalOutput(N, P, C, D, ouf);
    
    if(out_eval == -1){
        quitf(_wa, "Invalid permutation");
    }
    if(out_eval == -2){
        quitf(_wa, "X and p does not match");
    }
    if(out_eval > ans_eval){
        quitf(_wa, "X is not minimized");
    }
    if(out_eval < ans_eval){
        quitf(_fail, "Jury\'s solution is evalueted to be not optimal");
    }

    quitf(_ok, "correct answer");
}
