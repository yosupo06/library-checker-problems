#include <iostream>
#include "random.h"
#include "../params.h"

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, int(S_LEN_MAX));
    int m = gen.uniform(1, n);

    auto gen_asterisk_string_ab = [&gen](size_t n)
    {
        std::string s(n, '*');
        for (char &c : s)
            if (gen.uniform(1, 100) == 1)
                c = gen.uniform('a', 'b');
        return s;
    };

    std::string s = gen_asterisk_string_ab(n);
    std::string t = gen_asterisk_string_ab(m);

    printf("%s\n", s.c_str());
    printf("%s\n", t.c_str());
    return 0;
}
