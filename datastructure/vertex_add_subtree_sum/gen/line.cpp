#include "random.h"
#include <iostream>

using namespace std;

int main(int, char *argv[])
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    int q = 500'000;
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << gen.uniform(0, 1'000'000'000);
        if (i != n - 1)
            cout << " ";
    }
    cout << "\n";

    for (int i = 1; i < n; i++)
    {
        cout << i - 1;
        if (i != n - 1)
            cout << " ";
    }
    cout << "\n";

    for (int i = 0; i < q; i++)
    {
        int t = gen.uniform(0, 1);
        cout << t << " ";
        if (t == 0)
        {
            int p = gen.uniform(0, n - 1);
            int x = gen.uniform(0, 1'000'000'000);
            cout << p << " " << x << "\n";
        }
        else
        {
            auto u = gen.uniform(0, n - 1);
            cout << u << "\n";
        }
    }
    return 0;
}
