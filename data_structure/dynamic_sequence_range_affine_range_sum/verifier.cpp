#include "testlib.h"
#include "params.h"

int main() {
	registerValidation();
	
	int n = inf.readInt(1, (int) N_AND_Q_MAX);
	inf.readChar(' ');
	int q = inf.readInt(1, (int) N_AND_Q_MAX);
	inf.readChar('\n');
	
	auto a = inf.readInts(n, 0, (int) MOD - 1);
	inf.readChar('\n');
	
	int len = n;
	for (int i = 0; i < q; i++) {
		int t = inf.readInt(0, 4);
		inf.readChar(' ');
		if (t == 0) {
			inf.readInt(0, len);
			inf.readChar(' ');
			inf.readInt(0, (int) MOD - 1);
			len++;
		} else if (t == 1) {
			ensure(len > 0);
			inf.readInt(0, len - 1);
			len--;
		} else {
			int l = inf.readInt(0, len - 1);
			inf.readChar(' ');
			inf.readInt(l + 1, len);
			if (t == 3) {
				inf.readChar(' ');
				inf.readInt(0, MOD - 1);
				inf.readChar(' ');
				inf.readInt(0, MOD - 1);
			}
		}
		inf.readChar('\n');
	}
	
	inf.readEof();
	return 0;
}
