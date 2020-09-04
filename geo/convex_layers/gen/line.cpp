#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_MAX);
    printf("%d\n",n);
    //Pick a random direction
    auto dx = gen.uniform(-2,2);
    auto dy = gen.uniform(-2,2);
    while(dx==0&&dy==0) {
      dx = gen.uniform(0,2);
      dy = gen.uniform(0,2);
    }
    //Pick a random bottom left corner for the bounding box
    auto x0 = gen.uniform(0LL,X_AND_Y_MAX-(n-1)*abs(dx));
    auto y0 = gen.uniform(0LL,X_AND_Y_MAX-(n-1)*abs(dy));
    //Find the starting point
    if(dx<0){
      x0-=(n-1)*dx;
    }
    if(dy<0){
      y0-=(n-1)*dy;
    }
    //Output the points
    for(int i=0;i<n;i++){
        printf("%lld %lld\n",x0+i*dx,y0+i*dy);
    }
    return 0;
}
