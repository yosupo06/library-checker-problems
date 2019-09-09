#include <iostream>
#include "random.h"

using namespace std;

struct E {
    int from, to, cost;
};

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200'000);
    int m = gen.uniform(0, n - 1);
    int s = gen.uniform(0, n - 1);

    cout << n << " " << m << " " << s << endl;

    for (int i = 0; i < m; i++) {
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        cout << a << " " << b << "\n";
    }

    return 0;
}