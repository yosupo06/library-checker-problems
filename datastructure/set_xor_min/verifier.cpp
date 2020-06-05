#include <assert.h>
#include "testlib.h"
#include "params.h"

int main() {
	registerValidation();

	int Q = inf.readInt(1, MAX_Q);
	inf.readChar('\n');
	
	std::set<int> all;
	for (int i = 0; i < Q; i++) {
		int t = inf.readInt(0, 2);
		inf.readChar(' ');
		int x = inf.readInt(0, (1 << 30) - 1);
		inf.readChar('\n');
		
		if (t == 0) all.insert(x);
		else if (t == 1) all.erase(x);
		else assert(all.size());
	}
	
	inf.readEof();
	return 0;
}
