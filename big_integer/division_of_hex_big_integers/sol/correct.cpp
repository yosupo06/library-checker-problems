#include <iostream>
using namespace std;

#include "../base.hpp"
#include "../params.h"

char buf1[LOG_16_A_AND_B_MAX + 100];
char buf2[LOG_16_A_AND_B_MAX + 100];

int main() {
  int t;
  scanf("%d\n", &t);
  while (t--) {
    scanf("%s %s\n", buf1, buf2);
    bigint a = string{buf1};
    bigint b = string{buf2};
    auto [q, r] = divmod(a, b);
    printf("%s %s\n", q.to_string().c_str(), r.to_string().c_str());
  }
}
