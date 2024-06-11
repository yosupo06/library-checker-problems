#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(N_M_MAX - 100, N_M_MAX);
    int m = gen.uniform<int>(N_M_MAX - 100, N_M_MAX);
    
    printf("%d %d\n", n, m);

    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++){
        a[i] = gen.uniform<int>(0, m - 1);
        b[i] = gen.uniform<int>(a[i] + 1, m);
    }

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    for(int i = 0; i < n; i++){
        a[i] += gen.uniform<int>(-2, 2);
        if(a[i] < 0)a[i] = 0;
        if(a[i] > m)a[i] = m;
        b[i] += gen.uniform<int>(-2, 2);
        if(b[i] < 0)b[i] = 0;
        if(b[i] > m)b[i] = m;
        if(a[i] == b[i]){
            if(a[i] != 0){
                a[i]--;
            }
            else{
                b[i]++;
            }
        }
        if(a[i] > b[i]){
            swap(a[i], b[i]);
        }
    }

    for(int i = 0; i < n; i++){
        printf("%d", a[i]);
        if(i == n - 1){
            printf("\n");
        }
        else{
            printf(" ");
        }
    }

    for(int i = 0; i < n; i++){
        printf("%d", b[i]);
        if(i == n - 1){
            printf("\n");
        }
        else{
            printf(" ");
        }
    }

    return 0;
}