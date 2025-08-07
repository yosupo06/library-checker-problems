#include <algorithm>
#include <cassert>
#include "params.h"
#include "testlib.h"
using namespace std;

int main()
{
    registerValidation();
    long long T = inf.readLong(1, T_MAX);
    inf.readChar('\n');
    if (T == 1)
    {
        long long N = inf.readLong(1, N_MAX);
        inf.readChar('\n');
        long long SQ = sqrtl(N);
        while (SQ * SQ + SQ <= N)
            SQ++;
        long long sz = N / SQ + SQ - 1;
        // f
        for (int i = 0; i < sz; i++)
        {
            inf.readInt(0, MOD - 1);
            if (i == sz - 1)
                inf.readChar('\n');
            else
                inf.readSpace();
        }
        // g
        for (int i = 0; i < sz; i++)
        {
            inf.readInt(0, MOD - 1);
            if (i == sz - 1)
                inf.readChar('\n');
            else
                inf.readSpace();
        }
        inf.readEof();
    }
    else
    {
        for (int _ = 1; _ <= T; _++)
        {
            long long N = inf.readLong(1, N_MAX);
            inf.readChar('\n');
            ensure(N == _);
            long long SQ = sqrtl(N);
            while (SQ * SQ + SQ <= N)
                SQ++;
            long long sz = N / SQ + SQ - 1;
            // f
            for (int i = 0; i < sz; i++)
            {
                inf.readInt(0, MOD - 1);
                if (i == sz - 1)
                    inf.readChar('\n');
                else
                    inf.readSpace();
            }
            // g
            for (int i = 0; i < sz; i++)
            {
                inf.readInt(0, MOD - 1);
                if (i == sz - 1)
                    inf.readChar('\n');
                else
                    inf.readSpace();
            }
        }
        inf.readEof();
    }
}
