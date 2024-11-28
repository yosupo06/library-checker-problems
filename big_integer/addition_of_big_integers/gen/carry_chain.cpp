#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
  // seed % 2 : randomize last some digits or not
  // seed / 2 : switch patterns
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  // decimal
  std::string DIGIT_CHARS = "0123456789";
  int BASE = 10;

  // short case
  long long max_dig1 = 1;
  while(true){
    long long x = max_dig1 + 1;
    if(x > LOG_10_A_AND_B_MAX) break;
    // split sum(size) into 14 unit,
    // around 12 unit required, 2 unit left for randomization
    if((x * (x+1) / 2 + x * 10) > SUM_OF_CHARACTER_LENGTH / 14) break;
    max_dig1 = x;
  }
  
  std::vector<std::string> A, B;

  // type 1, 3
  if(seed / 2 == 0){

    // Case Type 1
    //   1 + 999...999
    // 4 unit
    for(int t=0; t<4; t++){
      for(int d=1; d<=max_dig1; d++){

        std::string a = std::string(1, DIGIT_CHARS[1]);
        std::string b = std::string(d, DIGIT_CHARS[BASE-1]);

        if(t & 1) std::swap(a, b);
        if(t & 2){
          a.insert(a.begin(), '-');
          b.insert(b.begin(), '-');
        }

        A.push_back(std::move(a));
        B.push_back(std::move(b));
      }
    }
    
    // Case Type 3
    //   1000...000 - 999...999
    // 8 unit
    for(int t=0; t<4; t++){
      for(int d=1; d<=max_dig1; d++){
        std::string a = std::string(d, DIGIT_CHARS[BASE-1]);
        std::string b = std::string(1, DIGIT_CHARS[1]) + std::string(d, DIGIT_CHARS[0]);

        if(t & 1) std::swap(a, b);
        if(t & 2){
          a.insert(a.begin(), '-');
        } else {
          b.insert(b.begin(), '-');
        }

        A.push_back(std::move(a));
        B.push_back(std::move(b));
      }
    }
  }
  // type 2, 4, 5
  else if(seed / 2 == 1){
    
    // Case Type 2
    //   1000...000 - 1
    // 4 unit
    for(int t=0; t<4; t++){
      for(int d=1; d<=max_dig1; d++){
        std::string a = std::string(1, DIGIT_CHARS[1]);
        std::string b = std::string(1, DIGIT_CHARS[1]) + std::string(d, DIGIT_CHARS[0]);

        if(t & 1) std::swap(a, b);
        if(t & 2){
          a.insert(a.begin(), '-');
        } else {
          b.insert(b.begin(), '-');
        }

        A.push_back(std::move(a));
        B.push_back(std::move(b));
      }
    }
  
    // Case Type 4
    //   A + B = 0
    // 4 unit
    for(int t=0; t<2; t++){
      for(int d=1; d<=max_dig1; d++){
        std::string a;
        for(int i=0; i<d; i++){
          int dig = gen.uniform((i == 0 ? 1 : 0), BASE-1);
          a.push_back(DIGIT_CHARS[dig]);
        }
        
        std::string b = a;

        if(t & 1){
          a.insert(a.begin(), '-');
        } else {
          b.insert(b.begin(), '-');
        }

        A.push_back(std::move(a));
        B.push_back(std::move(b));
      }
    }
  
    // Case Type 5
    //   A + B = 100...000*
    // 4 unit
    for(int t=0; t<2; t++){
      for(int d=1; d<=max_dig1; d++){
        std::string a;
        std::string b;

        for(int i=0; i<d; i++){
          // if (BASE-1) at the leading digit , b will have a leading zero
          int dig = (i == 0) ? gen.uniform(1, BASE-2) : gen.uniform(0, BASE-1);
          a.push_back(DIGIT_CHARS[dig]);
          b.push_back(DIGIT_CHARS[BASE-1 - dig]);
        }
        
        auto u = gen.uniform_pair(1, BASE);
        a.push_back(DIGIT_CHARS[BASE - u.first]);
        b.push_back(DIGIT_CHARS[u.second - 1]);

        if(t & 1){
          a.insert(a.begin(), '-');
          b.insert(b.begin(), '-');
        }

        A.push_back(std::move(a));
        B.push_back(std::move(b));
      }
    }

  }

  int T = (int)A.size();

  int available_char_count = SUM_OF_CHARACTER_LENGTH;
  for(auto& a : A) available_char_count -= (int)a.size();
  for(auto& b : B) available_char_count -= (int)b.size();

  // randomize lower digit
  if(seed % 2 == 1){
    while(available_char_count >= 2){
      int c0 = gen.uniform(0, BASE-1);
      int c1 = gen.uniform(0, BASE-1);
      int t = gen.uniform(0, T-1);
      A[t].push_back(DIGIT_CHARS[c0]);
      B[t].push_back(DIGIT_CHARS[c1]);
      available_char_count -= 2;
    }
  }

  printf("%d\n", T);
  for (int i = 0; i < T; i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
