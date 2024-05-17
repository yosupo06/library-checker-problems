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

    vector<string> fixed_period_list = {
        string("a"),
        string("z"),
        string("ab"),
        string("zyz"),
        string("abc")
    };


    string period = fixed_period_list.at(seed / 2);
    int maxlen = Q_MAX;
    if (seed % 2 == 1) maxlen /= 2;
    string s;
    while (int(s.size() + period.size()) <= maxlen) {
        s += period;
    }

    int len = int(s.size());
    
    int q = len;
    int num_insert = len;
    int num_delete = 0;
    if (seed % 2) {
        q = len * 2;
        num_delete = q - num_insert;
    }

    vector<int> sw(q);
    for (int i = 0; i < q; i++) sw[i] = gen.uniform_bool();

    int pos_p = 0;
    for (int i = 0; i < num_insert; i++) pos_p += 1 - sw[i];
    int pos_q = pos_p;
    int pos_i = 0;
    
    printf("%d\n", q);

    for (int i = 0; i < num_insert; i++) {
        if (sw[pos_i] == 0) {
            pos_p--;
            printf("0 %c\n", s[pos_p]);
        }
        else {
            printf("1 %c\n", s[pos_q]);
            pos_q++;
        }
        pos_i++;
    }

    for (int i = 0; i < num_delete; i++) {
        if (sw[pos_i] == 0) {
            pos_q--;
            printf("2\n");
        }
        else {
            printf("3\n");
            pos_p++;
        }
        pos_i++;
    }

    return 0;
}
