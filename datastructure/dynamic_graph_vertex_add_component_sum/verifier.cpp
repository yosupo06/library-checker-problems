#include <set>
#include <tuple>
#include "testlib.h"
#include "./params.h"
using namespace::std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(N_AND_Q_MIN,N_AND_Q_MAX, "n");
    inf.readSpace();
    int q = inf.readInt(N_AND_Q_MIN,N_AND_Q_MAX,"q");
    inf.readEoln();
    set<pair<int,int>>s;
    for(int i=0;i<n;i++) {
        inf.readInt(A_AND_X_MIN,A_AND_X_MAX,"a_i");
        if (i!=n-1)inf.readSpace();
    }
    inf.readEoln();
    for(int i=0;i<q;i++) {
        int x = inf.readInt(0,3,"x");
        inf.readSpace();
        if(x==0){
            int u = inf.readInt(0,n-1,"u");
            inf.readSpace();
            int v = inf.readInt(0,n-1,"v");
            ensure(u!=v);
            ensure(!s.count(minmax(u,v)));
            s.insert(minmax(u,v));
        }
        if(x==1){
            int u = inf.readInt(0,n-1,"u");
            inf.readSpace();
            int v = inf.readInt(0,n-1,"v");
            ensure(u!=v);
            ensure(s.count(minmax(u,v)));
            s.erase(minmax(u,v));
        }
        if(x==2){
            inf.readInt(0,n-1,"v");
            inf.readSpace();
            inf.readInt(A_AND_X_MIN,A_AND_X_MAX,"x");
        }
        if(x==3){
            inf.readInt(0,n-1,"v");
        }
        inf.readEoln();
    }
    inf.readEof();
}