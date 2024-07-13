#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

void out(vector<P> S) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
}

int sqrt_int_ceil(int nn){
    int n = 0;
    while((n+1) * (n+1) <= nn) n++;
    return n;
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int chunk_width = 10;
    int n = N_MAX;
    int chunk_count = n / 20;

    vector<int> chunk_n(chunk_count);
    for(int i=0; i<n; i++) chunk_n[gen.uniform<int>(0, chunk_count-1)]++;

    const int global_coord_min = int(-X_AND_Y_ABS_MAX);
    const int global_coord_width = int(X_AND_Y_ABS_MAX) * 2 + 1;
    int chunk_count_side = sqrt_int_ceil(chunk_count);
    int chunk_interval = (global_coord_width - chunk_width) / (chunk_count_side - 1);

    vector<P> S;
    
    for(int chunk_i = 0; chunk_i < chunk_count; chunk_i++){
        int offset_x = global_coord_min + chunk_i / chunk_count_side * chunk_interval;
        int offset_y = global_coord_min + chunk_i % chunk_count_side * chunk_interval;
        for(int i = 0; i < chunk_n[i]; i++){
            int dx = gen.uniform<int>(0, chunk_width - 1);
            int dy = gen.uniform<int>(0, chunk_width - 1);
            S.push_back(make_pair(offset_x + dx, offset_y + dy));
        }
    }

    gen.shuffle(S.begin(), S.end());

    out(S);
    return 0;
}
