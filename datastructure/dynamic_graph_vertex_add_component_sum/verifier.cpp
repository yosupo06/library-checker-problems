#include <set>
#include <tuple>
#include "testlib.h"
using namespace::std;
#define N_MAX 200'000
#define Q_MAX 200'000
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1,N_MAX, "n");
    inf.readSpace();
    int q = inf.readInt(1,Q_MAX,"q");
    inf.readEoln();
    set<pair<int,int>>s;
    for(int i=0;i<n;i++) {
        inf.readInt(1,1'000'000'000,"a_i");
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
            inf.readInt(0,1'000'000'000,"x");
        }
        if(x==3){
            inf.readInt(0,n-1,"v");
        }
        inf.readEoln();
    }
    inf.readEof();
}