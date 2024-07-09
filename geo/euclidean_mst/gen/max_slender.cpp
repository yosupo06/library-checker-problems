#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

void out(vector<P> S) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int h = 100;
    int w = X_AND_Y_ABS_MAX - h;

    vector<P> S;
    for(int i=0; i<n; i++){
        int x = gen.uniform<int>(-w, w);
        int y = gen.uniform<int>(-h, h);
        S.push_back(make_pair(x, y));
    }

    if(seed == 1){
        for(auto& a : S){
            swap(a.first, a.second);
        }
    }
    else if(seed == 2){
        for(auto& a : S){
            a.second += a.first;
        }
    }
    else if(seed == 3){
        for(auto& a : S){
            a.second -= a.first;
        }
    }

    gen.shuffle(S.begin(), S.end());

    out(S);
    return 0;
}
