#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform(0, 1000000000);
    int b = gen.uniform(0, 1000000000);
    
    cout << a << " " << b << endl;
    return 0;
}
