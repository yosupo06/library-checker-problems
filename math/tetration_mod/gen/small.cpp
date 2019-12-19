#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int l = 20;
    int t = l * l * l;
    cout << t << "\n";
    for (int a = 0; a < l; a++) {
        for (int b = 0; b < l; b++) {
            for (int m = 1; m <= l; m++) {
                cout << a << " " << b << " " << m << "\n";
            }
        }
    }
    return 0;
}
