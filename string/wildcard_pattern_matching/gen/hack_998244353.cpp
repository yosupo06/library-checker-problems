#include <iostream>
#include <map>
#include "../params.h"
#include "random.h"

using namespace std;

char random_char(Random &gen)
{
    int x = gen.uniform<int>(0, 26);
    return (x == 26 ? '*' : 'a' + x);
}

/*
return {A,B} s.t.
|A| = |B| = N
Σ A_i B_i (A_i - B_i)^2 ≡ 0 with `a` = off, ..., `z` = off + 25
*/
pair<string, string> hack_998244353(Random &gen, int N, int off)
{
    assert(N == (1 << 18));
    // a=off, ..., z=25+off
    string A(N, '*'), B(N, '*');
    int M = N / 2;
    for (int i = 0; i < M; ++i)
        A[i] = random_char(gen), B[i] = random_char(gen);

    auto calc = [&](int i) -> int
    {
        int a = (A[i] == '*' ? 0 : off + (A[i] - 'a'));
        int b = (B[i] == '*' ? 0 : off + (B[i] - 'a'));
        return a * b * (a - b) * (a - b);
    };

    constexpr int mod = 998244353;

    // 左 M 文字について k 文字を採用した場合の sum
    map<int, int> MP;
    long long sum_l = 0;
    for (int i = 0; i < M; ++i)
    {
        sum_l += calc(i);
        MP[sum_l % mod] = 1 + i;
    }

    long long sum_r = 0;
    while (1)
    {
        int i = gen.uniform<int>(M, N - 1);
        sum_r -= calc(i);
        A[i] = random_char(gen), B[i] = random_char(gen);
        sum_r += calc(i);
        int k = sum_r % mod;
        k = mod - k;
        if (sum_r != 0 && MP.count(k))
        {
            for (int i = MP[k]; i < M; ++i)
                A[i] = '*', B[i] = '*';
            break;
        }
    }
    long long sm = 0;
    for (int i = 0; i < N; ++i)
        sm += calc(i);
    assert(sm % mod == 0);
    return {A, B};
}

int main(int, char *argv[])
{
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int offsets[] = {0, 1, int('a')};

    int n = S_LEN_MAX;
    int m = n / 2;
    auto [A, B] = hack_998244353(gen, m, offsets[seed % 3]);
    int a = gen.uniform<int>(0, n - m);
    int b = n - m - a;
    string L, R;
    for (int i = 0; i < a; ++i)
        L += random_char(gen);
    for (int i = 0; i < b; ++i)
        R += random_char(gen);
    A = L + A + R;

    printf("%s\n", A.c_str());
    printf("%s\n", B.c_str());
    return 0;
}
