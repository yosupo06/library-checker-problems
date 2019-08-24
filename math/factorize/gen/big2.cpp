#include <iostream>
#include "random.h"

using namespace std;

vector<long long> enum_prime(long long st, long long ed) {
    if (st == 1) st = 2;
    vector<bool> is_prime(ed - st + 1, true);
    for (long long i = 2; i * i <= ed; i++) {
        for (long long j = (st + i - 1) / i * i; j <= ed; j += i) {
            is_prime[j - st] = false;
        }
    }
    vector<long long> primes;
    for (long long i = st; i <= ed; i++) {
        if (is_prime[i - st]) primes.push_back(i);
    }
    return primes;
}

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    auto primes = enum_prime(1'000'000'000 - 1'000'000, 1'000'000'000);
    int k = int(primes.size());
    int q = 50;
    vector<long long> a(q);
    for (int i = 0; i < q; i++) {
        a[i] = primes[gen.uniform(0, k - 1)] * primes[gen.uniform(0, k - 1)];
    }

    cout << q << endl;
    for (auto x: a) {
        cout << x << endl;
    }
    return 0;
}
