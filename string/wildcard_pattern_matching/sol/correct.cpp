#include <string>
#include <vector>
#include <tuple>

#include <atcoder/convolution>

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
    std::vector v(3, std::vector<ll>(n));
    for (size_t i = 0; i < n; i++)
    {
        ll a = s[i] == '*' ? 0 : s[i] - 'a' + 1;
        v[0][i] = a;
        v[1][i] = a * a;
        v[2][i] = a * a * a;
    }
    return v;
}

int main()
{

    std::string s = scan();
    std::string t = scan();

    std::reverse(t.begin(), t.end());

    auto S = make_vectors(s);
    auto T = make_vectors(t);

    size_t n = s.size(), m = t.size();
    std::vector<ll> sum(n - m + 1, 0);
    for (size_t j = 0; j < 3; j++)
    {
        auto st = atcoder::convolution_ll(S[j], T[2 - j]);
        for (size_t i = 0; i <= n - m; i++)
            sum[i] += st[i];
    }

    for (auto a : sum)
        std::cout << bool(a);
    std::cout << "\n";
}