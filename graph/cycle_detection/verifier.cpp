#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>

int main() {
	registerValidation();
	
	int N = inf.readInt(N_MIN, N_MAX);
	inf.readSpace();
	int M = inf.readInt(M_MIN, M_MAX);
	inf.readChar('\n');
	
	for(int i=0; i<M; i++) {
		int u = inf.readInt(0, N-1);
		inf.readSpace();
		int v = inf.readInt(0, N-1);
		inf.readChar('\n');
		ensure(u != v);
	}
	inf.readEof();
	return 0;
}
