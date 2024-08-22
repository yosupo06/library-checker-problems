#include <cstdio>
#include <cstdlib>
#include "../params.h"

int main(int, char** argv){
    int n = atoi(argv[1]) + N_MIN;
    printf("%d\n", n);
    return 0;
}
