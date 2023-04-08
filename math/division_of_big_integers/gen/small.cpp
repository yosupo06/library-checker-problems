#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "../params.h"

int main() {
  vector<string> A, B;
  int lsum = 0, flag = true;
  for (int i = 0; flag; i++) {
    for (int j = 1; j <= i * 2 + 10 && flag; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          int a = k ? -i : +i;
          int b = l ? -j : +j;
          string sa = to_string(a);
          string sb = to_string(b);
          lsum += sa.size() + sb.size();
          if (lsum > SUM_OF_CHARACTER_LENGTH) {
            flag = false;
            break;
          }
          A.push_back(sa);
          B.push_back(sb);
        }
      }
    }
  }
  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
