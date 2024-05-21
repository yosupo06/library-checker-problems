#include <iostream>
#include "random.h"
#include "../params.h"

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, int(S_LEN_MAX));
    int m = gen.uniform(1, n);

    auto gen_asterisk_string_alternating = [&gen](size_t n, double prob)
    {
        std::string s(n, '*');
        for (size_t i = 0; i < n; i += 2)
            s[i] = (gen.uniform01() < prob ? 'a' : 'b');
        return s;
    };

    double prob = 1.0 / m;

    std::string s = gen_asterisk_string_alternating(n, prob);
    std::string t = gen_asterisk_string_alternating(m, prob);

    printf("%s\n", s.c_str());
    printf("%s\n", t.c_str());
    return 0;
}
