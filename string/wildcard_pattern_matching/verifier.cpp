#include <iostream>

#include "testlib.h"
#include "params.h"

int main()
{
    registerValidation();

    std::string s = inf.readToken(format("[a-z*]{%d, %d}", 1, int(S_LEN_MAX)));
    inf.readChar('\n');
    std::string t = inf.readToken(format("[a-z*]{%d, %d}", 1, int(s.size())));
    inf.readChar('\n');
    inf.readEof();
    return 0;
}