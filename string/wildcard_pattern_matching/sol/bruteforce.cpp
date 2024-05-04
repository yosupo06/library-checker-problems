#include <string>
#include <iostream>

static char buf[1 << 19];
std::string scan()
{
    scanf("%s", buf);
    return std::string(buf);
}

int main()
{
    std::string s = scan();
    std::string t = scan();

    for (size_t i = 0; i <= s.size() - t.size(); i++)
    {
        bool ok = true;
        for (size_t j = 0; j < t.size() and ok; j++)
            ok &= s[i + j] == t[j] || s[i + j] == '*' || t[j] == '*';
        std::cout << ok;
    }
    std::cout << "\n";
}