#include <iostream>
#include "random.h"

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, (1 << 19) - 1);
    int m = gen.uniform(1, n);

    auto gen_asterisk_string = [&gen](size_t n)
    {
        std::string s = gen.lower_string(n);
        for (char &c : s)
            if (gen.uniform_bool())
                c = '*';
        return s;
    };

    std::string s = gen_asterisk_string(n);
    std::string t = gen_asterisk_string(m);

    printf("%s\n", s.c_str());
    printf("%s\n", t.c_str());
    return 0;
}
