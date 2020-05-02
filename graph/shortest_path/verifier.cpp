#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>

int main() {
	registerValidation();
	
	int n = inf.readInt(N_MIN, N_MAX);
	inf.readSpace();
	int m = inf.readInt(M_MIN, M_MAX);
	inf.readSpace();
	int s = inf.readInt(0, n - 1);
	inf.readSpace();
	int t = inf.readInt(0, n - 1);
	inf.readChar('\n');
	
	ensure(s != t);
	
	std::set<std::pair<int, int> > hens;
	for (int i = 0; i < m; i++) {
		int a = inf.readInt(0, n - 1);
		inf.readSpace();
		int b = inf.readInt(0, n - 1);
		inf.readSpace();
		inf.readInt(C_MIN, C_MAX, "c");
		inf.readChar('\n');
		
		ensure(a != b);
		ensure(hens.insert({a, b}).second);
	}
	inf.readEof();
	return 0;
}
