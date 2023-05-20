#include <cstdio>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

//int main(int, char* argv[]) {
    //long long seed = atoll(argv[1]);
    //auto gen = Random(seed);
int main(){
    
    string s;
    char x = 'a';
    while((long long)s.size() * 2 + 1 <= N_MAX){
        s = s + string(1, x) + s;
        if(x == 'z') break;
        x++;
    }

    printf("%s\n", s.c_str());
    return 0;
}
