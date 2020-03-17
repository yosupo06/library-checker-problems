#include <algorithm>
#include "testlib.h"

using namespace std;
using ll = long long;

long long pow(long long a,long long n,long long p){
    long long ret=1;
    for(;n>0;n>>=1,a=a*a%p)if(n%2==1)ret=ret*a%p;
    return ret;
}

long long gcd(long long a,long long b){
    return a==0?b:gcd(b%a,a);
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();

    for (int i = 0; i < t; i++) {
        long long k = inf.readLong();
        long long y = inf.readLong();
        long long p = inf.readLong();
        long long x = ouf.readLong(-1, p - 1);
        if (x != -1 && pow(x,k,p) != y) {
            quitf(_wa, "invalid x");
        }
        k%=p-1;
        bool actual = (x != -1);
        bool expected = ((k==0 && y==1) || (k!=0 && y==0) || (k!=0 && pow(y,(p-1)/gcd(k,p-1),p)==1));
        if (expected && !actual) {
            quitf(_wa, "you cann't find x");
        }
        if (!expected && actual) {
            quitf(_fail, "what happened???");
        }
    }
    quitf(_ok, "OK");
}
