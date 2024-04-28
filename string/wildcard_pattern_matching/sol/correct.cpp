#include <string>
#include <vector>
#include <tuple>

#include <atcoder/all>

using ll = long long;

static char buf[1 << 19];
std::string scan()
{
    scanf("%s", buf);
    return std::string(buf);
}

auto make_vectors(const std::string &s)
{
    size_t n = s.size();
    std::vector<ll> s1(n), s2(n), s3(n);
    for (size_t i = 0; i < n; i++)
    {
        ll a = s[i] == '*' ? 0 : s[i] - 'a' + 1;
        s1[i] = a;
        s2[i] = a * a;
        s3[i] = a * a * a;
    }
    return std::make_tuple(s1, s2, s3);
}

int main()
{

    std::string s = scan();
    std::string t = scan();
}