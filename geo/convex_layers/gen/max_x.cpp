#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(){
    int n=N_MAX/4;
    printf("%d\n",n*4);
    for(int i=0;i<n;i++){
        printf("%d %d\n",i,i);
        printf("%d %d\n",n*2-i,i);
        printf("%d %d\n",i,n*2-i);
        printf("%d %d\n",n*2-i,n*2-i);
    }
    return 0;
}
