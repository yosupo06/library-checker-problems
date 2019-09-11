#include <iostream>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << gen.uniform(0, 500'000) << "\n";
    return 0;
}
