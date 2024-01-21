#include <iostream>
#include <tuple>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long caseid = atoll(argv[1]);
    long long seed = caseid + 200;
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;

    int slide_stride = 3;
    int slide_time_interval = 6;
    int slide_position = 0;
    int window_width = n / 2;
    if(caseid == 1){
        slide_stride = -3;
        slide_position = n - window_width;
    }

    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform<int>(1, MOD - 1);
        int b = gen.uniform<int>(0, MOD - 1);
        printf("%d %d\n", a, b);
    }
    for (int i = 0; i < q; i++) {
        if(i % slide_time_interval == 0){
            int l = slide_position;
            int r = l + window_width;
            int c = gen.uniform<int>(1, MOD - 1);
            int d = gen.uniform<int>(0, MOD - 1);
            printf("0 %d %d %d %d\n", l, r, c, d);
            slide_position += slide_stride;
        } else {
            int t = gen.uniform(0, 1);
            printf("%d ", t);
            if (t == 0) {
                // short range
                int l = -1;
                int r = -1;
                int c = gen.uniform<int>(1, MOD - 1);
                int d = gen.uniform<int>(0, MOD - 1);
                while(l == -1 || n < r){
                    l = gen.uniform(0, n);
                    r = l + gen.uniform(1, 10);
                }
                printf("%d %d %d %d\n", l, r, c, d);
            } else {
                int l, r;
                tie(l, r) = gen.uniform_pair(0, n);
                int x = gen.uniform<int>(0, MOD - 1);
                printf("%d %d %d\n", l, r, x);
            }
        }
    }
    return 0;
}
