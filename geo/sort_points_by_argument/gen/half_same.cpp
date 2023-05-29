#include <cstdio>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

int uniform_the_range(Random& gen){
    return gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
}

pair<int, int> random_on_x_axis_but_not_origin(Random& gen){
    int x = 0;
    while(x == 0) x = uniform_the_range(gen);
    return { x, 0 };
}

pair<int, int> random_on_no_axis(Random& gen){
    int y = 0;
    while(y == 0) y = uniform_the_range(gen);
    int x = 0;
    while(x == 0) x = uniform_the_range(gen);
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
        if(gen.uniform_bool()){
            printf("%d %d\n", concentrate.first, concentrate.second);
        }
        else{
            int x = uniform_the_range(gen);
            int y = uniform_the_range(gen);
            printf("%d %d\n", x, y);
        }
    }
    return 0;
}
