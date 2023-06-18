#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include "random.h"
#include "../params.h"

using namespace std;

//int main(int, char* argv[]) {
    //long long seed = atoll(argv[1]);
    //auto gen = Random(seed);
int main(){

    auto f = [](long long x){
        return x * (x+1) * (x+2) / 6;
    };

    auto max_ord = [&](long long maxN){
        assert(f(2) <= maxN);
        long long ok = 2, ng = 10000;
        while(ok + 1 < ng){
            long long x = (ok + ng) / 2;
            ((f(x) <= maxN) ? ok : ng) = x;
        }
        return ok;
    };

    long long re = max_ord(N_MAX);
    // may do some random stuff to `re`

    string s;
    for(int k=1; k<=re; k++){
        string tmp = string(k, 'a');
        tmp.back() = 'b';
        for(int t=k; t<=re; t++) s += tmp;
    }

    assert(f(re) == (long long)s.size());

    printf("%s\n", s.c_str());
    return 0;
}
