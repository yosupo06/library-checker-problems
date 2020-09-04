#include <bits/stdc++.h>
#include "testlib.h"
#include <set>
#include "params.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n");
    inf.readEoln();
    std::set<std::pair<int,int> > ps;
    for(int i=0;i<n;i++){
      int x=inf.readInt(0,X_AND_Y_MAX);
      inf.readSpace();
      int y=inf.readInt(0,X_AND_Y_MAX);
      inf.readEoln();
      ensuref(!ps.count({x,y}),"Duplicate point (%d,%d)\n",x,y);
      ps.insert({x,y});
    }
    inf.readEof();
}
