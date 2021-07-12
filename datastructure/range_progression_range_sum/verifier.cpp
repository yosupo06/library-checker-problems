#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_AND_Q_MAX, "Q");
    inf.readChar('\n');

    for(int i = 0; i < n; ++i)
	{
        inf.readLong(-A_K_MIN_MAX, A_K_MIN_MAX, "a_i");
        if(i != n - 1)
		{ inf.readSpace(); }
    }
    inf.readChar('\n');

	while(q--)
	{
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t)
		{
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            inf.readInt(l, n - 1, "r");
        }
		else
		{
			int l = inf.readInt(0, n - 1, "l");
			inf.readSpace();
			inf.readInt(l, n - 1, "r");
			inf.readSpace();

			inf.readLong(-A_K_MIN_MAX, A_K_MIN_MAX, "k");
        }
        inf.readChar('\n');
    }

    inf.readEof();
}
