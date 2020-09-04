#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(){
    int n=N_MAX/2;
    printf("%d\n",n*2);
    for(int i=1;i<=n;i++){
        printf("%d %d\n",i,0);
        printf("%d %d\n",0,i);
    }
    return 0;
}
