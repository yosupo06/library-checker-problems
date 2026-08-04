#include <algorithm>
#include <vector>
#include "params.h"
#include "testlib.h"

using namespace std;

bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }
    return true;
}

int main() {
    registerValidation();

    int n = inf.readInt(0, N_MAX, "N");
    inf.readSpace();
    long long p = inf.readLong(2LL, (long long)P_MAX, "p");
    inf.readChar('\n');
    ensure(is_prime(p));

    for (int i = 0; i <= n; i++) {
        long long a = inf.readLong(0LL, p - 1, "a_i");
        if (i != n) {
            inf.readSpace();
        } else {
            ensure(a == 1);
            inf.readChar('\n');
        }
    }
    inf.readEof();
}
