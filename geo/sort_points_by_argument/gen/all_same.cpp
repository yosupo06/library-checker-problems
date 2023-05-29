#include <cstdio>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

pair<int, int> random_on_x_axis_but_not_origin(Random& gen){
    int x = 0;
    while(x == 0) x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
    return { x, 0 };
}

pair<int, int> random_on_no_axis(Random& gen){
    int y = 0;
    while(y == 0) y = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
    int x = 0;
    while(x == 0) x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
    return { x, y };
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    
    printf("%d\n", n);
    
    pair<int, int> concentrate = { 0, 0 };

    if(seed == 0){
        concentrate = { 0, 0 };
    }
    else if(seed == 1){
        concentrate = random_on_x_axis_but_not_origin(gen);
    }
    else if(seed == 2){
        concentrate = random_on_no_axis(gen);
    }

    for(int i=0; i<n; i++){
        printf("%d %d\n", concentrate.first, concentrate.second);
    }
    return 0;
}
