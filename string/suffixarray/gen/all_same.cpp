#include <iostream>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(190'000, 200'000);

    char c = gen.uniform('a', 'z');

    string s(n, c);

    cout << s << endl;
    return 0;
}
