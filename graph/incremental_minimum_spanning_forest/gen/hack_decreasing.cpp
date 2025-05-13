#include "../params.h"
#include<iostream>
using namespace std;

int main(){    
    int n = N_MAX, m = M_MAX;

    printf("%d %d\n", n, m);

    for(int i = 0; i < m; i++){
        printf("%d %d %d\n", i%n, (i+1)%n, m-i);
    }
    
    return 0;

}