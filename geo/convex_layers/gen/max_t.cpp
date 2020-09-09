#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(){
    int n=N_MAX/3;
    printf("%d\n",n*3);
    for(int i=1;i<=n;i++){
        printf("%d %d\n",n-i,n);
        printf("%d %d\n",n+i,n);
        printf("%d %d\n",n,n-i);
    }
    return 0;
}
