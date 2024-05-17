// TLE attack for solutions not using quicklinks or direct links

//   s = ababab...ab
//   push back 'b' or 'c'

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int len = Q_MAX / 4;
    
    int q = len * 4;
    printf("%d\n", q);

    auto alphabet = gen.choice(3, 'a', 'z');
    gen.shuffle(alphabet.begin(), alphabet.end());

    for (int i = 0; i < len; i++) {
        printf("0 %c\n", alphabet[0]);
        printf("0 %c\n", alphabet[2]);
    }

    for (int i = 0; i < len; i++) {
        int t = gen.uniform(0, 1);
        if (gen.uniform_bool()) {
            printf("0 %c\n", alphabet[1 + t]);
            printf("2\n");
        } else {
            printf("1 %c\n", alphabet[0 + t]);
            printf("3\n");
        }
    }

    return 0;
}
