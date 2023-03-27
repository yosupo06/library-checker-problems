#include <iostream>
#include <vector>
using namespace std;

#include "../base.hpp"

int main() {
  int t;
  scanf("%d\n", &t);
  char b1[100], b2[100];
  for (int i = 0; i < t; i++) {
    scanf("%s %s\n", b1, b2);
    i128 a = str_to_i128(b1);
    i128 b = str_to_i128(b2);
    printf("%s\n", i128_to_str(a + b).c_str());
  }
  return 0;
}
