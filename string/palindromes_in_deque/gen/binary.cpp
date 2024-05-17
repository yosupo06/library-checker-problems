#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
// #include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    // auto gen = Random(seed);

    int flag0 = int(seed % 2);
    int flag1 = int(seed / 2 % 2);

    int maxlen = Q_MAX / 2;

    string s;
    for (int d = 0; int(s.size() * 2 + 1) < maxlen; d++) {
        string t = s + string(1, 'a' + d) + s;
        s = t;
    }

    int len = int(s.size());
    
    int q = len * 2;
    printf("%d\n", q);

    for (int i = 0; i < len; i++) {
        printf("%d %c\n", flag0 ? 0 : 1, s[i]);
    }

    for (int i = 0; i < len; i++) {
        printf("%d\n", flag1 ? 2 : 3);
    }

    return 0;
}
