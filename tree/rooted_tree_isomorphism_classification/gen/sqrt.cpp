
#include <cstdio>
#include <vector>
#include <algorithm>
#include "../params.h"

std::vector<int> makeRootedTree(int BSIZE, int BCOUNT, bool add1){
    std::vector<int> res;
    res.push_back(-1);
    for(int d=0; d<BCOUNT; d++){
        int root = res.size();
        res.push_back(0);
        for(int i=0; i<BSIZE; i++){
            res.push_back(root);
            if(i < 30 && (d & (1 << i))) for(int ii=0; ii<i+1; ii++) res.push_back(res.size() - 1);
        }
    }
    if(add1) res.push_back(0);
    int n = res.size();
    for(int i=0; i<n-1; i++) res[i] = res[i]+1;
    res.pop_back();
    return res;
}

int main(){
    auto T = makeRootedTree(300, 500, true);
    int N = T.size() + 1;
    printf("%d\n", N);
    for(int i=0; i<(int)T.size(); i++){
        if(i) printf(" ");
        printf("%d", T[i]);
    }
    printf("\n");
    return 0;
}
