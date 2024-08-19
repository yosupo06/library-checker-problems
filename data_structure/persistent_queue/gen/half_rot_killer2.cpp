#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>

int main() {
  const int q = 140000+200000;
  int p=-1;
  std::printf("%d\n", q);
  for (int i=0;i<140000;++i) {
    std::printf("0 %d 1\n", i-1);
    ++p;
  }
  for (int i=0;i<100000;++i) {
    std::printf("0 131069 1\n");
    ++p;
    std::printf("0 %d 1\n", p);
    ++p;
  }
}
