#include "testlib.h"
#include "params.h"

int main() {
	registerValidation();
	
	int n = inf.readInt(1, N_MAX);
	inf.readChar(' ');
	int q = inf.readInt(1, Q_MAX);
	inf.readChar('\n');
	
	for (int i = 0; i < n; i++) {
		inf.readInt(0, COORD_MAX, "x");
		inf.readSpace();
		inf.readInt(0, COORD_MAX, "y");
		inf.readSpace();
		inf.readInt(0, MOD - 1, "w");
		inf.readChar('\n');
	}
	
	for (int i = 0; i < q; i++) {
		int t = inf.readInt(0, 3);
		inf.readSpace();
		if (t == 0) {
			inf.readInt(0, COORD_MAX, "x");
			inf.readSpace();
			inf.readInt(0, COORD_MAX, "y");
			inf.readSpace();
			inf.readInt(0, MOD - 1, "w");
			++n;
		}
		else if (t == 1) {
			inf.readInt(0, n - 1, "x");
			inf.readSpace();
			inf.readInt(0, MOD - 1, "w");
		} 
		else if (t == 2) {
			int l = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int d = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int r = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int u = inf.readInt(0, COORD_MAX);
			ensure(l < r);
			ensure(d < u);
		}
		else {
			int l = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int d = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int r = inf.readInt(0, COORD_MAX);
			inf.readSpace();
			int u = inf.readInt(0, COORD_MAX);
			ensure(l < r);
			ensure(d < u);
			inf.readSpace();
			inf.readInt(0, MOD - 1);
			inf.readSpace();
			inf.readInt(0, MOD - 1);
		}
		inf.readChar('\n');
	}
	inf.readEof();
	return 0;
}
