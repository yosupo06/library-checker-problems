#include <iostream>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char**) {
    vector<int> a{4033, 4681};
    int q = a.size();
    printf("%d\n", q);
    for (int x: a) {
        printf("%d\n", x);
    }
    return 0;
}
