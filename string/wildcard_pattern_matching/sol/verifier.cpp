#include <iostream>

#include "testlib.h"
#include "params.h"

int main()
{
    registerValidation();

    std::string s = inf.readToken(std::format("[a-z\*]{%d, %d}", 1, S_LEN_MAX));
    inf.readChar('\n');
    std::string t = inf.readToken(std::format("[a-z\*]{%d, %d}", 1, s.size()));
    inf.readChar('\n');
    inf.readEof();
    return 0;
}